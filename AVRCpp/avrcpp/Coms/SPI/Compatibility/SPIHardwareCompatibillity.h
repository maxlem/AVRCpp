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

#ifndef SPIHardwareCompatibillity_H_
#define SPIHardwareCompatibillity_H_
#include "../SPIHardware.h"
#include <avr/interrupt.h>
#include "../../../CallbackServers/FastCallbackServer.h"


ISR(SPI_STC_vect)
{
	FastCallbackServer::getInstance()->dispatch(SPI_STC_vect_number);
}

namespace Coms
{

namespace SPI
{

SPIHardware * SPIHardware::getSPIHardware(size_t number)
{
	static SPIHardware * instance;

	if(isNull(instance))
		instance = new SPIHardware(SPI_STC_vect_number, &SPCR, &SPSR, &SPDR, &SPI_DDR, SPI_SS_PIN, SPI_SCK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN);

	return instance;

}

}

}


#endif /* SPIHardwareCompatibillity_H_ */
