/*
 * encoders.c
 *
 * Created: 04.11.2022
 * Author: echoromeo
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "pins.h"

#if (ENCODER_NUM > 0)

volatile int32_t p1_count;
volatile int32_t p2_count;

void encoders_init(void) {
	// Set up pins
	ENCODER1_PORT.PINCONFIG = PORT_PULLUPEN_bm;
	ENCODER1_PORT.PINCTRLUPD = ENCODER1_gm;
	#if defined(__AVR_AVR64DU28__) || defined(__AVR_AVR64DU32__)
	ENCODER1_PORT.EVGENCTRLA = (ENCODER1_PINA_bp << PORT_EVGEN0SEL_gp) | (ENCODER1_PINB_bp << PORT_EVGEN1SEL_gp);
	#endif // DU

	// Set up EVSYS
	EVSYS.ENCODER1_CHANNELA = ENCODER1_CHANNELA_gc;
	EVSYS.ENCODER1_CHANNELB = ENCODER1_CHANNELB_gc;
	EVSYS.USERCCLLUT0A = EVSYS_USER_CHANNEL2_gc;
	EVSYS.USERCCLLUT1A = EVSYS_USER_CHANNEL3_gc;
	#if defined(__AVR_AVR64DU28__) || defined(__AVR_AVR64DU32__)
	EVSYS.CHANNEL0 = EVSYS_CHANNEL_CCL_LUT0_gc;
	EVSYS.CHANNEL1 = EVSYS_CHANNEL_CCL_LUT1_gc;
	#else
	EVSYS.CHANNEL0 = EVSYS_CHANNEL0_CCL_LUT0_gc;
	EVSYS.CHANNEL1 = EVSYS_CHANNEL1_CCL_LUT1_gc;
	#endif // DU
	EVSYS.USERTCA0CNTA = EVSYS_USER_CHANNEL0_gc;
	EVSYS.USERTCA0CNTB = EVSYS_USER_CHANNEL1_gc;

	// Set up CCL
	CCL.TRUTH0 = CCL_TRUTH_1_bm;
	CCL.TRUTH1 = CCL_TRUTH_1_bm;
	CCL.LUT0CTRLB = CCL_INSEL0_EVENTA_gc;
	CCL.LUT1CTRLB = CCL_INSEL0_EVENTA_gc;
	CCL.LUT0CTRLA = CCL_ENABLE_bm | CCL_CLKSRC_OSC1K_gc | CCL_FILTSEL_FILTER_gc;
	CCL.LUT1CTRLA = CCL_ENABLE_bm | CCL_CLKSRC_OSC1K_gc | CCL_FILTSEL_FILTER_gc;

	// Set up TCA
	ENCODER1_TCA.EVCTRL = TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_CNTBEI_bm |
	                        TCA_SINGLE_EVACTA_CNT_POSEDGE_gc | TCA_SINGLE_EVACTB_UPDOWN_gc;
	ENCODER1_TCA.PER = ENCODER1_RESOLUTION-1;
	ENCODER1_TCA.INTCTRL = TCA_SINGLE_OVF_bm;
	encoder1_reset(0);
	ENCODER1_TCA.CTRLA = TCA_SINGLE_ENABLE_bm;


#if (ENCODER_NUM > 1)
	// Set up pins
	ENCODER2_PORT.PINCTRLUPD = ENCODER2_gm;

	// Set up EVSYS
	EVSYS.ENCODER2_CHANNELA = ENCODER2_CHANNELA_gc;
	EVSYS.ENCODER2_CHANNELB = ENCODER2_CHANNELB_gc;
	EVSYS.USERCCLLUT2A = EVSYS_USER_CHANNEL4_gc;
	EVSYS.USERCCLLUT3A = EVSYS_USER_CHANNEL5_gc;
	EVSYS.CHANNEL6 = EVSYS_CHANNEL6_CCL_LUT2_gc;
	EVSYS.CHANNEL7 = EVSYS_CHANNEL7_CCL_LUT3_gc;
	EVSYS.USERTCA1CNTA = EVSYS_USER_CHANNEL6_gc;
	EVSYS.USERTCA1CNTB = EVSYS_USER_CHANNEL7_gc;

	// Set up CCL
	CCL.TRUTH2 = CCL_TRUTH_1_bm;
	CCL.TRUTH3 = CCL_TRUTH_1_bm;
	CCL.LUT2CTRLB = CCL_INSEL0_EVENTA_gc;
	CCL.LUT3CTRLB = CCL_INSEL0_EVENTA_gc;
	CCL.LUT2CTRLA = CCL_ENABLE_bm | CCL_CLKSRC_OSC1K_gc | CCL_FILTSEL_FILTER_gc;
	CCL.LUT3CTRLA = CCL_ENABLE_bm | CCL_CLKSRC_OSC1K_gc | CCL_FILTSEL_FILTER_gc;

	// Set up TCA
	ENCODER2_TCA.EVCTRL = TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_CNTBEI_bm |
	                        TCA_SINGLE_EVACTA_CNT_POSEDGE_gc | TCA_SINGLE_EVACTB_UPDOWN_gc;
	ENCODER2_TCA.PER = ENCODER2_RESOLUTION-1;
	ENCODER2_TCA.INTCTRL = TCA_SINGLE_OVF_bm;
	encoder2_reset(0);
	ENCODER2_TCA.CTRLA = TCA_SINGLE_ENABLE_bm;
#endif // (ENCODER_NUM > 1)

	// Enable CCL last because of the enable-protect stuff
	CCL.CTRLA = CCL_ENABLE_bm;
}

void encoder1_reset(int8_t offset) {
	ENCODER1_TCA.CNT = 0;
	p1_count = offset;
}

int32_t encoder1_count(void) {
	return p1_count + encoder1_position;
}

uint8_t encoder1_count_limit(uint8_t max)
{
	int8_t position = encoder1_count();
	if (position < 0)
	{
		p1_count = -encoder1_position;
		position = 0;
	} else if (position > max)
	{
		p1_count = max - encoder1_position;
		position = max;
	}
	
	return position;
}

ISR(ENCODER1_vect) {
	if (ENCODER1_TCA.CTRLECLR & TCA_SINGLE_DIR_bm)
	{
		p1_count -= ENCODER1_RESOLUTION;
		} else {
		p1_count += ENCODER1_RESOLUTION;
	}
	
	// Handle overflow on int32?

	ENCODER1_TCA.INTFLAGS = TCA_SINGLE_OVF_bm;
}


#if (ENCODER_NUM > 1)

void encoder2_reset(int8_t offset) {
	ENCODER2_TCA.CNT = 0;
	p2_count = offset;	
}

int32_t encoder2_count(void) {
	return p2_count + encoder2_position;	
}

uint8_t encoder2_count_limit(uint8_t max)
{
	int8_t position = encoder2_count();
	if (position < 0)
	{
		p2_count = -encoder2_position;
		position = 0;
	} else if (position > max)
	{
		p2_count = max - encoder2_position;
		position = max;
	}
	
	return position;
}

ISR(ENCODER2_vect) {
	if (ENCODER2_TCA.CTRLECLR & TCA_SINGLE_DIR_bm)
	{
		p2_count -= ENCODER2_RESOLUTION;
	} else {
		p2_count += ENCODER2_RESOLUTION;
	}
	
	// Handle overflow on int32?

	ENCODER2_TCA.INTFLAGS = TCA_SINGLE_OVF_bm;
}

#endif /* (ENCODER_NUM > 1) */
#endif /* (ENCODER_NUM > 0) */
