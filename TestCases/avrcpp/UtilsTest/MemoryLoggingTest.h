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

#ifndef MemoryLoggingTest_H_
#define MemoryLoggingTest_H_

#include "TestCase.h"
#include "Utils/Logging.h"
#include "Utils/CppExtensions.h"



class MemoryLoggingTest :  public TestCase<MemoryLoggingTest>
{
private:
	const prog_mem * testStr;

public:


	MemoryLoggingTest(const prog_mem * testMethodName, TestCase<MemoryLoggingTest>::TestMethod testMethod) :
	TestCase<MemoryLoggingTest>(testMethodName, testMethod), testStr(PROG_MEM_STRING("01234567890012345678900123456789001234567890"))
	{
	}


	bool allocateAllStack()
	{
		bool result = true;

		void * memory = alloca(distanceHeapFromStack());

		result &= !isNull(memory);

		result &= stackSize() != 0;

		return result;

	}

	bool teststackSize()
	{
		size_t initialStackSize = stackSize();

		uint8_t * memory = new(Allocators::STACK) uint8_t[45];

		bool result = AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(stackSize(), initialStackSize + 45, "stackSize() after");

		result &= AVRUNIT_ASSERT_AUTONAME(!isNull(memory));

		memory = new(Allocators::STACK)uint8_t[distanceHeapFromStack() + __malloc_margin];

		result &= AVRUNIT_ASSERT_AUTONAME(isNull(memory));

		initialStackSize = stackSize();

		result &= AVRUNIT_ASSERT_AUTONAME(allocateAllStack());

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(stackSize(), initialStackSize, "stackSize() unchanged");

		return result;

	}


	size_t growHeap()
	{
		size_t initialHeapSize = heapSize();

		for(size_t maxNode = 1; maxNode < maxMemoryChunkLeft(); maxNode += 1)
		{
			uint8_t * memory = new uint8_t[maxNode];
			delete memory;

			if(initialHeapSize == heapSize())
				return maxNode - 1;
		}


	}

	bool testdistanceHeapFromStack()
	{
		size_t initialDistanceHeapFromStack = distanceHeapFromStack();

		uint8_t * memory = new(Allocators::STACK) uint8_t[10];

		bool result = AVRUNIT_ASSERT_AUTONAME(!isNull(memory));

		result &= AVRUNIT_ASSERT_EQUALS_LONG(distanceHeapFromStack(), initialDistanceHeapFromStack - 10);


		initialDistanceHeapFromStack = distanceHeapFromStack();

		size_t growth = growHeap();

		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(distanceHeapFromStack(), initialDistanceHeapFromStack - growth, 5);


		return result;

	}


};



#endif /* MemoryLoggingTest_H_ */
