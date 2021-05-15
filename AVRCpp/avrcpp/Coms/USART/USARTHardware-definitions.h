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


void USARTHardware::configureBitRate(uint16_t finePrescaler, bool doubleBitRate, bool synchroneous)
{
	#ifdef URSEL
	// USREL must be selected simultaneously with other bits since UCSRC shares IO address with UBRRH
	clearBit(*ucsrc, URSEL);
	#endif

	finePrescaler &= 0x0FFF;

	*ubrrl = (uint8_t)finePrescaler;
	*ubrrh = (uint8_t)(finePrescaler>>8);

	changeBitValueTo(*ucsra, U2X, doubleBitRate);

	changeBitValueTo(*ucsrc, UMSEL, synchroneous);
}

void USARTHardware::configureFrameSize(FrameSize dataBits)
{

	#ifdef URSEL
	// USREL must be selected simultaneously with other bits since UCSRC shares IO address with UBRRH
	setBit(*ucsrc, URSEL);
	#endif

	setConfig(ucsrc, buildMask(UCSZ0, UCSZ1), dataBits);

	changeBitValueTo(*ucsrb, UCSZ2, dataBits == FrameSizes::NINE_BITS);
}

void USARTHardware::configureStopBitsMode(StopBitsMode stopBits)
{

	#ifdef URSEL
	// USREL must be selected simultaneously with other bits since UCSRC shares IO address with UBRRH
	setBit(*ucsrc, URSEL);
	#endif

	setConfig(ucsrc, buildMask(USBS), stopBits);

}

void USARTHardware::configureParityMode(ParityMode parity)
{

	#ifdef URSEL
	// USREL must be selected simultaneously with other bits since UCSRC shares IO address with UBRRH
	setBit(*ucsrc, URSEL);
	#endif

	setConfig(ucsrc, buildMask(UPM0, UPM1), parity);

}

void USARTHardware::enableMPCM()
{
	setConfig(ucsra, buildMask(MPCM), 0x01);
}

void USARTHardware::disableMPCM()
{
	setConfig(ucsra, buildMask(MPCM), 0x00);
}

void USARTHardware::configureDefaults()
{
	configureBitRate();
	configureFrameSize();
	configureStopBitsMode();
	configureParityMode();
}

void USARTHardware::enableReceiver()
{
	setBit(*ucsrb, RXEN);
}

void USARTHardware::disableReceiver()
{
	clearBit(*ucsrb, RXEN);
}

void USARTHardware::enableFrameReceivedInterrupts()
{
	setBit(*ucsrb, RXCIE);
}

void USARTHardware::disableFrameReceivedInterrupts()
{
	clearBit(*ucsrb, RXCIE);
}

uint16_t USARTHardware::readFrame()
{

	if(bitIsSetInRegister(*ucsrb, RXB8))
		return *udr + USART_NINTH_BIT_MASK;

	return *udr;
}

bool USARTHardware::isFrameReceived()
{
	return bitIsSetInRegister(*ucsra, RXC);
}


void USARTHardware::clearFrameReceivedFlag()
{
	setBit(*ucsra, RXC);
}

void USARTHardware::enableTransmitter()
{
	setBit(*ucsrb, TXEN);
}

void USARTHardware::disableTransmitter()
{
	clearBit(*ucsrb, TXEN);
}

void USARTHardware::enableTransmitterReadyInterrupts()
{
	setBit(*ucsrb, UDRIE);
}

void USARTHardware::disableTransmitterReadyInterrupts()
{
	clearBit(*ucsrb, UDRIE);
}

void USARTHardware::writeFrame(uint16_t data)
{

	changeBitValueTo(*ucsrb, TXB8, data & USART_NINTH_BIT_MASK);

	*udr = (uint8_t)data;
}

bool USARTHardware::isTransmitterReady()
{
	return bitIsSetInRegister(*ucsra, UDRE);
}

bool USARTHardware::isFrameTransmitted()
{
	return bitIsSetInRegister(*ucsra, TXC);
}

void USARTHardware::clearFrameTransmittedFlag()
{
	setBit(*ucsra, TXC);
}

void USARTHardware::enableFrameTransmittedInterrupts()
{
	setBit(*ucsra, TXCIE);
}

void USARTHardware::disableFrameTransmittedInterrupts()
{
	clearBit(*ucsra, TXCIE);
}

uint8_t USARTHardware::status()
{
	return *ucsra & USART_UCSRA_STATUS_MASK;
}
