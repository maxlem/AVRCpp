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

#ifndef Timer16bits3OCRTest_H_
#define Timer16bits3OCRTest_H_
#include "TestCase.h"
#include "TestSuite.h"

#include "Timers/Timer16bits3OCR.h"
#include "CallbackServers/FastCallbackServer.h"
#include "CallbackServers/Callback.h"
#include <stdlib.h>

using Timers::Timer16bits3OCR;



class TestCallback : public Callback
{

public :

	void callback()
	{
		calledBack = true;
	}

	volatile bool calledBack;
};


class Timer16bits3OCRTest : public TestCase<Timer16bits3OCRTest>
{

	Timer16bits3OCR * timer16bits3OCR;

public:

	Timer16bits3OCRTest(const prog_mem * testMethodName_P, TestCase<Timer16bits3OCRTest>::TestMethod testMethod) :
		TestCase<Timer16bits3OCRTest>(testMethodName_P, testMethod)
	{
		timer16bits3OCR = Timer16bits3OCR::getTimer16bits3OCR(1);

	}

	~Timer16bits3OCRTest()
	{
	}

	void setUp()
	{
		timer16bits3OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		timer16bits3OCR->getCounter()->setValue(0);

		timer16bits3OCR->getCounter()->disableOVFInterrupts();

		timer16bits3OCR->getCounter()->clearOVFFlag();



	}

	void tearDown()
	{
	}

	bool testgeTimer16bits3OCR()
	{
		return AVRUNIT_ASSERT(!isNull(timer16bits3OCR));
	}

	bool testsetPrescaler()
	{


		bool result = AVRUNIT_ASSERT_EQUALS_LONG(timer16bits3OCR->getCounter()->read(), 0);

		result = AVRUNIT_ASSERT_EQUALS_LONG(16000000ul, F_CPU); // this test assumes that

		timer16bits3OCR->getCounter()->setPrescaler(Timers::Prescalers::FASTEST_1);

		_delay_ms(4.096); // the duration of 2^16 timer ticks at 16 Mhz

		timer16bits3OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		result = AVRUNIT_ASSERT_IN_RANGE_LONG(timer16bits3OCR->getCounter()->read(), 0, 100);

		result = AVRUNIT_ASSERT(timer16bits3OCR->getCounter()->readOVFFlag());

		return result;

	}

	bool testOverflowCallback()
	{
		TestCallback2 * ovf = new TestCallback2();

		timer16bits3OCR->getCounter()->connectCallback(ovf);

		timer16bits3OCR->getCounter()->enableOVFInterrupts();

		enableInterrupts();

		timer16bits3OCR->getCounter()->setPrescaler(Timers::Prescalers::FASTEST_1);

		_delay_ms(5);

		timer16bits3OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		disableInterrupts();

		timer16bits3OCR->getCounter()->disableOVFInterrupts();

		bool result = AVRUNIT_ASSERT(ovf->calledBack);

		result &= AVRUNIT_ASSERT(!timer16bits3OCR->getCounter()->readOVFFlag()); // will be cleared by interrupt routine

		delete ovf;

		return result;
	}

	bool testOCR()
	{

		timer16bits3OCR->getComparatorA()->setOCRValue(0x00FF);

		timer16bits3OCR->getCounter()->setPrescaler(Timers::Prescalers::FASTEST_1);

		_delay_ms(4.096/2);

		timer16bits3OCR->getCounter()->setPrescaler(Timers::Prescalers::STOP_TIMER_0);

		bool result = AVRUNIT_ASSERT(timer16bits3OCR->getComparatorA()->readOCRFlag());

		result &= AVRUNIT_ASSERT(!timer16bits3OCR->getCounter()->readOVFFlag());

		return result;
	}


};


#endif /* Timer16bits3OCRTest_H_ */
