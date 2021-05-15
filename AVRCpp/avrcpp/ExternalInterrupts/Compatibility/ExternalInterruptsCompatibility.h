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

#ifndef EXTERNALINTERRUPTSCOMPATIBILITY_H_
#define EXTERNALINTERRUPTSCOMPATIBILITY_H_

#include "../ExternalInterrupts.h"
#include <avr/interrupt.h>

#ifdef __AVR_ATmega128__ //TODO : other devices

#define EXTERNAL_INT0
#define ISC_EICR0 	EICRA
#define EIMSK0		EIMSK
#define EIFR0		EIFR

#define EXTERNAL_INT1
#define ISC_EICR1 	EICRA
#define EIMSK1		EIMSK
#define EIFR1		EIFR

#define EXTERNAL_INT2
#define ISC_EICR2 	EICRA
#define EIMSK2		EIMSK
#define EIFR2		EIFR

#define EXTERNAL_INT3
#define ISC_EICR3 	EICRA
#define EIMSK3		EIMSK
#define EIFR3		EIFR

#define EXTERNAL_INT4
#define ISC_EICR4 	EICRB
#define EIMSK4		EIMSK
#define EIFR4		EIFR

#define EXTERNAL_INT5
#define ISC_EICR5 	EICRB
#define EIMSK5		EIMSK
#define EIFR5		EIFR

#define EXTERNAL_INT6
#define ISC_EICR6 	EICRB
#define EIMSK6		EIMSK
#define EIFR6		EIFR

#define EXTERNAL_INT7
#define ISC_EICR7 	EICRB
#define EIMSK7		EIMSK
#define EIFR7		EIFR

#endif

#define EXTERNAL_INT_CASE(number) \
	case number : 	static ExternalInterrupt * instance##number;\
					if(isNull(instance##number))\
						instance##number = new ExternalInterrupt(&ISC_EICR##number, ExternalInterrupt::RISING_EDGE, buildMask(ISC##number##0, ISC##number##1), &EIMSK##number, INT##number, &EIFR##number, INTF##number);\
					instance = instance##number;\
					break

#define EXTERNAL_INT_ISR(number) \
ISR(INT##number##_vect)\
{\
	ExternalInterrupt::getInstance(number)->externalInterruptCallBack();\
}\

ExternalInterrupt * ExternalInterrupt::getInstance(size_t number)
{

	static ExternalInterrupt * instance;

	switch (number)
	{

#ifdef EXTERNAL_INT0
				EXTERNAL_INT_CASE(0);
#endif
#ifdef EXTERNAL_INT1
				EXTERNAL_INT_CASE(1);
#endif
#ifdef EXTERNAL_INT2
				EXTERNAL_INT_CASE(2);
#endif
#ifdef EXTERNAL_INT3
				EXTERNAL_INT_CASE(3);
#endif
#ifdef EXTERNAL_INT4
				EXTERNAL_INT_CASE(4);
#endif
#ifdef EXTERNAL_INT5
				EXTERNAL_INT_CASE(5);
#endif
#ifdef EXTERNAL_INT6
				EXTERNAL_INT_CASE(6);
#endif
#ifdef EXTERNAL_INT7
				EXTERNAL_INT_CASE(7);
#endif

	default :	instance = NULL;

	}

	return instance;

}

#ifdef EXTERNAL_INT0
EXTERNAL_INT_ISR(0);
#endif
#ifdef EXTERNAL_INT1
EXTERNAL_INT_ISR(1);
#endif
#ifdef EXTERNAL_INT2
EXTERNAL_INT_ISR(2);
#endif
#ifdef EXTERNAL_INT3
EXTERNAL_INT_ISR(3);
#endif
#ifdef EXTERNAL_INT4
EXTERNAL_INT_ISR(4);
#endif
#ifdef EXTERNAL_INT5
EXTERNAL_INT_ISR(5);
#endif
#ifdef EXTERNAL_INT6
EXTERNAL_INT_ISR(6);
#endif
#ifdef EXTERNAL_INT7
EXTERNAL_INT_ISR(7);
#endif

#endif /* EXTERNALINTERRUPTSCOMPATIBILITY_H_ */
