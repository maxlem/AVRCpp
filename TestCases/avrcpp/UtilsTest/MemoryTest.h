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

#ifndef MEMORYTEST_H_
#define MEMORYTEST_H_

#include "TestCase.h"
#include "Utils/Logging.h"
#include "Utils/CppExtensions.h"



class MemoryTest :  public TestCase<MemoryTest>
{
private:
	const prog_mem * testStr;

public:


	MemoryTest(const prog_mem * testMethodName, TestCase<MemoryTest>::TestMethod testMethod) :
	TestCase<MemoryTest>(testMethodName, testMethod), testStr(PROG_MEM_STRING("01234567890012345678900123456789001234567890"))
	{
	}

	bool callBack(const char * str)
	{

		const prog_mem * otherStr = PROG_MEM_STRING("Another string");
		char * string = new(Allocators::STACK) char[45];
		strcpy(string, otherStr);

		bool result =  AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME_P(string, otherStr, "other string wrote");

		strcpy(string, str);

		return result & AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME_P(string, testStr, "testString string wrote");

	}

	bool testnew_Allocators_STACK()
	{


		size_t initialStackSize = stackSize();

		char * string = new(Allocators::STACK) char[45];

		bool result = AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(stackSize(), initialStackSize + 45, "new(Allocators::STACK)");

		strcpy(string, testStr);


		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME_P(string, testStr, "allocation string wrote");


		result &= callBack(string);

		result &= AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME_P(string, testStr, "after callback");

		return result;
	}

	bool allocateMaxMemoryChunck()
	{
		uint8_t * STACK_PROVISION = new(Allocators::STACK) uint8_t[100]; // stack provision

		uint8_t * bytes = new uint8_t[maxMemoryChunkLeft()];

		bool result = !isNull(bytes);

		delete bytes;

		return result;

	}
	bool testnew()
	{
		const size_t mallocMarginExtra = 30; //TODO find out why

		size_t initialStackSize = stackSize();

		char * initialHeapTop =  (char*)getHeapTop();

		size_t initialDistanceHeapFromStack = distanceHeapFromStack();

		size_t initialmaxChunkLeft = maxMemoryChunkLeft();

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(initialDistanceHeapFromStack, RAMEND - initialStackSize - (size_t)initialHeapTop);

		uint8_t * bytes = new uint8_t[4000];

		result &= AVRUNIT_ASSERT_AUTONAME(isNull(bytes));

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(initialmaxChunkLeft, maxMemoryChunkLeft(), "maxMemoryChunkLeft");

		result &= AVRUNIT_ASSERT_AUTONAME(allocateMaxMemoryChunck());



		PRINT_MEMORY_STATUS();

		return result;
	}


};

#endif /* MEMORYTEST_H_ */
