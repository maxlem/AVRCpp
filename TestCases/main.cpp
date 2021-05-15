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

//#define ROBOSTIX
//#define MAINBOARD
#define ARDUINO_MEGA

#include "Utils/Delay.h"
#include "Utils/Blink.h"
#include "TestClass.h"

#include "avrcpp/TimersTest/Timer8bits2OCRTest.h"
#include "avrcpp/TimersTest/Timer16bits3OCRTest.h"

#include "avrcpp/ADC/ADCHardwareTest.h"

#include "avrcpp/Coms/USART/USARTHardwareTest.h"
#include "avrcpp/Coms/USART/stdioUSARTTest.h"
#include "avrcpp/Coms/USART/ActiveBufferedUSARTTest.h"

#include "avrcpp/Coms/SPI/SPIHardwareTest.h"
#include "avrcpp/Coms/SPI/SPIMasterTest.h"

#include "avrcpp/UtilsTest/UtilsTest.h"
#include "avrcpp/UtilsTest/MemoryTest.h"
#include "avrcpp/UtilsTest/MemoryLoggingTest.h"

//#include "avrcpp/CallbackServersTest/CallbackServersTest.h"

#include "avrcpp/ExternalInterruptTest/ExternalInterruptTest.h"

#include "avrcpp/DataStructuresTest/DictionaryTest.h"
#include "avrcpp/DataStructuresTest/ListTest.h"
#include "avrcpp/DataStructuresTest/QueueTest.h"
#include "avrcpp/DataStructuresTest/StringBufferTest.h"
#include "avrcpp/DataStructuresTest/BufferTest.h"


#include "avrcppext/SensorsTests/ADCSensorTest.h"
#include "avrcppext/SensorsTests/SCA3000Test.h"
#include "avrcppext/SensorsTests/SensorSerializerTest.h"


#include "avrcppext/Actuators/RCServos/RCServoTest.h"

#include "avrcppext/RegularExpressions/RegexTest.h"

#include "TestSuite.h"
#include "TestResult.h"
#include "TestCase.h"

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>

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
Blink green(&PORTE, &DDRE, 6);
Blink red(&PORTE, &DDRE, 7);



void successCallBack()
{
	green.blink();
}

void failureCallBack()
{
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


#ifdef ARDUINO_MEGA

#define MANUAL
#define CONSOLE


void successCallBack()
{
	static Blink blue(&PORTB, &DDRB, 7, 1, BLINK_DELAY);

	blue.blink();
}

void failureCallBack()
{
	static Blink red(&PORTB, &DDRB, 7, 1, BLINK_DELAY);

	red.blink();
}
#endif

//using Coms::USART::ActiveBufferedUSART;

int main()
{

	Blink orange(&PORTB, &DDRB, 7, 1, BLINK_DELAY);

	successCallBack();


	stderr = Coms::USART::fdevopen(_FDEV_SETUP_RW, Coms::USART::USARTHardware::getUSARTHardware(0));

	stdin = stdout = Coms::USART::fdevopen(_FDEV_SETUP_RW, Coms::USART::USARTHardware::getUSARTHardware(0));


	PRINT_MEMORY_STATUS();

#ifdef CONSOLE
	messageCallBack(PROG_MEM_STRING("\n\n\n\r[TestCases for avrcpp Library]\n\n\n\r"));
#endif

	AVRUNIT_CONFIGURE_ASSERT(failureCallBack, successCallBack, messageCallBack);

	while(true)
	{
		TestResult r;// = new TestResult(); //TODO FIND out why allocating TestResult locally doesn't work past delete myTestSuite

//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(RCServoTest, &r, testsetPosition);

//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(SensorSerializerTest, &r, teststart);

//		AVRUNIT_DECLARE_RUN_DELETE_SUITE_4_TESTS(Timer8bits2OCRTest, &r, testgeTimer8bits2OCR, testsetPrescaler, testOverflowCallback, testOCR);


//		AVRUNIT_DECLARE_RUN_DELETE_SUITE_4_TESTS(Timer16bits3OCRTest, &r, testgeTimer16bits3OCR, testsetPrescaler, testOverflowCallback, testOCR);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE_2_TESTS(Timer16bits3OCRTest, &r, testOverflowCallback, testOCR);


//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(SampleTest, &r, testserialize);

//		AVRUNIT_DECLARE_RUN_DELETE_SUITE_4_TESTS(ADCHardwareTest, &r, testgetInstance, testUntriggeredConversions, testTriggeredConversions, testDifferentialModes);


//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(ADCSensorTest, &r, testRead);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(SCA3000Test, &r, testRead);
//
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(AbstractSensorSerializerTest, &r, testexecuteWithMocks);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(AbstractSensorSerializerTest, &r, testexecuteWithAnalogs);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(AbstractSensorSerializerTest, &r, testsynchronize);

//		AVRUNIT_DECLARE_RUN_DELETE_SUITE_2_TESTS(SPIHardwareTest, &r, testgetSPIHardware, testSCA3000);

//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(SPIMasterTest, &r, testSCA3000);

//		AVRUNIT_DECLARE_RUN_DELETE_SUITE_6_TESTS(USARTHardwareTest, &r, testdefaults, testconfigureBitRate, testconfigureDataBitsMode, testconfigureStopBitsMode, testconfigureParityMode, testMPCM);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(stdioUSARTTest, &r, testLoopback);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE_2_TESTS(ActiveBufferedUSARTTest, &r, testLoopbackSingleChar, testLoopbackCallback);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(ActiveBufferedUSARTTest, &r, benchmark);
		AVRUNIT_DECLARE_RUN_DELETE_SUITE(USARTHardwareTest, &r, receiveInLoop);
//		AVRUNIT_DECLARE_RUN_DELETE_SUITE(AnalogSensorTest, &r, testsample);


//		CallbackServersTest::SuiteType * CallbackServersTestSuite = new CallbackServersTest::SuiteType(PROG_MEM_STRING("CallbackServersTestSuite"), true);
////		AVRUNIT_SUITE_ADD_TEST(CallbackServersTestSuite, CallbackServersTest, testDictionnaryCallbackServer);
////		AVRUNIT_SUITE_ADD_TEST(CallbackServersTestSuite, CallbackServersTest, testFastCallbackServer);
//		AVRUNIT_SUITE_ADD_2_TESTS(CallbackServersTestSuite, CallbackServersTest, testDictionnaryCallbackServer, testFastCallbackServer);
//		CallbackServersTestSuite->run(&r);
//		delete CallbackServersTestSuite;



//
//		UtilsTest::SuiteType * utilsTestSuite = new UtilsTest::SuiteType(PROG_MEM_STRING("utilsTestSuite"), true);
//		AVRUNIT_SUITE_ADD_6_TESTS(utilsTestSuite, UtilsTest, testInterruptFlags, testBuildMask, testSetConfig, testChecksum, strdupAll, testparseValue);
//		utilsTestSuite->run(&r);
//		delete utilsTestSuite;
//
//		QueueTest::SuiteType * queueSuite = new QueueTest::SuiteType(PROG_MEM_STRING("queueSuite"), true);
//		AVRUNIT_SUITE_ADD_7_TESTS(queueSuite, QueueTest, testnumberOfElements, testenQueue, testdeQueue, testisEmpty, testisFull, testoperators, testresize);
//		queueSuite->run(&r);
//		delete queueSuite;
//
//
//
//		StringBufferTest::SuiteType * stringBufSuite = new StringBufferTest::SuiteType(PROG_MEM_STRING("stringBufSuite"), true);
//		AVRUNIT_SUITE_ADD_TEST(stringBufSuite, StringBufferTest, testoperators);
//		stringBufSuite->run(&r);
//		delete stringBufSuite;
//
//		ListTest::SuiteType * listSuite = new ListTest::SuiteType(PROG_MEM_STRING("listSuite"), true);
//		AVRUNIT_SUITE_ADD_8_TESTS(listSuite, ListTest, testappend, testnumberOfElements, testinsertElement, testremove, testisEmpty, testposition, testAssign, testElements);
//		listSuite->run(&r);
//		delete listSuite;
//
//		DictionaryTest::SuiteType * dictSuite = new DictionaryTest::SuiteType(PROG_MEM_STRING("dictSuite"), true);
//		AVRUNIT_SUITE_ADD_8_TESTS(dictSuite, DictionaryTest, testinsertElement, testfind, testremoveElement, testclone, testassign, testkeys, testelements, testassign);
//		dictSuite->run(&r);
//		delete dictSuite;
//
//		BufferTest::SuiteType * pascalMemoryBufferTestSuite = new BufferTest::SuiteType(PROG_MEM_STRING("pascalMemoryBufferTestSuite"), true);
//		AVRUNIT_SUITE_ADD_TEST(pascalMemoryBufferTestSuite, BufferTest, testConstructorsDestructors);
//		pascalMemoryBufferTestSuite->run(&r);
//		delete pascalMemoryBufferTestSuite;
//
//
//		LIS302LTest::SuiteType * lis302TestSuite = new LIS302LTest::SuiteType(PROG_MEM_STRING("lis302TestSuite"), true);
//		AVRUNIT_SUITE_ADD_TEST(lis302TestSuite, LIS302LTest, testsample);
////		AVRUNIT_SUITE_ADD_2_TESTS(lis302TestSuite, LIS302LTest, testscaledSample, testrawSample);
//		lis302TestSuite->run(&r);
//		delete lis302TestSuite;
//
//		ExternalInterruptTest::SuiteType * eiTestSuite = new ExternalInterruptTest::SuiteType(PROG_MEM_STRING("eiTestSuite"), true);
//		AVRUNIT_SUITE_ADD_2_TESTS(eiTestSuite, ExternalInterruptTest, testGetInstance, testExternalInterruptCallBack);
//		eiTestSuite->run(&r);
//		delete eiTestSuite;
//
//
//
//
//		CallbackI2CSlaveTest::SuiteType * callbackI2CSlaveTest = new CallbackI2CSlaveTest::SuiteType(PROG_MEM_STRING("callbackI2CSlaveTest"), true);
////		AVRUNIT_SUITE_ADD_TEST(callbackI2CSlaveTest, CallbackI2CSlaveTest, testwrite);
//		AVRUNIT_SUITE_ADD_2_TESTS(callbackI2CSlaveTest, CallbackI2CSlaveTest, testread, testwrite);
//		callbackI2CSlaveTest->run(&r);
//		delete callbackI2CSlaveTest;
//
//		CallbackComI2CSlaveTest::SuiteType * callbackComI2CSlaveTest = new CallbackComI2CSlaveTest::SuiteType(PROG_MEM_STRING("callbackComI2CSlaveTest"), true);
////		AVRUNIT_SUITE_ADD_TEST(callbackComI2CSlaveTest, CallbackComI2CSlaveTest, testwrite);
//		AVRUNIT_SUITE_ADD_2_TESTS(callbackComI2CSlaveTest, CallbackComI2CSlaveTest, testread, testwrite);
//		callbackComI2CSlaveTest->run(&r);
//		delete callbackComI2CSlaveTest;
//
//
//
//		MemoryLoggingTest::SuiteType * memoryLoggingTestSuite = new MemoryLoggingTest::SuiteType(PROG_MEM_STRING("memoryLoggingTestSuite"), true);
//		AVRUNIT_SUITE_ADD_2_TESTS(memoryLoggingTestSuite, MemoryLoggingTest, teststackSize, testdistanceHeapFromStack);
//		memoryLoggingTestSuite->run(&r);
//		delete memoryLoggingTestSuite;
//
//
//		MemoryTest::SuiteType * memSuite = new MemoryTest::SuiteType(PROG_MEM_STRING("memSuite"), true);
//		AVRUNIT_SUITE_ADD_2_TESTS(memSuite, MemoryTest, testnew_Allocators_STACK, testnew);
//		memSuite->run(&r);
//		delete memSuite;
//
//		RegexTest::SuiteType * regexSuite = new RegexTest::SuiteType(PROG_MEM_STRING("regexSuite"), true);
////		AVRUNIT_SUITE_ADD_TEST(regexSuite, RegexTest, testregexp);
//		AVRUNIT_SUITE_ADD_TEST(regexSuite, RegexTest, testRegularExpression);
//		regexSuite->run(&r);
//		delete regexSuite;

//		printMemoryLog();

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


		}

		delay(5000);

		messageCallBack("\n\n\r");
	}

}

