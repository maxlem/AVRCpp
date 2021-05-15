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

#ifndef Counter_H_
#define Counter_H_
#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "../CallbackServers/CallbackConnector.h"
#include "Prescalers.h"
#include "TimerOutputCompareModes.h"
#include "TimerWaveGenerationModes.h"

namespace Timers
{

using Prescalers::Prescaler;

using WaveGenerationModes::WaveGenerationMode4bits;

template <typename IOAddressType, typename uint_t>
class Counter : public CallbackConnector
{
public :

	Counter(uint8_t callbackVectorNumber, IOAddressType tcnt, IOAddress tccrb, uint8_t csMask, IOAddress timsk, uint8_t toie, IOAddress tifr, uint8_t tov);
	inline void setPrescaler(Prescaler prescaler) const FORCE_INLINE;
	inline uint_t read() const FORCE_INLINE;
	inline void setValue(uint_t value) const FORCE_INLINE;

	inline void enableOVFInterrupts() const FORCE_INLINE;
	inline void disableOVFInterrupts() const FORCE_INLINE;
	inline bool readOVFFlag() const FORCE_INLINE;
	inline void clearOVFFlag() const FORCE_INLINE;

protected :

	IOAddressType tcnt;
	IOAddress tccrb;
	uint8_t csMask;
	IOAddress timsk;
	uint8_t toie;
	IOAddress tifr;
	uint8_t tov;
};

typedef Counter<IOAddress, uint8_t> Counter8;
typedef Counter<IOAddress16, uint16_t> Counter16;

template <typename IOAddressType, typename uint_t>
void Counter<IOAddressType, uint_t>::setPrescaler(Prescaler prescaler) const
{
	setConfig(tccrb, csMask, prescaler);
}

template <typename IOAddressType, typename uint_t>
uint_t Counter<IOAddressType, uint_t>::read() const
{
	return *tcnt;
}

template <typename IOAddressType, typename uint_t>
void Counter<IOAddressType, uint_t>::setValue(uint_t value) const
{
	*tcnt = value;
}

template <typename IOAddressType, typename uint_t>
void Counter<IOAddressType, uint_t>::enableOVFInterrupts() const
{
	setBit(*timsk, toie);
}

template <typename IOAddressType, typename uint_t>
void Counter<IOAddressType, uint_t>::disableOVFInterrupts() const
{
	clearBit(*timsk, toie);
}

template <typename IOAddressType, typename uint_t>
bool Counter<IOAddressType, uint_t>::readOVFFlag() const
{
	return bitIsSetInRegister(*tifr, tov);
}

template <typename IOAddressType, typename uint_t>
void Counter<IOAddressType, uint_t>::clearOVFFlag() const
{
	setBit(*tifr, tov);
}

}

#endif /* Counter_H_ */
