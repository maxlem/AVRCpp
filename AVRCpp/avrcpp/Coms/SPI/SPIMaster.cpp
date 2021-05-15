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

#include "SPIMaster.h"

namespace Coms
{

namespace SPI
{

SPIMaster::SPIMaster(SPIHardware * spiHardware, IOAddress slaveSelectPort, IOAddress slaveSelectDDR, uint8_t slaveSelectPinNumber) :
spiHardware(spiHardware), slaveSelectPort(slaveSelectPort), slaveSelectDDR(slaveSelectDDR), slaveSelectPinNumber(slaveSelectPinNumber)
{
	setBit(*slaveSelectDDR, slaveSelectPinNumber);
	setBit(*slaveSelectPort, slaveSelectPinNumber);
}

SPIMaster::~SPIMaster()
{
	// TODO Auto-generated destructor stub
}


Buffer<uint8_t> & SPIMaster::transmitAndReceive(Buffer<uint8_t> & transmitAndReceiveBuffer)
{
	clearBit(*slaveSelectPort, slaveSelectPinNumber); // pull SS low

	for(size_t i = 0; i < transmitAndReceiveBuffer.numberOfElements; i++)
	{
		spiHardware->writeByte(transmitAndReceiveBuffer.buffer[i]);

		while(!spiHardware->readInterruptFlag());

		transmitAndReceiveBuffer.buffer[i] = spiHardware->readByte();
	}

	setBit(*slaveSelectPort, slaveSelectPinNumber); // pull SS high

	return transmitAndReceiveBuffer;
}

}

}
