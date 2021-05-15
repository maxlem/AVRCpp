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

#ifndef USIHardware_H_
#define USIHardware_H_
#include "../../Utils/CppExtensions.h"
#include "../../Utils/BitManipulation.h"


namespace Coms
{

namespace USI
{

namespace ClockSources
{

enum ClockSource
{
	SOFTWARE = 0x00,
	TIMER_OC_PIN = 0x01,
	EXTERNAL_POSITIVE_EDGE = 0x02,
	EXTERNAL_NEGATIVE_EDGE = 0x03,
};

}



using ClockSources::ClockSource;


class USIHardware
{
public:
	static USIHardware * getUSIHardware();
	virtual ~USIHardware();

	inline bool readStartConditionInterruptFlag() FORCE_INLINE;
	inline void clearStartConditionInterruptFlag() FORCE_INLINE;
	inline void enableStartConditionInterrupts() FORCE_INLINE;
	inline void disableStartConditionInterrupts() FORCE_INLINE;

	inline bool readCounterOverflowInterruptFlag() FORCE_INLINE;
	inline void clearCounterOverflowInterruptFlag() FORCE_INLINE;
	inline void enableCounterOverflowInterrupts() FORCE_INLINE;
	inline void disableCounterOverflowInterrupts() FORCE_INLINE;

	inline bool readStopConditionFlag() FORCE_INLINE;
	inline void clearStopConditionFlag() FORCE_INLINE;

	inline bool readWriteCollisionFlag() FORCE_INLINE;

	inline uint8_t readCounterValue() FORCE_INLINE;

	inline void disable() FORCE_INLINE;
	inline void enableInSPIMode() FORCE_INLINE;
	inline void enableInI2CMode() FORCE_INLINE;

	inline void setClockSourceMode(ClockSource clockSource) FORCE_INLINE;

	inline void setClockStrobe() FORCE_INLINE;
	inline void clearClockStrobe() FORCE_INLINE;

	inline void toggleClock() FORCE_INLINE;

	inline uint8_t readByte() FORCE_INLINE;

	inline void writeByte(uint8_t byte) FORCE_INLINE;



protected:

	USIHardware(uint8_t callbackVectorNumber, IOAddress usidr, IOAddress usibr, IOAddress usisr, IOAddress usicr);


	uint8_t callbackVectorNumber;
	IOAddress usidr;
	IOAddress usibr;
	IOAddress usisr;
	IOAddress usicr;

};

#include "USIHardware-definition.h"

}

}

#endif /* USIHardware_H_ */
