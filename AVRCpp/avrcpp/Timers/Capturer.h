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

#ifndef Capturer_H_
#define Capturer_H_

#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "../CallbackServers/CallbackConnector.h"

namespace Timers
{

class Capturer16 : public CallbackConnector
{
public:
	Capturer16(uint8_t callbackVectorNumber, IOAddress16 icr, IOAddress tccrb, IOAddress timsk, uint8_t icie, IOAddress tifr, uint8_t icf);

	virtual ~Capturer16();

	inline void setICRValue(uint16_t value) FORCE_INLINE;
	inline uint16_t readICR() FORCE_INLINE;

	inline void enableNoiseCanceler() FORCE_INLINE;
	inline void disableNoiseCanceler() FORCE_INLINE;

	inline void triggerOnRisingEdge() FORCE_INLINE;
	inline void triggerOnFallingEdge() FORCE_INLINE;

	inline void enableICRInterrupts() FORCE_INLINE;
	inline void disableICRInterrupts() FORCE_INLINE;
	inline bool readICRFlag() FORCE_INLINE;
	inline void clearICRFlag() FORCE_INLINE;

protected:
	IOAddress16 icr;
	IOAddress tccrb;
	IOAddress timsk;
	uint8_t icie;
	IOAddress tifr;
	uint8_t icf;
};


void Capturer16::setICRValue(uint16_t value)
{
	*icr = value;
}

uint16_t Capturer16::readICR()
{
	return *icr;
}

void Capturer16::enableNoiseCanceler()
{
	setBit(*tccrb, ICNC1);

}
void Capturer16::disableNoiseCanceler()
{
	clearBit(*tccrb, ICNC1);
}

void Capturer16::triggerOnRisingEdge()
{
	setBit(*tccrb, ICES1);
}

void Capturer16::triggerOnFallingEdge()
{
	clearBit(*tccrb, ICES1);
}

void Capturer16::enableICRInterrupts()
{

	setBit(*timsk, icie);

}
void Capturer16::disableICRInterrupts()
{
	clearBit(*timsk, icie);
}

bool Capturer16::readICRFlag()
{
	return bitIsSetInRegister(*tifr, icf);
}

void Capturer16::clearICRFlag()
{
	setBit(*tifr, icf);
}

}

#endif /* Capturer_H_ */
