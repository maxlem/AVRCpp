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

#ifndef Timer8bits2OCRCompatibility_H_
#define Timer8bits2OCRCompatibility_H_
#include "TimersCompatibility.h"
#include "../../CallbackServers/FastCallbackServer.h"
#include "../Timer8bits2OCR.h"

namespace Timers
{

#define Timer8bits2OCR_CREATE(number) \
	new Timer8bits2OCR(&TCCR##number##A, buildMask(COM##number##A0, COM##number##A1), buildMask(COM##number##B0, COM##number##B1), buildMask(WGM##number##0, WGM##number##1),\
						&TCCR##number##B, WGM##number##2, buildMask(CS##number##0, CS##number##1, CS##number##2),\
						&TCNT##number, &OCR##number##A, &OCR##number##B, \
						&TIMSK##number, TOIE##number, TIMER##number##_OVF_vect_number, OCIE##number##A, TIMER##number##_COMPA_vect_number, OCIE##number##B, TIMER##number##_COMPB_vect_number,\
						&TIFR##number, TOV##number, OCF##number##A, OCF##number##B)

#define Timer8bits2OCR_CASE(number)\
	case number:		static Timer8bits2OCR * timer##number;\
						if(isNull(timer##number))\
							timer##number = Timer8bits2OCR_CREATE(number);\
						instance = timer##number;\
						break

#define Timer8bits2OCR_ISR(number) \
ISR(TIMER##number##_OVF_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(TIMER##number##_OVF_vect_number);\
}\
ISR(TIMER##number##_COMPA_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(TIMER##number##_COMPA_vect_number);\
}\
ISR(TIMER##number##_COMPB_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(TIMER##number##_COMPB_vect_number);\
}


#ifdef Timer8bits2OCR0
	Timer8bits2OCR_ISR(0);
#endif
#ifdef Timer8bits2OCR2
	Timer8bits2OCR_ISR(2);
#endif

Timer8bits2OCR * Timer8bits2OCR::getTimer8bits2OCR(size_t number)
{
	static Timer8bits2OCR * instance;


	switch(number)
	{
#ifdef Timer8bits2OCR0
		Timer8bits2OCR_CASE(0);
#endif
#ifdef Timer8bits2OCR1
		Timer8bits2OCR_CASE(1);
#endif
#ifdef Timer8bits2OCR2
		Timer8bits2OCR_CASE(2);
#endif
	default:	instance = NULL;


	}

	return instance;
}

}

#endif /* Timer8bits2OCRCompatibility_H_ */
