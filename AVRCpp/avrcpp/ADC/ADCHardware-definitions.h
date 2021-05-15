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

#define 	ADC_REFERENCE_MASK	0xC0
#define 	ADC_PRESCALE_MASK	0x07
#define 	ADC_MUX_MASK		0x1F
#define		ADC_10_BITS_MAX		1023.0f
#define		POWER_UP_ADC_CYCLES		25
#define		CONVERSION_ADC_CYCLES 	13

uint16_t ADCHardware::read()
{
	return *adc;
}

void ADCHardware::enableADC()
{
	setBit(*adcsra, ADEN);
}

void ADCHardware::disableADC()
{
	clearBit(*adcsra, ADEN);
}

void ADCHardware::enableAutoTriggering()
{
	setBit(*adcsra, ADATE);
}

void ADCHardware::disableAutoTriggering()
{
	clearBit(*adcsra, ADATE);
}

void ADCHardware::enableInterrupts()
{
	setBit(*adcsra, ADIE);
}

void ADCHardware::disableInterrupts()
{
	clearBit(*adcsra, ADIE);
}

bool ADCHardware::isConversionComplete()
{
	return bitIsSetInRegister(*adcsra, ADIF);
}

void ADCHardware::clearConversionCompleteFlag()
{
	setBit(*adcsra, ADIF);
}

void ADCHardware::setPrescaler(Prescaler prescaler)
{
	setConfig(adcsra, ADC_PRESCALE_MASK, prescaler);

}

void ADCHardware::setVoltageReference(VoltageReference voltageReference)
{
	setConfig(admux, ADC_REFERENCE_MASK, voltageReference);
}

void ADCHardware::setChannelMode(ChannelMode channelMode)
{
	setConfig(admux, ADC_MUX_MASK, channelMode);
}

void ADCHardware::leftAdjust()
{
	setBit(*admux, ADLAR);
}

void ADCHardware::rightAdjust()
{
	clearBit(*admux, ADLAR);
}

void ADCHardware::startConverter()
{
	setBit(*adcsra, ADSC); 					// start conversion
}

bool ADCHardware::isBusy()
{
	return bitIsSetInRegister(*adcsra, ADSC);
}



