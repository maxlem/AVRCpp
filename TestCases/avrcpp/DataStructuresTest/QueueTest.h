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

#ifndef QUEUETEST_H_
#define QUEUETEST_H_


#include "DataStructures/Queue.h"
#include "TestCase.h"
#include "../../TestClass.h"
#include "Utils/Utils.h"

class QueueTest :  public TestCase<QueueTest>
{

	TestClass el0;
	TestClass el1;
	TestClass el2;
	TestClass el3;
	TestClass el4;
	Queue<TestClass> * queue;

public:


	QueueTest(const prog_mem * testMethodName_P, TestCase<QueueTest>::TestMethod testMethod) :
	TestCase<QueueTest>(testMethodName_P, testMethod),
	el0(10, PROG_MEM_STRING("TestClass1")), el1(20, PROG_MEM_STRING("TestClass2")),
	el2(30, PROG_MEM_STRING("TestClass3")), el3(40, PROG_MEM_STRING("TestClass4")),
	el4(50, PROG_MEM_STRING("TestClass5"))
	{

	}

	void setUp()
	{
		queue = new Queue<TestClass>(10);
	}
	void tearDown()
	{
		delete queue;
	}

	bool testnumberOfElements()
	{
		bool result = AVRUNIT_ASSERT_EQUALS_LONG(queue->numberOfElements(), 0);
		queue->enQueue(el0);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(queue->numberOfElements(), 1);
		queue->enQueue(el1);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(queue->numberOfElements(), 2);
		return result;
	}

	bool testenQueue()
	{
		bool result = AVRUNIT_ASSERT(queue->isEmpty());
		queue->enQueue(el0);
		result &= AVRUNIT_ASSERT(!queue->isEmpty());
		result &= AVRUNIT_ASSERT_EQUALS_LONG(queue->numberOfElements(), 1);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el0.element);

		queue->enQueue(el1);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(queue->numberOfElements(), 2);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el1.element);

		return result;
	}


	bool testdeQueue()
	{
		bool result = AVRUNIT_ASSERT(queue->isEmpty());

		queue->enQueue(el0);
		queue->enQueue(el1);
		queue->enQueue(el2);

		TestClass t = queue->deQueue();
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t.element, 10);

		t = queue->deQueue();
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t.element, 20);

		t = queue->deQueue();
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t.element, 30);

		return result;
	}

	bool testisEmpty()
	{
		bool result = AVRUNIT_ASSERT(queue->isEmpty());

		queue->enQueue(el0);
		queue->enQueue(el1);
		queue->enQueue(el2);

		result &= AVRUNIT_ASSERT(!queue->isEmpty());

		queue->deQueue();
		queue->deQueue();
		queue->deQueue();

		result &= AVRUNIT_ASSERT(queue->isEmpty());

		return result;
	}

	bool testisFull()
	{
		bool result = AVRUNIT_ASSERT(queue->isEmpty());

		queue->enQueue(el0);
		queue->enQueue(el1);
		queue->enQueue(el2);
		queue->enQueue(el3);
		queue->enQueue(el4);
		queue->enQueue(el0);
		queue->enQueue(el1);
		queue->enQueue(el2);
		queue->enQueue(el3);
		queue->enQueue(el4);

		result &= AVRUNIT_ASSERT(queue->isFull());

		return result;
	}
	bool testoperators()
	{
		*queue << el0 << el1;

		bool result = AVRUNIT_ASSERT_EQUALS_STRING(queue->tail().element, el1.element);

		result = AVRUNIT_ASSERT_EQUALS_STRING(queue->front().element, el0.element);

		Buffer<TestClass> buf(1, &el3);

		*queue << el2 << buf;

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->numberOfElements(), 4);


		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME((*queue)[0].element, el0.element, "operator[]");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME((*queue)[1].element, el1.element, "operator[]");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME((*queue)[2].element, el2.element, "operator[]");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME((*queue)[3].element, el3.element, "operator[]");


		Queue<TestClass> copy = *queue;

		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(copy[0].element, el0.element, "operator[]");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(copy[1].element, el1.element, "operator[]");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(copy[2].element, el2.element, "operator[]");
		result &= AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(copy[3].element, el3.element, "operator[]");


		*queue << copy;

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el1.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el2.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el3.element);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el1.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el2.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el3.element);

		return result;

	}

	bool testresize()
	{

		queue->enQueue(el0);
		queue->enQueue(el1);
		queue->enQueue(el2);
		queue->enQueue(el3);
		queue->enQueue(el4);

		queue->enQueue(el0);
		queue->enQueue(el1);
		queue->enQueue(el2);
		queue->enQueue(el3);
		queue->enQueue(el4);

		bool isFull = !queue->enQueue(el0);

		bool result = AVRUNIT_ASSERT_AUTONAME(isFull);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->numberOfElements(), 10);


		queue->resize(15);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->numberOfElements(), 10);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->capacity(), 15);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el4.element);

		isFull = !queue->enQueue(el2);

		result &= AVRUNIT_ASSERT_AUTONAME(!isFull);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el2.element);

		queue->resize(10);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->numberOfElements(), 10);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->capacity(), 10);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el4.element);


		queue->deQueue();
		queue->deQueue();
		queue->deQueue();
		queue->deQueue();
		queue->deQueue();

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->numberOfElements(), 5);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->capacity(), 10);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el4.element);

		queue->enQueue(el0);
		queue->enQueue(el1);
		queue->enQueue(el2);
		queue->enQueue(el3);
		queue->enQueue(el4);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->numberOfElements(), 10);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->capacity(), 10);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el4.element);


		queue->resize(25);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->numberOfElements(), 10);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->capacity(), 25);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->front().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->tail().element, el4.element);


		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el1.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el2.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el3.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el4.element);

		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el0.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el1.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el2.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el3.element);
		result &= AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(queue->deQueue().element, el4.element);

		return result;

	}
};

#endif /* QUEUETEST_H_ */
