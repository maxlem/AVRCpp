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

#ifndef SPIHardware_H_
#define SPIHardware_H_

#include "../../Utils/CppExtensions.h"
#include "../../Utils/BitManipulation.h"
#include "../../CallbackServers/CallbackConnector.h"
#include "Compatibility/SPIHardwareCompatibilityInterface.h"

namespace Coms
{

namespace SPI
{

namespace Prescalers
{

enum Prescaler
{
	DIV_4 = 0x00,
	DIV_16 = 0x01,
	DIV_64 = 0x02,
	DIV_128 = 0x03
};

}

using Prescalers::Prescaler;

class SPIHardware : public CallbackConnector
{

public:

	static SPIHardware * getSPIHardware(size_t number);

	virtual ~SPIHardware();

	inline void enable() FORCE_INLINE;

	inline void disable() FORCE_INLINE;

	inline void enableInterrupts() FORCE_INLINE;

	inline void disableInterrupts() FORCE_INLINE;

	inline bool readInterruptFlag() FORCE_INLINE;

	inline void clearInterruptFlag() FORCE_INLINE;

	inline void transmitLSBFirst() FORCE_INLINE;

	inline void transmitMSBFirst() FORCE_INLINE;

	inline void setMaster() FORCE_INLINE;

	inline void setSlave() FORCE_INLINE;

	inline void setSPIPinsDirections(DataDirection slaveSelectPinDirection = INPUT, DataDirection sckPinDirection = OUTPUT, DataDirection mosiPinDirection = OUTPUT, DataDirection misoPinDirection = OUTPUT) FORCE_INLINE;

	inline void setSCKHighWhenIdle() FORCE_INLINE;

	inline void setSCKLowWhenIdle() FORCE_INLINE;

	inline void sampleDataOnSCKLeadingEdge() FORCE_INLINE;

	inline void sampleDataOnSCKTrailingEdge() FORCE_INLINE;

	inline void setPrescaler(Prescaler prescaler, bool doubleBitRate) FORCE_INLINE;

	inline bool checkWriteCollision() FORCE_INLINE;

	inline uint8_t readByte() FORCE_INLINE;

	inline void writeByte(uint8_t byte) FORCE_INLINE;

protected:

	SPIHardware(uint8_t callbackVectorNumber, IOAddress spcr, IOAddress spsr, IOAddress spdr, IOAddress spiDDR, uint8_t ssPinNumber, uint8_t sckPinNumber, uint8_t mosiPinNumber, uint8_t misoPinNumber);

	IOAddress spcr;
	IOAddress spsr;
	IOAddress spdr;

	IOAddress spiDDR;
	uint8_t ssPinNumber;
	uint8_t sckPinNumber;
	uint8_t mosiPinNumber;
	uint8_t misoPinNumber;

};

#include "SPIHardware-definitions.h"

}

}

#endif /* SPIHardware_H_ */
