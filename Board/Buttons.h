/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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


#include <avr/io.h>
#include <stdbool.h>
#include <LUFA/Common/Common.h>
#include <avr/sfr_defs.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(__INCLUDE_FROM_BUTTONS_H)
#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
#endif

	/* Public Interface - May be used in end-application: */
	/* Macros: */
	/** Button mask for the buttons. */
#define BUTTONS_BUTTON1      (1 << 5)
#define BUTTONS_BUTTON2      (1 << 6)
#define BUTTONS_BUTTON3      (1 << 7)
#define BUTTONS_MASK  (BUTTONS_BUTTON1|BUTTONS_BUTTON2|BUTTONS_BUTTON3)

#if !defined(__DOXYGEN__)
	static inline void Buttons_Init(void)
	{
		DDRF  &= ~BUTTONS_MASK;
		PORTF |=  BUTTONS_MASK;
	}

	static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
	static inline uint8_t Buttons_GetStatus(void)
	{
		return ((PINF & BUTTONS_MASK) ^ BUTTONS_MASK);
	}
#endif

#if defined(__cplusplus)
}
#endif

/** @} */

