/*
Copyright (c) 2007-2021 Maxime Lemonnier

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef ANALOGTODIGITALINTERFACECOMPATIBILITY_H_
#define ANALOGTODIGITALINTERFACECOMPATIBILITY_H_
#include "../ADCHardware.h"
#include <avr/interrupt.h>




#ifndef ADATE
	#define ADATE ADFR
#endif


#ifdef __AVR_ATmega1280__

#define ADC_vect_number 	29

#endif

#ifdef __AVR_ATtiny45__

#define ADC_vect_number 	8

#endif

#ifdef __AVR_ATmega16__

#define TRIGGER_REG 	SFIOR
#define TRIGGER_MASK	buildMask(ATDS0, ADTS1, ADTS2)
#define INTERNAL_VOLTAGE 2.56f

namespace Triggers
{

	/*!
	 * Trigger sources for trigger
	 */
	enum Trigger
	{
		MANUAL,
		FREE_RUNNING,
		ANALOG_COMPARATOR,
		EXTERNAL_INTERRUPT_0,
		TIMER0_COMPARE_MATCH,
		TIMER0_OVERFLOW,
		TIMER1_COMPARE_MATCH,
		TIMER1_OVERFLOW
	};

}


#endif


#ifdef __AVR_ATmega128__

#define TRIGGER_REG 	SFIOR
#define TRIGGER_MASK	0x00
#define INTERNAL_VOLTAGE 2.56f

namespace Triggers
{

	/*!
	 * Trigger sources for trigger
	 */
	enum Trigger
	{
		MANUAL,
		FREE_RUNNING
	};

}

#endif /* __AVR_ATmega128__ */

#endif /*ANALOGTODIGITALCOMPATIBILITY_H_*/
