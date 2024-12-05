/**
 * USB_DEVICE_STACK Generated Driver File
 * 
 * @file usb_device.c
 * 
 * @ingroup usb_device_stack
 * 
 * @brief Driver implementation file for the USB device setup.
 *
 * @version USB_DEVICE_STACK Driver Version 1.0.0
*/
/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <usb_core.h>
#include <usb_hid.h>
#include <usb_hid_keyboard.h>
#include <usb_hid_keycodes.h>
#include "usb_device.h"
#include "usb0.h"

static RETURN_CODE_t usbStatus;
static void USBDevice_TransferHandler(void);
static void USBDevice_EventHandler(void);
static void USBDevice_DefaultStartOfFrameCallback(void);
static void USBDevice_DefaultSuspendCallback(void);
static void USBDevice_DefaultWakeFromSuspendCallback(void);
static void USBDevice_DefaultResetCallback(void);
static void HID_DefaultSetReportCallback(uint16_t report);

void USBDevice_Initialize(void)
{
    USB_DescriptorPointersSet(&descriptorPointers);
    USB_SOFCallbackRegister(USBDevice_DefaultStartOfFrameCallback);
    USB_SuspendCallbackRegister(USBDevice_DefaultSuspendCallback);
    USB_ResumeCallbackRegister(USBDevice_DefaultWakeFromSuspendCallback);
    USB_ResetCallbackRegister(USBDevice_DefaultResetCallback);
    
    USB_HIDKeyboardInitialize(&USB_HIDKeyboardReportDescriptor, HID_DefaultSetReportCallback);

    USB0_TrnComplCallbackRegister(USBDevice_TransferHandler);
    USB0_BusEventCallbackRegister(USBDevice_EventHandler);

    usbStatus = USB_Start();
}

RETURN_CODE_t USBDevice_StatusGet(void)
{
    return usbStatus;
}

static void USBDevice_TransferHandler(void)
{
    usbStatus = USB_TransferHandler();
}

static void USBDevice_EventHandler(void)
{
    usbStatus = USB_EventHandler();
}

void USBDevice_StartOfFrameCallbackRegister(USB_EVENT_CALLBACK_t cb)
{
    USB_SOFCallbackRegister(cb);
}

void USBDevice_SuspendCallbackRegister(USB_EVENT_CALLBACK_t cb)
{
    USB_SuspendCallbackRegister(cb);
}

void USBDevice_WakeFromSuspendCallbackRegister(USB_EVENT_CALLBACK_t cb)
{
    USB_ResumeCallbackRegister(cb);
}

void USBDevice_ResetCallbackRegister(USB_EVENT_CALLBACK_t cb)
{
    USB_ResetCallbackRegister(cb);    
}

static void USBDevice_DefaultStartOfFrameCallback(void)
{
    // Add routine here
}

static void USBDevice_DefaultSuspendCallback(void)
{
    // Add routine here
}

static void USBDevice_DefaultWakeFromSuspendCallback(void)
{
    // Add routine here
}

static void USBDevice_DefaultResetCallback(void)
{
    // Add routine here
}
    
void HID_SetReportCallbackRegister(USB_HID_REPORT_CALLBACK_t cb)
{
    USB_HIDReportUpdatedCallbackRegister(cb);
}

static void HID_DefaultSetReportCallback(uint16_t report)
{
    // Add routine here
}

/**
 End of File
*/
