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

#ifndef I2CMaster_H_
#define I2CMaster_H_

#include "I2CHardware.h"
#include "../../DataStructures/ActiveBuffers/ActiveReceiveBuffers/ActiveReceiveBuffer.h"
#include "../../DataStructures/ActiveBuffers/ActiveReceiveBuffers/ActiveReceiveBufferObserver.h"
#include "../../DataStructures/ActiveBuffers/ActiveTransmitBuffers/ActiveTransmitBuffer.h"
#include "../../DataStructures/ActiveBuffers/ActiveTransmitBuffers/ActiveTransmitBufferObserver.h"

namespace Coms
{

namespace I2C
{

class I2CMaster
{
public:
	I2CMaster(I2CHardware * i2cHardware);
	virtual ~I2CMaster();

	void setDestinationAddress(uint8_t destinationAddress);

	uint8_t readRegister(uint8_t registerAddress);
	void writeRegister(uint8_t registerAddress, uint8_t registerContent);

	void readRegisters(uint8_t startRegisterAddress, ActiveReceiveBuffer * receiveBuffer);
	void writeRegisters(uint8_t startRegisterAddress, ActiveTransmitBuffer * transmitBuffer);

	void writeRegistersAM(uint8_t registerAddress, uint8_t *RegisterBuf, uint32_t BufSizeByte);

protected:
	bool selectRegister(uint8_t registerAddress);

protected:

	I2CHardware * i2cHardware;

	uint8_t destinationAddress;
};

}

}

#endif /* I2CMaster_H_ */
