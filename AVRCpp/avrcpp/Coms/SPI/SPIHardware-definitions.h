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

void SPIHardware::enable()
{
	setBit(*spcr, SPE);
}
void SPIHardware::disable()
{
	clearBit(*spcr, SPE);
}

void SPIHardware::enableInterrupts()
{
	setBit(*spcr, SPIE);
}

void SPIHardware::disableInterrupts()
{
	clearBit(*spcr, SPIE);
}

bool SPIHardware::readInterruptFlag()
{
	return bitIsSetInRegister(*spsr, SPIF);
}

void SPIHardware::clearInterruptFlag()
{
	setBit(*spsr, SPIF);
}

void SPIHardware::transmitLSBFirst()
{
	setBit(*spcr, DORD);
}
void SPIHardware::transmitMSBFirst()
{
	clearBit(*spcr, DORD);
}
void SPIHardware::setMaster()
{
	setBit(*spcr, MSTR);
}
void SPIHardware::setSlave()
{
	clearBit(*spcr, MSTR);
}

void SPIHardware::setSPIPinsDirections(DataDirection slaveSelectPinDirection, DataDirection sckPinDirection, DataDirection mosiPinDirection, DataDirection misoPinDirection)
{
	changeBitValueTo(*spiDDR, ssPinNumber, slaveSelectPinDirection);
	changeBitValueTo(*spiDDR, sckPinNumber, sckPinDirection);
	changeBitValueTo(*spiDDR, mosiPinNumber, mosiPinDirection);
	changeBitValueTo(*spiDDR, misoPinNumber, misoPinDirection);
}
void SPIHardware::setSCKHighWhenIdle()
{
	setBit(*spcr, CPOL);
}
void SPIHardware::setSCKLowWhenIdle()
{
	clearBit(*spcr, CPOL);
}
void SPIHardware::sampleDataOnSCKLeadingEdge()
{
	setBit(*spcr, CPHA);
}
void SPIHardware::sampleDataOnSCKTrailingEdge()
{
	clearBit(*spcr, CPHA);
}
void SPIHardware::setPrescaler(Prescaler prescaler, bool doubleBitRate)
{
	applyMaskedConfig(*spcr, 0x03, prescaler);

	changeBitValueTo(*spsr, SPI2X, doubleBitRate);

}
bool SPIHardware::checkWriteCollision()
{
	return bitIsSetInRegister(*spsr, WCOL);
}
uint8_t SPIHardware::readByte()
{
	return *spdr;
}
void SPIHardware::writeByte(uint8_t byte)
{
	*spdr = byte;
}
