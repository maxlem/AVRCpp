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

#ifndef Timer8bits2OCRTest_H_
#define Timer8bits2OCRTest_H_
#include "TestCase.h"
#include "TestSuite.h"

#include "Timers/Timer8bits2OCR.h"
#include "CallbackServers/FastCallbackServer.h"
#include "CallbackServers/Callback.h"
#include <stdlib.h>

using Timers::Timer8bits2OCR;



class TestCallback2 : public Callback
{

public :

	TestCallback2() : calledBack(false)
	{

	}
	void callback()
	{
		calledBack = true;
	}

	volatile bool calledBack;
};


class Timer8bits2OCRTest : public TestCase<Timer8bits2OCRTest>
{

	Timer8bits2OCR * timer8bits2OCR;

public:

	Timer8bits2OCRTest(const prog_mem * testMethodName_P, TestCase<Timer8bits2OCRTest>::TestMethod testMethod) :
		TestCase<Timer8bits2OCRTest>(testMethodName_P, testMethod)
	{
		timer8bits2OCR = Timer8bits2OCR::getTimer8bits2OCR(0);


	}

	~Timer8bits2OCRTest()
	{

	}

	void setUp()
	{
		timer8bits2OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		timer8bits2OCR->getCounter()->setValue(0);

		timer8bits2OCR->getCounter()->disableOVFInterrupts();

		timer8bits2OCR->getCounter()->clearOVFFlag();

	}

	void tearDown()
	{
	}

	bool testgeTimer8bits2OCR()
	{
		return AVRUNIT_ASSERT(!isNull(timer8bits2OCR));
	}

	bool testsetPrescaler()
	{


		bool result = AVRUNIT_ASSERT_EQUALS_LONG(timer8bits2OCR->getCounter()->read(), 0);

		result = AVRUNIT_ASSERT_EQUALS_LONG(16000000ul, F_CPU); // this test assumes that

		timer8bits2OCR->getCounter()->setPrescaler(Timers::Prescalers::FASTEST_1);

		_delay_ms(4.096); // the duration of 2^16 timer ticks at 16 Mhz

		timer8bits2OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		result = AVRUNIT_ASSERT_IN_RANGE_LONG(timer8bits2OCR->getCounter()->read(), 0, 100);

		result = AVRUNIT_ASSERT(timer8bits2OCR->getCounter()->readOVFFlag());

		return result;

	}

	bool testOverflowCallback()
	{
		TestCallback2 * ovf = new TestCallback2();

		timer8bits2OCR->getCounter()->connectCallback(ovf);

		timer8bits2OCR->getCounter()->enableOVFInterrupts();

		enableInterrupts();

		timer8bits2OCR->getCounter()->setPrescaler(Timers::Prescalers::FASTEST_1);

		_delay_ms(0.05);

		timer8bits2OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		disableInterrupts();

		timer8bits2OCR->getCounter()->disableOVFInterrupts();

		bool result = AVRUNIT_ASSERT(ovf->calledBack);

		result &= AVRUNIT_ASSERT(!timer8bits2OCR->getCounter()->readOVFFlag()); // will be cleared by interrupt routine

		delete ovf;

		return result;
	}

	bool testOCR()
	{

		bool result = AVRUNIT_ASSERT(!timer8bits2OCR->getCounter()->readOVFFlag());

		timer8bits2OCR->getComparatorA()->setOCRValue(0x04);

		timer8bits2OCR->getCounter()->setPrescaler(Timers::Prescalers::FASTEST_1);

		_delay_us(1);

		timer8bits2OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		result &= AVRUNIT_ASSERT(timer8bits2OCR->getComparatorA()->readOCRFlag());

		result &= AVRUNIT_ASSERT(!timer8bits2OCR->getCounter()->readOVFFlag());

		return result;
	}


};


#endif /* Timer8bits2OCRTest_H_ */
