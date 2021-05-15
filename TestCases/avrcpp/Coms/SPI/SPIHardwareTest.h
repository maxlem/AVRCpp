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

#ifndef SPIHardwareTest_H_
#define SPIHardwareTest_H_

#include "TestCase.h"
#include "Coms/SPI/SPIHardware.h"
#include <stdio.h>
#include <math.h>
using Coms::SPI::SPIHardware;

#define READ_MARGIN 10

class SPIHardwareTest : public TestCase<SPIHardwareTest>
{
public:

	SPIHardwareTest(const prog_mem * testMethodName_P, TestCase<SPIHardwareTest>::TestMethod testMethod) :
	TestCase<SPIHardwareTest>(testMethodName_P, testMethod)
	{

		spiHardware = SPIHardware::getSPIHardware(0);

	}

	void setUp()
	{
	}

	void tearDown()
	{
		spiHardware->disable();
	}

	bool testgetSPIHardware()
	{
		return AVRUNIT_ASSERT(!isNull(spiHardware));
	}

	bool testSCA3000()
	{
		setBit(DDRC, PINC0); //PINC0 is SS, set it as output
		setBit(PORTC, PINC0); // pull SS high

		DDRB = (1<<PINB0) | (1<<PINB1) | (1<<PINB2); // set SCK and MOSI as output


		spiHardware->setPrescaler(Coms::SPI::Prescalers::DIV_128, false);
		spiHardware->setMaster();
//		spiHardware->setSCKHighWhenIdle();
//		spiHardware->sampleDataOnSCKLeadingEdge();
		spiHardware->transmitMSBFirst();

		spiHardware->enable();



		while(true)
		{
		clearBit(PORTC, PINC0); // pull SS low

		spiHardware->writeByte(0x09 << 2);

		while(!spiHardware->readInterruptFlag());

		uint8_t status = spiHardware->readByte();

//		spiHardware->readByte();

//		bool result = AVRUNIT_ASSERT(!spiHardware->checkWriteCollision());

		spiHardware->writeByte(0x00);

		while(!spiHardware->readInterruptFlag());

		int16_t z = spiHardware->readByte() << 8;

		spiHardware->writeByte(0x00);

		while(!spiHardware->readInterruptFlag());

		z += spiHardware->readByte() & 0xF8;

		spiHardware->writeByte(0x00);

		while(!spiHardware->readInterruptFlag());

		int16_t y = spiHardware->readByte() << 8;

		spiHardware->writeByte(0x00);

		while(!spiHardware->readInterruptFlag());

		y += spiHardware->readByte() & 0xF8;

		spiHardware->writeByte(0x00);

		while(!spiHardware->readInterruptFlag());

		int16_t x = spiHardware->readByte() << 8;

		spiHardware->writeByte(0x00);

		while(!spiHardware->readInterruptFlag());

		x += spiHardware->readByte() & 0xF8;


		setBit(PORTC, PINC0); // pull SS high

//
//		if(z & 0x1000)
//			z = -(z & ~0x1000);
//
//		if(y & 0x1000)
//			y = -(y & ~0x1000);
//
//		if(x & 0x1000)
//			x = -(x & ~0x1000);

		printf("x, y, z = (%i, %i, %i)   status = %x    \r", 3*x/32, 3*y/32, 3*z/32, status);
//		printf("z = %i  status = %x    \r", z, status);
		delay(50);
		}



//		return result;

	}

	bool testMCP41050()
	{
		setBit(DDRC, PINC0); //PINC0 is SS, set it as output
		setBit(PORTC, PINC0); // pull SS high

		DDRB = (1<<PINB0) | (1<<PINB1) | (1<<PINB2); // set SCK and MOSI as output

		setBit(PORTB, PINB0);

		spiHardware->setPrescaler(Coms::SPI::Prescalers::DIV_128, false);
		spiHardware->setMaster();
//		spiHardware->setSCKHighWhenIdle();
//		spiHardware->sampleDataOnSCKLeadingEdge();
//		spiHardware->transmitMSBFirst();

		spiHardware->enable();


		uint8_t potValue = 0x00;

		while(true)
		{
		clearBit(PORTC, PINC0); // pull SS low

		spiHardware->writeByte(0x17);

		while(!spiHardware->readInterruptFlag());

		spiHardware->clearInterruptFlag();

		spiHardware->writeByte(potValue);

		while(!spiHardware->readInterruptFlag());

		spiHardware->clearInterruptFlag();


		setBit(PORTC, PINC0); // pull SS high

		potValue++;

		}



//		return result;

	}

	SPIHardware * spiHardware;

};

#endif /* SPIHardwareTest_H_ */
