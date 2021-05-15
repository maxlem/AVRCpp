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

#ifndef SCA3000Test_H_
#define SCA3000Test_H_

#include "TestCase.h"
#include "Coms/SPI/SPIMaster.h"
#include "Sensors/SCA3000.h"
#include <stdio.h>
#include <math.h>

using Coms::SPI::SPIMaster;
using Coms::SPI::SPIHardware;

#define READ_MARGIN 10

class SCA3000Test : public TestCase<SCA3000Test>
{
public:

	SCA3000Test(const prog_mem * testMethodName_P, TestCase<SCA3000Test>::TestMethod testMethod) :
	TestCase<SCA3000Test>(testMethodName_P, testMethod)
	{

//		DDRB = (1<<PINB0) | (1<<PINB1) | (1<<PINB2); // set SCK and MOSI as output

		spiHardware = SPIHardware::getSPIHardware(0);
		spiHardware->setPrescaler(Coms::SPI::Prescalers::DIV_128, false);
		spiHardware->setSPIPinsDirections(OUTPUT, OUTPUT, OUTPUT, OUTPUT);
		spiHardware->setMaster();
		spiHardware->transmitMSBFirst();
		spiHardware->enable();


		spiMaster = new SPIMaster(spiHardware, &PORTC, &DDRC, PINC0);
		sca3000x = new SCA3000(spiMaster, 0x05);
		sca3000y = new SCA3000(spiMaster, 0x07);
		sca3000z = new SCA3000(spiMaster, 0x09);

	}

	void setUp()
	{
		enableInterrupts();
	}

	void tearDown()
	{
		disableInterrupts();
		spiHardware->disable();
	}

	bool testRead()
	{

		bool result = AVRUNIT_ASSERT_IN_RANGE_LONG(3*(int)sca3000y->read().serialize().buffer/32, 0, 50);
		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(3*(int)sca3000y->read().serialize().buffer/32, 0, 50);
		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(3*(int)sca3000z->read().serialize().buffer/32, -1000, 50);

		return result;

	}

	SPIMaster * spiMaster;
	SPIHardware * spiHardware;
	SCA3000 * sca3000x;
	SCA3000 * sca3000y;
	SCA3000 * sca3000z;

};
#endif /* SCA3000Test_H_ */
