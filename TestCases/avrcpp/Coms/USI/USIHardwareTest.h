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

#ifndef USIHardwareTest_H_
#define USIHardwareTest_H_

#include "TestCase.h"
#include "Coms/USI/USIHardware.h"
#include <stdio.h>
#include <math.h>

using Coms::USI::USIHardware;

#define READ_MARGIN 10

class USIHardwareTest : public TestCase<USIHardwareTest>
{
public:

	USIHardwareTest(const prog_mem * testMethodName_P, TestCase<USIHardwareTest>::TestMethod testMethod) :
	TestCase<USIHardwareTest>(testMethodName_P, testMethod)
	{

		usiHardware = USIHardware::getUSIHardware();

	}

	void setUp()
	{
	}

	void tearDown()
	{
		usiHardware->disable();
	}

	bool testgetUSIHardware()
	{
		return AVRUNIT_ASSERT(!isNull(usiHardware));
	}

	bool testMCP41050()
	{
//		setBit(DDRC, PINC0); //PINC0 is SS, set it as output
//		setBit(PORTC, PINC0); // pull SS high
//
//		DDRB = (1<<PINB0) | (1<<PINB1) | (1<<PINB2); // set SCK and MOSI as output
//
//		setBit(PORTB, PINB0);
//
//		usiHardware->setPrescaler(Coms::SPI::Prescalers::DIV_128, false);
//		usiHardware->setMaster();
//		usiHardware->setSCKHighWhenIdle();
//		usiHardware->sampleDataOnSCKLeadingEdge();
//		usiHardware->transmitMSBFirst();

		usiHardware->enableInSPIMode();


		uint8_t potValue = 0x00;

		while(true)
		{
//		clearBit(PORTC, PINC0); // pull SS low
//
//		usiHardware->writeByte(0x17);
//
//		while(!usiHardware->readInterruptFlag());
//
//		usiHardware->clearInterruptFlag();
//
//		usiHardware->writeByte(potValue);
//
//		while(!usiHardware->readInterruptFlag());
//
//		usiHardware->clearInterruptFlag();
//
//
//		setBit(PORTC, PINC0); // pull SS high

		potValue++;

		}



//		return result;

	}

	USIHardware * usiHardware;

};

#endif /* USIHardwareTest_H_ */
