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

#ifndef SPIMasterTest_H_
#define SPIMasterTest_H_

#include "TestCase.h"
#include "Coms/SPI/SPIMaster.h"
#include <stdio.h>
#include <math.h>

using Coms::SPI::SPIMaster;
using Coms::SPI::SPIHardware;

#define READ_MARGIN 10

class SPIMasterTest : public TestCase<SPIMasterTest>
{
public:

	SPIMasterTest(const prog_mem * testMethodName_P, TestCase<SPIMasterTest>::TestMethod testMethod) :
	TestCase<SPIMasterTest>(testMethodName_P, testMethod)
	{

//		DDRB = (1<<PINB0) | (1<<PINB1) | (1<<PINB2); // set SCK and MOSI as output

		spiHardware = SPIHardware::getSPIHardware(0);
		spiHardware->setPrescaler(Coms::SPI::Prescalers::DIV_128, false);
		spiHardware->setSPIPinsDirections(OUTPUT, OUTPUT, OUTPUT, OUTPUT);
		spiHardware->setMaster();
		spiHardware->transmitMSBFirst();
		spiHardware->enable();


		spiMaster = new SPIMaster(spiHardware, &PORTC, &DDRC, PINC0);

	}

	void setUp()
	{
	}

	void tearDown()
	{
		spiHardware->disable();
	}

	bool testSCA3000()
	{
		while(true)
		{

		uint8_t data[] = {0x09<<2,0,0,0,0,0,0};

		Buffer<uint8_t> transmitAndReceiveBuffer(7, data);

		spiMaster->transmitAndReceive(transmitAndReceiveBuffer);

		int16_t z = data[1] << 8;

		z += data[2] & 0xF8;

		printf("z = %i  status = %x    \r", 3*z/32, data[0]);

		delay(50);
		}



//		return result;

	}

	SPIMaster * spiMaster;
	SPIHardware * spiHardware;

};

#endif /* SPIMasterTest_H_ */
