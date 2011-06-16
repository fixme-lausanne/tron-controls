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
#include <LUFA/Common/Common.h>
#include <avr/sfr_defs.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(__INCLUDE_FROM_JOYSTICK_H)
#error Do not include this file directly. Include LUFA/Drivers/Board/Joystick.h instead.
#endif

	/* Private Interface - For use in library only: */
#if !defined(__DOXYGEN__)
#define JOY_MASK                 ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3))
#endif

	/* Public Interface - May be used in end-application: */
	/* Macros: */
#define JOY_UP                    (1 << 0)
#define JOY_DOWN                  (1 << 1)
#define JOY_LEFT                  (1 << 2)
#define JOY_RIGHT                 (1 << 3)

	/* Inline Functions: */
#if !defined(__DOXYGEN__)
	static inline void Joystick_Init(void)
	{
		DDRD  &= ~JOY_MASK;
		PORTD |= JOY_MASK;

		DDRB  = 0;
		PORTB |= 0xff;
	}

	static inline uint8_t Joystick_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
	static inline uint8_t Joystick_GetStatus(void)
	{
		return (uint8_t)(~PIND & JOY_MASK);
	}

	static inline uint8_t Joystick_GetDial(void) ATTR_WARN_UNUSED_RESULT;
	static inline uint8_t Joystick_GetDial(void)
	{
		return (uint8_t)(PINB);
	}
#endif

	/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

/** @} */

