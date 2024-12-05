/**
 *  USBHIDMOUSE HID Mouse Source File
 *  @file usb_hid_mouse.c
 *  @ingroup usb_hid
 *  @brief Contains implementation for USB Mouse drivers.
 *  @version USB Device Stack Driver Version 1.0.0
 */

/*
    (c) 2023 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
 */

#include <usb_hid_mouse.h>
#include <stddef.h>
#include <usb_common_elements.h>
#include <usb_hid.h>
#include <usb_hid_transfer.h>
#include <usb_core.h>
#include <usb_config.h>
#include <usb_protocol_hid.h>

STATIC uint8_t usbHIDMouseRate;
STATIC uint8_t usbHIDMouseProtocol;
STATIC USB_MOUSE_REPORT_DATA_t mouseInputReport;

void USB_HIDMouseInitialize(USB_HID_REPORT_DESCRIPTOR_t *reportPtr)
{
    // Initialize idle rate and protocol
    usbHIDMouseRate = 0;
    usbHIDMouseProtocol = 0;
    // Clear input report
    mouseInputReport.Button = 0;
    mouseInputReport.X = 0;
    usbHIDMouseProtocol = 0;
    //Clear input report
	mouseInputReport.id = 2;
    mouseInputReport.Button = 0;
	mouseInputReport.HWheel = 0;
	mouseInputReport.VWheel = 0;
    mouseInputReport.X = 0;
    mouseInputReport.Y = 0;
    // Register Rate, Protocol and Report Descriptor pointers
    USB_HIDInitialize(&usbHIDMouseRate, &usbHIDMouseProtocol, reportPtr);
};

RETURN_CODE_t USB_HIDMouseMove(int8_t x_position, int8_t y_position)
{
    RETURN_CODE_t status = UNINITIALIZED;

    // Add position in HID mouse report
    if ((-127 > x_position) || (127 < x_position))
    {
        status = UNSUPPORTED; // Overflow of report
    }
    else if ((-127 > y_position) || (127 < y_position))
    {
        status = UNSUPPORTED; // Overflow of report
    }
    else
    {
		mouseInputReport.Button = 0;
        mouseInputReport.HWheel = 0;
        mouseInputReport.VWheel = 0;
	    mouseInputReport.X = x_position;
        mouseInputReport.Y = y_position;

        // Valid and send report
        status = USB_HIDMouseReportInSend(&mouseInputReport);
    }

    return status;
}

RETURN_CODE_t USB_HIDMouseScroll(int8_t h_position, int8_t v_position)
{
    mouseInputReport.Button = 0;
    mouseInputReport.X = 0;
    mouseInputReport.Y = 0;
    mouseInputReport.HWheel = h_position;
    mouseInputReport.VWheel = v_position;

	return USB_HIDMouseReportInSend(&mouseInputReport);
}

RETURN_CODE_t USB_HIDMouseButton(bool buttonState, uint8_t button)
{
    RETURN_CODE_t status = UNINITIALIZED;
    // Modify buttons report
    if (HID_MOUSE_BUTTON_DOWN == buttonState)
    {
        mouseInputReport.Button |= button;
        status = USB_HIDMouseReportInSend(&mouseInputReport);
    }
    else
    {
        mouseInputReport.Button &= ~button;
        status = USB_HIDMouseReportInSend(&mouseInputReport);
    }

    return status;
}

RETURN_CODE_t USB_HIDMouseButtonLeft(bool buttonState)
{
    return USB_HIDMouseButton(buttonState, HID_MOUSE_LEFT_BUTTON);
}

RETURN_CODE_t USB_HIDMouseButtonRight(bool buttonState)
{
    return USB_HIDMouseButton(buttonState, HID_MOUSE_RIGHT_BUTTON);
}

RETURN_CODE_t USB_HIDMouseButtonMiddle(bool buttonState)
{
    return USB_HIDMouseButton(buttonState, HID_MOUSE_MIDDLE_BUTTON);
}
