/*
 * encoders.h
 *
 * Created: 03.11.2022
 * Author: echoromeo
 */
#ifndef ENCODERS_H_
#define ENCODERS_H_

#include <avr/io.h>
#include <pinout.h>

#if (ENCODER_NUM > 0)
void encoders_init(void);

#define encoder1_position		(ENCODER1_TCA.CNTL)

void encoder1_reset(int8_t offset);
int32_t encoder1_count(void);
uint8_t encoder1_count_limit(uint8_t max);

#if (ENCODER_NUM > 1)
#define encoder2_position		(ENCODER2_TCA.CNTL)

void encoder2_reset(int8_t offset);
int32_t encoder2_count(void);
uint8_t encoder2_count_limit(uint8_t max);

#endif /* (ENCODER_NUM > 1) */
#endif /* (ENCODER_NUM > 0) */
#endif /* ENCODERS_H_ */