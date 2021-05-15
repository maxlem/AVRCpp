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

#ifndef Timer16bits2OCR_H_
#define Timer16bits2OCR_H_

#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "Prescalers.h"
#include "TimerOutputCompareModes.h"
#include "TimerWaveGenerationModes.h"
#include "Counter.h"
#include "Comparator.h"
#include "Capturer.h"

namespace Timers
{

class Timer16bits2OCR
{

public:

	virtual ~Timer16bits2OCR();

	static Timer16bits2OCR * getTimer16bits2OCR(size_t number);

	inline void setWaveGenerationMode(uint8_t wgm3, uint8_t wgm2, uint8_t wgm1, uint8_t wgm0) FORCE_INLINE;

	inline Counter16 * getCounter() FORCE_INLINE;

	inline Comparator16 * getComparatorA() FORCE_INLINE;

	inline Comparator16 * getComparatorB() FORCE_INLINE;

	inline Capturer16 * getCapturer() FORCE_INLINE;

protected:

	Timer16bits2OCR(IOAddress tccra, uint8_t comaMask, uint8_t combMask, uint8_t wgmLSBMask,
			IOAddress tccrb, uint8_t wgmMSBMask, uint8_t csMask,
			IOAddress tccrc,
			IOAddress16 tcnt, IOAddress16 ocra, IOAddress16 ocrb, IOAddress16 icr,
			IOAddress timsk, uint8_t toie, uint8_t toieCallbackVectorNumber, uint8_t ociea, uint8_t ocieaCallbackVectorNumber, uint8_t ocieb, uint8_t ociebCallbackVectorNumber, uint8_t icie, uint8_t icieCallbackVectorNumber,
			IOAddress tifr, uint8_t tov, uint8_t ocfa, uint8_t ocfb, uint8_t icf);




	IOAddress tccra;
	IOAddress tccrb;
	IOAddress tccrc;

	IOAddress16 icr;

	IOAddress timsk;
	uint8_t icie;

	IOAddress tifr;
	uint8_t icf;

	Counter16 counter;

	Comparator16 comparatorA;
	Comparator16 comparatorB;

	Capturer16 capturer;
};

#include "Timer16bits2OCR-definitions.h"

}

#endif /* Timer16bits2OCR_H_ */
