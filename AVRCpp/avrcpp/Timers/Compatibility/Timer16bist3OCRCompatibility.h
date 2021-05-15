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
#ifndef Timer16bits3OCRCompatibility_H_
#define Timer16bits3OCRCompatibility_H_
#include "TimersCompatibility.h"
#include "../../CallbackServers/FastCallbackServer.h"
#include "../Timer16bits3OCR.h"

namespace Timers
{

#define Timer16bits3OCR_CREATE(number) \
	new Timer16bits3OCR(&TCCR##number##A, buildMask(COM##number##A0, COM##number##A1), buildMask(COM##number##B0, COM##number##B1), buildMask(COM##number##C0, COM##number##C1), buildMask(WGM##number##0, WGM##number##1),\
						&TCCR##number##B, buildMask(WGM##number##2, WGM##number##3), buildMask(CS##number##0, CS##number##1, CS##number##2),\
						&TCCR##number##C, \
						&TCNT##number, &OCR##number##A, &OCR##number##B, &OCR##number##C, &ICR##number, \
						&TIMSK##number, TOIE##number, TIMER##number##_OVF_vect_number, OCIE##number##A, TIMER##number##_COMPA_vect_number, OCIE##number##B, TIMER##number##_COMPB_vect_number, OCIE##number##C, TIMER##number##_COMPC_vect_number, ICIE##number, TIMER##number##_CAPT_vect_number,\
						&TIFR##number, TOV##number, OCF##number##A, OCF##number##B, OCF##number##C, ICF##number)

#define Timer16bits3OCR_CASE(number)\
	case number:		static Timer16bits3OCR * timer##number;\
						if(isNull(timer##number))\
							timer##number = Timer16bits3OCR_CREATE(number);\
						instance = timer##number;\
						break

#define Timer16bits3OCR_ISR(number) \
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
}\
ISR(TIMER##number##_COMPC_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(TIMER##number##_COMPC_vect_number);\
}\
ISR(TIMER##number##_CAPT_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(TIMER##number##_CAPT_vect_number);\
}


#ifdef Timer16bits3OCR1
		Timer16bits3OCR_ISR(1);
#endif
#ifdef Timer16bits3OCR3
		Timer16bits3OCR_ISR(3);
#endif
#ifdef Timer16bits3OCR4
		Timer16bits3OCR_ISR(4);
#endif
#ifdef Timer16bits3OCR5
		Timer16bits3OCR_ISR(5);
#endif

Timer16bits3OCR * Timer16bits3OCR::getTimer16bits3OCR(size_t number)
{
	static Timer16bits3OCR * instance;


	switch(number)
	{
#ifdef Timer16bits3OCR1
		Timer16bits3OCR_CASE(1);
#endif
#ifdef Timer16bits3OCR3
		Timer16bits3OCR_CASE(3);
#endif
#ifdef Timer16bits3OCR4
		Timer16bits3OCR_CASE(4);
#endif
#ifdef Timer16bits3OCR5
		Timer16bits3OCR_CASE(5);
#endif
	default:	instance = NULL;


	}

	return instance;
}

}

#endif /* Timer16bits3OCRCompatibility_H_ */
