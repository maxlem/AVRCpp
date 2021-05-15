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

#ifndef Timer8bits2OCR_H_
#define Timer8bits2OCR_H_

//#include "../Utils/CppExtensions.h"
//#include "../Utils/BitManipulation.h"
#include "Prescalers.h"
#include "TimerOutputCompareModes.h"
#include "TimerWaveGenerationModes.h"
#include "Counter.h"
#include "Comparator.h"

namespace Timers
{

class Timer8bits2OCR
{
public:
	virtual ~Timer8bits2OCR();

	static Timer8bits2OCR * getTimer8bits2OCR(size_t number);

	inline void setWaveGenerationMode(uint8_t wgm2, uint8_t wgm1, uint8_t wgm0) FORCE_INLINE;

	inline Counter8 * getCounter() FORCE_INLINE;

	inline Comparator8 * getComparatorA() FORCE_INLINE;

	inline Comparator8 * getComparatorB() FORCE_INLINE;

protected:

	Timer8bits2OCR(IOAddress tccra, uint8_t comaMask, uint8_t combMask, uint8_t wgmLSBMask,
			IOAddress tccrb, uint8_t wgmMSB, uint8_t csMask,
			IOAddress tcnt, IOAddress ocra, IOAddress ocrb,
			IOAddress timsk, uint8_t toie, uint8_t toieCallbackVectorNumber, uint8_t ociea, uint8_t ocieaCallbackVectorNumber, uint8_t ocieb, uint8_t ociebCallbackVectorNumber,
			IOAddress tifr, uint8_t tov, uint8_t ocfa, uint8_t ocfb);




	IOAddress tccra;
	IOAddress tccrb;

	IOAddress timsk;
	uint8_t icie;

	IOAddress tifr;
	uint8_t icf;

	Counter8 counter;

	Comparator8 comparatorA;
	Comparator8 comparatorB;
};

#include "Timer8bits2OCR-definitions.h"

}

#endif /* Timer8bits2OCR_H_ */
