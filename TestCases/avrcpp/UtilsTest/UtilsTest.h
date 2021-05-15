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

#ifndef UTILSTEST_H_
#define UTILSTEST_H_

#include "Utils/Utils.h"
#include "Utils/Logging.h"
#include "TestCase.h"

class UtilsTest :  public TestCase<UtilsTest>
{

	IOAddress ddra;

	static bool calledBack;

public:


	UtilsTest(const prog_mem * testMethodName, TestCase<UtilsTest>::TestMethod testMethod) : TestCase<UtilsTest>(testMethodName, testMethod)
	{
		ddra = &DDRA;
	}

	static void callBack()
	{
		calledBack = true;
	}

	void setUp()
	{
		disableInterrupts();


		*ddra = 0x00;
	}

	void tearDown()
	{
		disableInterrupts();
		*ddra = 0x00;
	}


	bool testSetBits()
	{

		setBit(*ddra, 0);

		bool result = AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(0, 0, 0, 0, 0, 0, 0, 1), "setBit");

		setBit(*ddra, 1);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(0, 0, 0, 0, 0, 0, 1, 1), "setBit #2");

		*ddra = 0x00;

		set2Bits(*ddra, 0, 1);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(0, 0, 0, 0, 0, 0, 1, 1), "set2Bits");

		*ddra = 0x00;

		set3Bits(*ddra, 0, 1, 7);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(1, 0, 0, 0, 0, 0, 1, 1), "set3Bits");

		*ddra = 0x00;

		set4Bits(*ddra, 0, 1, 7, 6);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(1, 1, 0, 0, 0, 0, 1, 1), "set4Bits");

		*ddra = 0x00;


		return result;
	}

	bool testClearBits()
	{

		*ddra = 0xFF;


		clearBit(*ddra, 0);

		bool result = AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(1, 1, 1, 1, 1, 1, 1, 0), "clearBit");

		clearBit(*ddra, 1);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(1, 1, 1, 1, 1, 1, 0, 0), "clearBit #2");

		*ddra = 0xFF;

		clear2Bits(*ddra, 0, 1);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(1, 1, 1, 1, 1, 1, 0, 0), "clear2Bits");

		*ddra = 0xFF;

		clear3Bits(*ddra, 0, 1, 7);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(0, 1, 1, 1, 1, 1, 0, 0), "clear3Bits");

		*ddra = 0xFF;

		clear4Bits(*ddra, 0, 1, 7, 6);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(*ddra, mask8(0, 0, 1, 1, 1, 1, 0, 0), "clear4Bits");

		*ddra = 0xFF;


		return result;
	}


	bool testInterruptFlags()
	{

		disableInterrupts();

		bool enabled = interruptsEnabled();

		bool result = AVRUNIT_ASSERT(!enabled);

		enableInterrupts();

		enabled = interruptsEnabled();

		result &= AVRUNIT_ASSERT(enabled);

		disableInterrupts();

		enabled = interruptsEnabled();

		return 	result & AVRUNIT_ASSERT(!enabled);

	}


	bool testBuildMask()
	{
		return AVRUNIT_ASSERT_EQUALS_LONG(buildMask(2,4,6), 84u);
	}

	bool testSetConfig()
	{
		setConfig(ddra, buildMask(2,4,6), 0x03);

		return AVRUNIT_ASSERT_EQUALS_LONG(*ddra, 20u);
	}

	bool testChecksum()
	{
		#define TEST_CHECKSUM_SUM_SIZE 10
		uint8_t bytes[TEST_CHECKSUM_SUM_SIZE] = {0,1,2,3,4,5,6,7,8,9};

		uint8_t sum = (TEST_CHECKSUM_SUM_SIZE - 1) * (TEST_CHECKSUM_SUM_SIZE / 2);

		uint8_t testValue = sum + computeChecksum<uint8_t, uint8_t>(bytes, TEST_CHECKSUM_SUM_SIZE);

		bool result = AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(testValue, 0, "testChecksum normal");

		for (size_t i = 0; i < TEST_CHECKSUM_SUM_SIZE; i++)
			bytes[i] = 100;

		sum = ((uintmax_t)(TEST_CHECKSUM_SUM_SIZE * 100))%((uintmax_t)pow(2, sizeof(uint8_t) * 8));
		testValue = sum + computeChecksum<uint8_t, uint8_t>(bytes, TEST_CHECKSUM_SUM_SIZE);

		result = AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(testValue, 0, "testChecksum overflow");


		return result;
	}

	bool strdupAll()
	{
		const prog_mem * testStr = PROG_MEM_STRING("strdup_test123");

		size_t delta = stackSize();

		char * str = new(Allocators::STACK) char[100]; // MAKE SURE : strlen_P(testStr) + 1 < 100

		delta = stackSize() - delta;

		bool result = AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(delta, 100, "new(Allocators::STACK) char[100]");

		delta = stackSize();

		char * allocaStr = (char*)__builtin_alloca(100);

		delta = stackSize() - delta;

		strcpy(str, testStr);
		char * strdup1 = strdup(str);
		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME(strdup1, str, "strdup");
		delete strdup1;


		strdup1 = strdup(testStr);
		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME(strdup1, str, "strdup_P");

		strdup1 = strdup(strdup1, testStr);

		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME(strdup1, str, "strdup(void*,const prog_mem *)");

		const prog_mem * smallerStr = PROG_MEM_STRING("Smaller");

		strdup1 = strdup(strdup1, smallerStr);

		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME_P(strdup1, smallerStr, "strdup(void*,const prog_mem *) - smallerStr");

		const prog_mem * larger = PROG_MEM_STRING("smallerStr_Larger");

		strdup1 = strdup(strdup1, larger);

		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME_P(strdup1, larger, "strdup(void*,const prog_mem *) - larger");


		delete strdup1;

		size_t stackBefore = stackSize();
		strdup1 = strdup(str, Allocators::STACK);
		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME(strdup1, str, "strdupStack");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(stackBefore + strlen(str) + 1, stackSize(), "strdupStack NULL char");

		stackBefore = stackSize();
		strdup1 = strdup(testStr, Allocators::STACK);
		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME(strdup1, str, "strdupStack");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(stackBefore + strlen(str) + 1, stackSize(), "strdupStack NULL char");

		return result;
	}

	bool testparseValue()
	{
		size_t prescaler = 0;
		setupParseValue('_');
		parseValue(ADC::DIV_2, prescaler);

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(prescaler, 2);

		return result;
	}
};

#endif /* UTILSTEST_H_ */
