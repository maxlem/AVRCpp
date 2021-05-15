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

#ifndef Comparator_H_
#define Comparator_H_

#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "../CallbackServers/CallbackConnector.h"
#include "TimerOutputCompareModes.h"

namespace Timers
{
using CompareModes::CompareMode;

template <typename IOAddressType, typename uint_t>
class Comparator :  public CallbackConnector
{
public:
	Comparator(uint8_t callbackVectorNumber, IOAddressType ocr, IOAddress tccra, uint8_t comMask, IOAddress timsk, uint8_t ocie, IOAddress tifr, uint8_t ocf);
	virtual ~Comparator();

	inline void setOCRValue(uint_t value) const FORCE_INLINE;
	inline void setOCROutputPinMode(CompareMode mode) const FORCE_INLINE;
	inline void enableOCRInterrupts() const FORCE_INLINE;
	inline void disableOCRInterrupts() const FORCE_INLINE;
	inline bool readOCRFlag() const FORCE_INLINE;
	inline void clearOCRFlag() const FORCE_INLINE;

protected:
	IOAddressType ocr;
	IOAddress tccra;
	uint8_t comMask;
	IOAddress timsk;
	uint8_t ocie;
	IOAddress tifr;
	uint8_t ocf;
};

typedef Comparator<IOAddress, uint8_t> Comparator8;

typedef Comparator<IOAddress16, uint16_t> Comparator16;

template <typename IOAddressType, typename uint_t>
void Comparator<IOAddressType, uint_t>::setOCRValue(uint_t value) const
{
	*ocr = value;
}

template <typename IOAddressType, typename uint_t>
void Comparator<IOAddressType, uint_t>::setOCROutputPinMode(CompareMode mode) const
{
	setConfig(tccra, comMask, mode);
}

template <typename IOAddressType, typename uint_t>
void Comparator<IOAddressType, uint_t>::enableOCRInterrupts() const
{
	setBit(*timsk, ocie);
}

template <typename IOAddressType, typename uint_t>
void Comparator<IOAddressType, uint_t>::disableOCRInterrupts() const
{
	clearBit(*timsk, ocie);
}

template <typename IOAddressType, typename uint_t>
bool Comparator<IOAddressType, uint_t>::readOCRFlag() const
{
	return bitIsSetInRegister(*tifr, ocf);
}

template <typename IOAddressType, typename uint_t>
void Comparator<IOAddressType, uint_t>::clearOCRFlag() const
{
	setBit(*tifr, ocf);
}

}

#endif /* Comparator_H_ */
