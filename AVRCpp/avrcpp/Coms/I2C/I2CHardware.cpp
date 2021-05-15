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

#include "Compatibility/I2CHardwareCompatibillity.h"
#include "../../Utils/Utils.h"



#define TWSR_PRESCALER_MASK 	(uint8_t)(~TW_STATUS_MASK)



namespace Coms
{

namespace I2C
{

I2CHardware::I2CHardware(uint8_t callbackVectorNumber, IOAddress twdr, IOAddress twbr, IOAddress twcr, IOAddress twsr, IOAddress twar):
CallbackConnector(callbackVectorNumber), twdr(twdr), twbr(twbr), twcr(twcr), twsr(twsr), twar(twar)
{
	setBitRate();
	setSlaveAddress();
}

I2CHardware::~I2CHardware()
{
	// TODO Auto-generated destructor stub
}


size_t I2CHardware::setBitRate(uint8_t finePrescaler, Prescaler coarsePrescaler)
{
	*twbr = finePrescaler;
	setConfig(twsr,  TWSR_PRESCALER_MASK, coarsePrescaler);

	return F_CPU / (16 - 2 * finePrescaler * pow(4, coarsePrescaler));
}

void I2CHardware::setSlaveAddress(uint8_t address7bit, bool answerGeneralCalls)
{
	*twar = address7bit << 1; //the address occupy the register's MSBits

	if(answerGeneralCalls)
		setBit(*twar, TWGCE);		//answering general calls
}

}

}
