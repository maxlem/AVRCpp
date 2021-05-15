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

#define USI_COUNTER_MASK 0x0F	//0b00001111
#define USI_CLOCK_SOURCE_MASK 0x0C //0b00001100
bool USIHardware::readStartConditionInterruptFlag()
{
	return bitIsSetInRegister(*usisr, USISIF);

}
void USIHardware::clearStartConditionInterruptFlag()
{
	setBit(*usisr, USISIF);
}

void USIHardware::enableStartConditionInterrupts()
{
	setBit(*usicr, USISIE);
}

void USIHardware::disableStartConditionInterrupts()
{
	clearBit(*usicr, USISIE);
}

bool USIHardware::readCounterOverflowInterruptFlag()
{
	return bitIsSetInRegister(*usisr, USIOIF);
}

void USIHardware::clearCounterOverflowInterruptFlag()
{
	setBit(*usisr, USIOIF);
}

void USIHardware::enableCounterOverflowInterrupts()
{
	setBit(*usicr, USIOIE);
}

void USIHardware::disableCounterOverflowInterrupts()
{
	clearBit(*usicr, USIOIE);
}
bool USIHardware::readStopConditionFlag()
{
	return bitIsSetInRegister(*usisr, USISIF);
}

void USIHardware::clearStopConditionFlag()
{
	setBit(*usisr, USIPF);
}

bool USIHardware::readWriteCollisionFlag()
{
	return bitIsSetInRegister(*usisr, USISIF);
}
uint8_t USIHardware::readCounterValue()
{
	return *usisr & USI_COUNTER_MASK;
}
void USIHardware::disable()
{
	clear2Bits(*usicr, USIWM1, USIWM0);

}
void USIHardware::enableInSPIMode()
{
	clearBit(*usicr, USIWM1);
	setBit(*usicr, USIWM0);
}

void USIHardware::enableInI2CMode()
{
	setBit(*usicr, USIWM1);
	setBit(*usicr, USIWM0);
}

void USIHardware::setClockSourceMode(ClockSource clockSource)
{
	*usicr |= USI_CLOCK_SOURCE_MASK & clockSource << 2;

}
void USIHardware::setClockStrobe()
{
	setBit(*usicr, USICLK);

}
void USIHardware::clearClockStrobe()
{
	clearBit(*usicr, USICLK);
}
void USIHardware::toggleClock()
{
	setBit(*usicr, USITC);
}

uint8_t USIHardware::readByte()
{
	return *usibr;
}

void USIHardware::writeByte(uint8_t byte)
{
	*usidr = byte;
}
