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

#ifndef USARTHardwareTest_H_
#define USARTHardwareTest_H_

#include "TestCase.h"
#include "Coms/USART/USARTHardware.h"
#include <stdio.h>

using Coms::USART::USARTHardware;

#define READ_MARGIN 10

class USARTHardwareTest : public TestCase<USARTHardwareTest>
{
public:

	USARTHardwareTest(const prog_mem * testMethodName_P, TestCase<USARTHardwareTest>::TestMethod testMethod) :
	TestCase<USARTHardwareTest>(testMethodName_P, testMethod)
	{

		usartHardware = USARTHardware::getUSARTHardware(2);



	}

	uint16_t loopback(uint16_t data)
	{
		while(!usartHardware->isTransmitterReady());

		usartHardware->writeFrame(data);

		while(!usartHardware->isFrameTransmitted());

		while(!usartHardware->isFrameReceived());

		lastStatus = usartHardware->status();

		return usartHardware->readFrame();

	}

	void setUp()
	{
		printf(PROG_MEM_STRING("Connect RX1 and TX1 together (loopback mode)\n\r"));

		usartHardware->configureDefaults();
		usartHardware->enableTransmitter();
		usartHardware->enableReceiver();
	}

	void tearDown()
	{
		usartHardware->disableTransmitter();
		usartHardware->disableReceiver();
	}

	bool testdefaults()
	{

		uintmax_t bitRate = usartHardware->getBitRate();

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(bitRate, F_CPU/(8 * ( 34 + 1)));

		char character = loopback('a');

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(character, 'a');

		uint16_t number = loopback(255);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(number, 255);

		return result;
	}

	bool testconfigureBitRate()
	{

		usartHardware->configureBitRate(0, false, false);

		uintmax_t bitRate = usartHardware->getBitRate();

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(bitRate, F_CPU/16);

		char character = loopback('a');

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(character, 'a');

		usartHardware->configureBitRate(0xFFFF, true, false);

		bitRate = usartHardware->getBitRate();

		result &=  AVRUNIT_ASSERT_EQUALS_LONG(bitRate, F_CPU/(8*(0x0FFFu + 1)));

		character = loopback('a');

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(character, 'a');

		return result;
	}

	bool testconfigureDataBitsMode()
	{

		using namespace Coms::USART;

		usartHardware->configureFrameSize(FrameSizes::NINE_BITS);

		uint16_t number = loopback(256u);

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(number, 256u);

		number = loopback(513u);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(number, 1u);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		usartHardware->configureFrameSize(FrameSizes::FIVE_BITS);

		number = loopback(16u);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(number, 16u);

		number = loopback(33u);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(number, 1u);

		return result;
	}

	bool testconfigureStopBitsMode()
	{

		using namespace Coms::USART;

		usartHardware->configureStopBitsMode(StopBitsModes::TWO);

		char character = loopback('a');

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(character, 'a');

		return result;
	}

	bool testconfigureParityMode()
	{

		using namespace Coms::USART;

		usartHardware->configureParityMode(ParityModes::ODD);

		char character = loopback('a');

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(character, 'a');

		usartHardware->configureParityMode(ParityModes::EVEN);

		character = loopback('a');

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(character, 'a');

		return result;
	}

	bool testMPCM()
	{

		using namespace Coms::USART;


		usartHardware->configureFrameSize(FrameSizes::NINE_BITS);

		usartHardware->enableMPCM();

		bool result = AVRUNIT_ASSERT(!usartHardware->isFrameReceived());

		while(!usartHardware->isTransmitterReady());

		usartHardware->writeFrame(255);

		delay(100);

		result &= AVRUNIT_ASSERT(!usartHardware->isFrameReceived());

		char address = loopback(256 + 'a');

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(address, 'a');

		usartHardware->disableMPCM();

		char character = loopback('a');

		result &= AVRUNIT_ASSERT_EQUALS_LONG(lastStatus, 0x00);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(character, 'a');

		return result;
	}

	bool benchmark()
	{
		char c = '0';
		uint8_t oneToTen = 0;

		while(true)
		{

			while(!usartHardware->isTransmitterReady());

			usartHardware->writeFrame(c + oneToTen);

			oneToTen++;

			oneToTen %=10;
		}
	}

	bool receiveInLoop()
	{
//		usartHardware->configureBitRate(103, false, false); //9600

		usartHardware->configureBitRate(16, false, false); // <--- use THIS for communicating with xBee at 56.7k

		char c[26];

		while(true)
		{

			for(size_t i = 0; i < 25; i++)
			{
				while(!usartHardware->isFrameReceived());

				c[i] = usartHardware->readFrame();
			}

			c[25] = '\0';

			printf("received : %s \n\r", c);

		}
	}
private:

	USARTHardware * usartHardware;

	uint8_t lastStatus;
};


#endif /* USARTHardwareTest_H_ */
