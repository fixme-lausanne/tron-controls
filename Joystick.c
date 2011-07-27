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

#include "Joystick.h"

static uint8_t PrevJoystickHIDReportBuffer[sizeof(USB_JoystickReport_Data_t)];

USB_ClassInfo_HID_Device_t Mouse_HID_Interface = {
	.Config =
	{
		.InterfaceNumber              = 0,

		.ReportINEndpointNumber       = MOUSE_EPNUM,
		.ReportINEndpointSize         = HID_EPSIZE,
		.ReportINEndpointDoubleBank   = false,

		.PrevReportINBufferSize       = sizeof(USB_MouseReport_Data_t),
	},
};

USB_ClassInfo_HID_Device_t Joystick_HID_Interface = {
	.Config =
	{
		.InterfaceNumber              = 1,

		.ReportINEndpointNumber       = JOYSTICK_EPNUM,
		.ReportINEndpointSize         = HID_EPSIZE,
		.ReportINEndpointDoubleBank   = false,

		.PrevReportINBuffer           = PrevJoystickHIDReportBuffer,
		.PrevReportINBufferSize       = sizeof(PrevJoystickHIDReportBuffer),
	},
};


int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	sei();

	for (;;)
	{
		HID_Device_USBTask(&Mouse_HID_Interface);
		HID_Device_USBTask(&Joystick_HID_Interface);
		USB_USBTask();
	}
}

void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	Joystick_Init();
	LEDs_Init();
	Buttons_Init();
	USB_Init();
}

void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Mouse_HID_Interface);
	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Joystick_HID_Interface);

	USB_Device_EnableSOFEvents();

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Mouse_HID_Interface);
	HID_Device_ProcessControlRequest(&Joystick_HID_Interface);
}

void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Mouse_HID_Interface);
	HID_Device_MillisecondElapsed(&Joystick_HID_Interface);
}

static uint16_t
CreateMouseReport(USB_MouseReport_Data_t *MouseReport)
{
	static uint8_t last_pos = 0;
	uint8_t DialPos = Joystick_GetDial();

	if (DialPos == last_pos)
		return 0;

	MouseReport->Y = DialPos - last_pos;
	MouseReport->X = 0;
	MouseReport->Button = 0;
	last_pos = DialPos;

	return (sizeof(*MouseReport));
}

static uint16_t
CreateJoystickReport(USB_JoystickReport_Data_t *JoystickReport)
{
	uint8_t JoyStatus_LCL    = Joystick_GetStatus();
	uint8_t ButtonStatus_LCL = Buttons_GetStatus();

	if (JoyStatus_LCL & JOY_UP)
		JoystickReport->Joystick.Y = -1;
	else if (JoyStatus_LCL & JOY_DOWN)
		JoystickReport->Joystick.Y = 1;
	else
		JoystickReport->Joystick.Y = 0;

	if (JoyStatus_LCL & JOY_LEFT)
		JoystickReport->Joystick.X =  -1;
	else if (JoyStatus_LCL & JOY_RIGHT)
		JoystickReport->Joystick.X = 1;
	else
		JoystickReport->Joystick.X = 0;

	JoystickReport->Button = 0;
	if (ButtonStatus_LCL & BUTTONS_BUTTON1)
		JoystickReport->Button |= (1 << 0);
	if (ButtonStatus_LCL & BUTTONS_BUTTON2)
		JoystickReport->Button |= (1 << 1);
	if (ButtonStatus_LCL & BUTTONS_BUTTON3)
		JoystickReport->Button |= (1 << 2);

	return (sizeof(*JoystickReport));
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	if (HIDInterfaceInfo == &Mouse_HID_Interface) {
		*ReportSize = CreateMouseReport(ReportData);
		if (*ReportSize != 0)
			return true;
	} else if (HIDInterfaceInfo == &Joystick_HID_Interface) {
		*ReportSize = CreateJoystickReport(ReportData);
	}

	return false;
}

void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
}

