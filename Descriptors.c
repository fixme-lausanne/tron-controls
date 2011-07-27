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

#include "Descriptors.h"

const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] = {
	/* from -127 to 127, 1 button (fake), relative */
	HID_DESCRIPTOR_MOUSE(-128, 127, -128, 127, 1, false)
};

const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport[] = {
	/* Digital Joystick with three buttons:
	 * Mind the report id!
	 *   Min X/Y Axis values: -1 (left/down)
	 *   Max X/Y Axis values:  1 (right/up)
	 *   Buttons: 3
	 */
	HID_DESCRIPTOR_JOYSTICK(-1, 1, -1, 1, 3)
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor = {
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(01.10),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 0x03EB,
	.ProductID              = 0x2043,
	.ReleaseNumber          = VERSION_BCD(00.01),

	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor = {
	.Config = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

		.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
		.TotalInterfaces        = 2,

		.ConfigurationNumber    = 1,
		.ConfigurationStrIndex  = NO_DESCRIPTOR,

		.ConfigAttributes       = (USB_CONFIG_ATTR_BUSPOWERED | USB_CONFIG_ATTR_SELFPOWERED),

		.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
	},

	.HID1_MouseInterface = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

		.InterfaceNumber        = 0x00,
		.AlternateSetting       = 0x00,

		.TotalEndpoints         = 1,

		.Class                  = HID_CSCP_HIDClass,
		.SubClass               = HID_CSCP_NonBootSubclass,
		.Protocol               = HID_CSCP_NonBootProtocol,

		.InterfaceStrIndex      = NO_DESCRIPTOR
	},

	.HID1_MouseHID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

		.HIDSpec                = VERSION_BCD(01.11),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(MouseReport)
	},

	.HID1_ReportINEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | MOUSE_EPNUM),
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_EPSIZE,
		.PollingIntervalMS      = 0x01
	},



	.HID2_JoystickInterface = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

		.InterfaceNumber        = 0x01,
		.AlternateSetting       = 0x00,

		.TotalEndpoints         = 1,

		.Class                  = HID_CSCP_HIDClass,
		.SubClass               = HID_CSCP_NonBootSubclass,
		.Protocol               = HID_CSCP_NonBootProtocol,

		.InterfaceStrIndex      = NO_DESCRIPTOR
	},

	.HID2_JoustickHID = {
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

		.HIDSpec                = VERSION_BCD(01.11),
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = HID_DTYPE_Report,
		.HIDReportLength        = sizeof(JoystickReport)
	},

	.HID2_ReportINEndpoint = {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | JOYSTICK_EPNUM),
		.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize           = HID_EPSIZE,
		.PollingIntervalMS      = 0x01
	},
};

const USB_Descriptor_String_t PROGMEM LanguageString = {
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

const USB_Descriptor_String_t PROGMEM ManufacturerString = {
	.Header                 = {.Size = USB_STRING_LEN(17), .Type = DTYPE_String},

	.UnicodeString          = L"FIXME Hackerspace"
};

const USB_Descriptor_String_t PROGMEM ProductString = {
	.Header                 = {.Size = USB_STRING_LEN(13), .Type = DTYPE_String},

	.UnicodeString          = L"TRON Joystick"
};

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)	{
	case DTYPE_Device:
		Address = &DeviceDescriptor;
		Size    = sizeof(USB_Descriptor_Device_t);
		break;

	case DTYPE_Configuration:
		Address = &ConfigurationDescriptor;
		Size    = sizeof(USB_Descriptor_Configuration_t);
		break;

	case DTYPE_String:
		switch (DescriptorNumber) {
		case 0x00:
			Address = &LanguageString;
			Size    = pgm_read_byte(&LanguageString.Header.Size);
			break;
		case 0x01:
			Address = &ManufacturerString;
			Size    = pgm_read_byte(&ManufacturerString.Header.Size);
			break;
		case 0x02:
			Address = &ProductString;
			Size    = pgm_read_byte(&ProductString.Header.Size);
			break;
		}
		break;

	case HID_DTYPE_HID:
		switch (wIndex) {
		case 0:
			Address = &ConfigurationDescriptor.HID1_MouseHID;
			break;
		case 1:
			Address = &ConfigurationDescriptor.HID2_JoustickHID;
			break;
		}
		Size = sizeof(USB_HID_Descriptor_HID_t);
		break;

	case HID_DTYPE_Report:
		switch (wIndex) {
		case 0:
			Address = &MouseReport;
			Size = sizeof(MouseReport);
			break;
		case 1:
			Address = &JoystickReport;
			Size = sizeof(JoystickReport);
			break;
		}
		break;
	}

	*DescriptorAddress = Address;
	return Size;
}

