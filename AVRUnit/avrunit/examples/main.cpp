/*
 * main.cpp
 *
 *  Created on: 2009-06-06
 *      Author: malem303
 */
#include "../TestCase.h"
#include "../TestSuite.h"
#include "../TestResult.h"
#include "Timer16Test.h"

#include "Utils/CppExtensions.h"
#include "Utils/BitManipulation.h"
#include "Utils/Utils.h"
#include "Utils/Blink.h"
#include "Communication/USART.h"

class ClassUnderTest
{
public:

	int sum(int lhs, int rhs)
	{
		return lhs + rhs;
	}

	int substraction(int lhs, int rhs)
	{
		return lhs - rhs;
	}
};

class ClassUnderTestTest : public TestCase<ClassUnderTestTest>
{
private:
	ClassUnderTest * t;

public :


	ClassUnderTestTest(const prog_mem * testMethodName, TestCase<ClassUnderTestTest>::TestMethod testMethod) :TestCase<ClassUnderTestTest>(testMethodName, testMethod)
	{
	}

	bool testSum()
	{
		return AVRUNIT_ASSERT_EQUALS_LONG(t->sum(2,2), 4);
	}

	bool testSubstraction()
	{
		return AVRUNIT_ASSERT_EQUALS_LONG(t->substraction(2,2), 4);
	}

	void setUp()
	{
		t = new ClassUnderTest();
	}
	void tearDown()
	{
		delete t;
	}
};




void messageCallBack(const char * message)
{
	printf(message);
}

void successCallBack()
{
	static Blink blue(&PORTG, &DDRG, 3);
	blue.blink();
	PORTG = 0xFF;
}

void failureCallBack()
{
	static Blink red(&PORTG, &DDRG, 4);
	red.blink();
	PORTG = 0xFF;
}

using COM::USART;

int main()
{
	USART::getUSART(0)->setBaudRate(COM::BaudRates::BAUD_57600);
	stdin = stdout = USART::getUSART(0)->fdevopen(_FDEV_SETUP_RW);

	USART::getUSART(1)->setBaudRate(COM::BaudRates::BAUD_57600);
	stderr = USART::getUSART(1)->fdevopen(_FDEV_SETUP_RW);

	Blink green(&PORTE, &DDRE, 6);
	Blink red(&PORTE, &DDRE, 7);

	AVRUNIT_CONFIGURE_ASSERT(failureCallBack, successCallBack, messageCallBack);

	TestResult r;

	ClassUnderTestTest::SuiteType * classUnderTestSuite = new ClassUnderTestTest::SuiteType(PROG_MEM_STRING("classUnderTestSuite"), true);
	AVRUNIT_SUITE_ADD_2_TESTS(classUnderTestSuite, ClassUnderTestTest, testSum, testSubstraction);
	classUnderTestSuite->run(&r);
	delete classUnderTestSuite;

	Timer16Test::SuiteType * timer16TestSuite = new Timer16Test::SuiteType(PROG_MEM_STRING("timer16TestSuite"), true);
	AVRUNIT_SUITE_ADD_4_TESTS(timer16TestSuite, Timer16Test, testgetTimer, testgetTopValue, testsetTimerOverflowCallBack, testtimestampTimer);
	timer16TestSuite->run(&r);
	delete timer16TestSuite;

	return 0;
}
