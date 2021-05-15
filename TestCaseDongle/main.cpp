/*
 * main.cpp
 *
 *  Created on: 2009-09-14
 *      Author: malem303
 */

#include "Communication/Stdio.h"
#include "Communication/USART/ActiveBufferedUSART.h"
#include "avrcpp/CommunicationTest/PollComI2CMasterTest.h"
#include "avrcpp/CommunicationTest/CallbackComI2CMasterTest.h"
#include "Utils/Delay.h"
#include "Utils/Blink.h"




#define MAINBOARD
#define BLINK_DELAY 25

void messageCallBack(const char * message)
{
	printf(message);
#ifdef MEMORY_LOGGING
	PRINT_MEMORY_STATUS();
#endif
}

void messageCallBack(const prog_mem * message)
{
	printf(message);
#ifdef MEMORY_LOGGING
	PRINT_MEMORY_STATUS();
#endif
}


#ifdef MAINBOARD
#define MANUAL
#define CONSOLE





void successCallBack()
{
	static Blink green(&PORTE, &DDRE, 4, 1, BLINK_DELAY);

	green.blink();
}

void failureCallBack()
{
	static Blink red(&PORTE, &DDRE, 5, 1, BLINK_DELAY);

	red.blink();
}
#endif


#ifdef ROBOSTIX

#define MANUAL
#define CONSOLE


void successCallBack()
{
	static Blink blue(&PORTG, &DDRG, 3, 1, BLINK_DELAY);

	blue.blink();
	PORTG = 0xFF;
}

void failureCallBack()
{
	static Blink red(&PORTG, &DDRG, 4, 1, BLINK_DELAY);

	red.blink();
	PORTG = 0xFF;
}
#endif

using Coms::USART::ActiveBufferedUSART;

int main()
{
	DDRE = 0xFF;
	PORTE = 0xFF;



	stdin = stdout = stderr = Coms::Stdio::fdevopen(_FDEV_SETUP_RW, ActiveBufferedUSART::getInstance(0));

//	PollUSART::getPollUSART(1)->setBaudRate(BaudRates::BAUD_57600);
//	stdin = stdout = stderr = PollUSART::getPollUSART(1)->fdevopen(_FDEV_SETUP_RW);

	printf(PROG_MEM_STRING("\n\n\n\r[TestDongle for avrcpp Library]\n\n\n\r"));

	AVRUNIT_CONFIGURE_ASSERT(failureCallBack, successCallBack, messageCallBack);



	while(true)
	{
		delay(500);

		TestResult r;

		PollComI2CMasterTest::SuiteType * pollComI2CMasterTest = new PollComI2CMasterTest::SuiteType(PROG_MEM_STRING("pollComI2CMasterTest"), true);
//		AVRUNIT_SUITE_ADD_TEST(pollComI2CMasterTest, PollComI2CMasterTest, testwrite);
//		AVRUNIT_SUITE_ADD_TEST(pollComI2CMasterTest, PollComI2CMasterTest, testread);
		AVRUNIT_SUITE_ADD_2_TESTS(pollComI2CMasterTest, PollComI2CMasterTest, testwrite, testread);
		pollComI2CMasterTest->run(&r);
		delete pollComI2CMasterTest;

//		CallbackComI2CMasterTest::SuiteType * callbackComI2CMasterTest = new CallbackComI2CMasterTest::SuiteType(PROG_MEM_STRING("callbackComI2CMasterTest"), true);
////		AVRUNIT_SUITE_ADD_TEST(callbackComI2CMasterTest, CallbackComI2CMasterTest, testread);
//		AVRUNIT_SUITE_ADD_2_TESTS(callbackComI2CMasterTest, CallbackComI2CMasterTest, testwrite, testread);
//		callbackComI2CMasterTest->run(&r);
//		delete callbackComI2CMasterTest;

		messageCallBack("\n\n\r");
		for(size_t repetitions = 5; repetitions > 0; repetitions--)
		{
			messageCallBack(r.getSummary());
			messageCallBack("\r");
			size_t successes = r.getRunCount() - r.getErrorCount();

			while (successes > 0)
			{
				successCallBack();
				successes--;
			}

			size_t errors = r.getErrorCount();

			while (errors > 0)
			{
				failureCallBack();
				errors--;
			}

			delay(500);
		}
		messageCallBack("\n\n\r");
	}
//	masterWriteLoop();
//	masterReadLoop();

	return 0;
}
