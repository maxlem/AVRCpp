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

#ifndef I2CHardwareCompatibillity_H_
#define I2CHardwareCompatibillity_H_
#include "../I2CHardware.h"
#include <avr/interrupt.h>
#include "../../../CallbackServers/FastCallbackServer.h"


#define I2C_CREATE(number) \
	new I2CHardware(TWI##number##_vect_number, &TW##number##DR, &TW##number##BR, &TW##number##CR, &TW##number##SR, &TW##number##AR)

#define I2C_CASE(number)\
	case number:		static I2CHardware * i2c##number = NULL;\
						if(isNull(i2c##number))\
							i2c##number = I2C_CREATE(number);\
						instance = i2c##number;\
						break


#define I2C_ISR(number)\
ISR(TWI##number##_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(TWI##number##_vect_number);\
}\


#ifdef I2C0
				I2C_ISR(0);
#endif

namespace Coms
{

namespace I2C
{

I2CHardware* I2CHardware::getInstance(size_t number)
{
	static I2CHardware* instance = NULL;

	switch(number)
	{
#ifdef I2C0
				I2C_CASE(0);
#endif
#ifdef I2C1
				I2C_CASE(1);
#endif

	default:	instance = NULL;
	}

	return instance;
}

}

}


#endif /* I2CHardwareCompatibillity_H_ */
