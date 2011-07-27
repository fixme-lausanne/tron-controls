/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include <avr/pgmspace.h>

#include <LUFA/Drivers/USB/USB.h>

typedef struct {
	USB_Descriptor_Configuration_Header_t Config;
	USB_Descriptor_Interface_t            HID1_MouseInterface;
	USB_HID_Descriptor_HID_t              HID1_MouseHID;
	USB_Descriptor_Endpoint_t             HID1_ReportINEndpoint;
	USB_Descriptor_Interface_t            HID2_JoystickInterface;
	USB_HID_Descriptor_HID_t              HID2_JoustickHID;
	USB_Descriptor_Endpoint_t             HID2_ReportINEndpoint;
} USB_Descriptor_Configuration_t;

#define MOUSE_EPNUM	1
#define JOYSTICK_EPNUM  3

#define HID_EPSIZE      8

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
				    const uint8_t wIndex,
				    const void** const DescriptorAddress)
	ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);
