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

#ifndef EXTERNALINTERRUPTSTEST_H_
#define EXTERNALINTERRUPTSTEST_H_
#include "ExternalInterrupts/ExternalInterrupts.h"
#include "TestCase.h"

class ExternalInterruptTest :  public TestCase<ExternalInterruptTest>
{

	ExternalInterrupt * ei;

	IOAddress excitatingPort;
	IOAddress excitatingDDR;
	uint8_t excitatingPin;
	uint8_t interruptPin;
	static bool calledBack;

public:


	ExternalInterruptTest(const prog_mem * testMethodName_P, TestCase<ExternalInterruptTest>::TestMethod testMethod) : TestCase<ExternalInterruptTest>(testMethodName_P, testMethod)
	{
		excitatingPort = &PORTB;
		excitatingDDR = &DDRB;
		excitatingPin = 5;
		interruptPin = 4;
	}


	static void interruptCallBack()
	{
		calledBack = true;
	}

	void setUp()
	{


		calledBack = false;
		disableInterrupts();
		ei = ExternalInterrupt::getInstance(interruptPin);
	}

	void tearDown()
	{
		calledBack = false;
		disableInterrupts();
	}


	bool testGetInstance()
	{
		return AVRUNIT_ASSERT(!isNull(ei));
	}

	bool testExternalInterruptCallBack()
	{
		*excitatingDDR = bitValue(excitatingPin); // all input except excitatingPin
		*excitatingPort = 0x00;

		bool result = true;
		ei->configure(ExternalInterrupt::RISING_EDGE);
		ei->setInterruptCallBack(ExternalInterruptTest::interruptCallBack);
		delay(100);


		result &= AVRUNIT_ASSERT_TESTNAME(!calledBack, "setInterruptCallBack (before setBit)"); // since we haven't enabled interrupts yet

		setBit(*excitatingPort, excitatingPin);

		result &= AVRUNIT_ASSERT_TESTNAME(!calledBack, "setInterruptCallBack (after setBit, before sei)"); // since we haven't enabled interrupts yet

		clearBit(*excitatingPort, excitatingPin);

		enableInterrupts();
		setBit(*excitatingPort, excitatingPin);
		delay(10);
		disableInterrupts();

		return result & AVRUNIT_ASSERT_TESTNAME(calledBack, "setInterruptCallBack (after int. enable)");
	}

};

bool ExternalInterruptTest::calledBack = false;

#endif /* EXTERNALINTERRUPTSTEST_H_ */
