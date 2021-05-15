/*
 * Timer16Test.h
 *
 *  Created on: 2009-06-03
 *      Author: malem303
 */

#ifndef TIMER16TEST_H_
#define TIMER16TEST_H_
#include "../TestCase.h"
#include "../TestSuite.h"

#include "Timers/Timer.h"
#include "Utils/Delay.h"
using namespace Timers;

class Timer16Test : public TestCase<Timer16Test>
{


	static bool calledBack;

	Timer16 * timer1;

public:

	static void timerOverflowCallBack()
	{
		calledBack = true;
	}

	Timer16Test(const prog_mem * testMethodName_P, TestCase<Timer16Test>::TestMethod testMethod) : TestCase<Timer16Test>(testMethodName_P, testMethod)
	{

	}

	void setUp()
	{

		timer1 = Timer16::getTimer(1);
		timer1->setPrescaler(Prescalers::FASTEST_1);
	}

	void tearDown()
	{
		timer1->stop();
		timer1->setTimestamp(0);
		timer1->setTimerOverflowCallBack(NULL);
	}

	bool testgetTimer()
	{
		return AVRUNIT_ASSERT(!isNull(timer1));
	}

	bool testgetTopValue()
	{
			return AVRUNIT_ASSERT_EQUALS_LONG(timer1->getTopValue(), 0xFFFF);
	}
	bool testsetTimerOverflowCallBack()
	{
		calledBack= false;

		enableInterrupts();

		timer1->setTimerOverflowCallBack(Timer16Test::timerOverflowCallBack);

		timer1->start();

		wasteCycles(timer1->getTopValue() * 2);

		disableInterrupts();

		timer1->setTimerOverflowCallBack(NULL);

		return AVRUNIT_ASSERT(Timer16Test::calledBack);
	}

	bool testtimestampTimer()
	{
		uintmax_t topVal = timer1->getTopValue();
		timer1->setTimestamp(topVal * 2 + 78);

		bool result = AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(timer1->read(), timer1->getTopValue() * 2 + 78);

		timer1->setTimestamp(0);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(timer1->read(), 0);

		timer1->start(true);

		wasteCycles((uintmax_t)timer1->getTopValue() * 2);

		uintmax_t timestamp = timer1->read();
		timer1->stop();

		printf(PROG_MEM_STRING("timestamp : %u \n\r"), timestamp);

		result &= AVRUNIT_ASSERT_AUTONAME(timestamp > (uintmax_t)timer1->getTopValue());

		timestamp = timer1->read();

		result &= AVRUNIT_ASSERT_AUTONAME(timestamp == (uintmax_t)timer1->read()); // make sure it is stopped

		timer1->start(true);

		uintmax_t newTimestamp = timer1->read();

		timer1->stop();

		result &= AVRUNIT_ASSERT_AUTONAME(newTimestamp > timestamp);


		return result;

	}

};

bool Timer16Test::calledBack = false;



#endif /* TIMER16TEST_H_ */
