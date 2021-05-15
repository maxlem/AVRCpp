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

#ifndef LISTTEST_H_
#define LISTTEST_H_


#include "DataStructures/List.h"
#include "TestCase.h"
#include "../../TestClass.h"


class ListTest :  public TestCase<ListTest>
{

	TestClass el0;
	TestClass el1;
	TestClass el2;
	List<TestClass> * list;

public:


	ListTest(const prog_mem * testMethodName_P, TestCase<ListTest>::TestMethod testMethod) :
	TestCase<ListTest>(testMethodName_P, testMethod),
	el0(10, PROG_MEM_STRING("TestClass1")), el1(20, PROG_MEM_STRING("TestClass2")), el2(30, PROG_MEM_STRING("TestClass3"))
	{

	}

	void setUp()
	{
		list = new List<TestClass>();
	}
	void tearDown()
	{
		delete list;
	}

	bool testappend()
	{
		bool result = AVRUNIT_ASSERT(list->isEmpty());

		list->append(el0);
		result &= AVRUNIT_ASSERT(!list->isEmpty());
		result &= AVRUNIT_ASSERT_EQUALS_LONG(list->numberOfElements(), 1);
		list->append(el1);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(list->numberOfElements(), 2);


		TestClass * t = list->element(1);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t->element, 20);

		return result;
	}

	bool testinsertElement()
	{

		bool result = AVRUNIT_ASSERT(list->isEmpty());

		list->insertElement(el0, 0);
		result &= AVRUNIT_ASSERT(!list->isEmpty());
		result &= AVRUNIT_ASSERT_EQUALS_LONG(list->numberOfElements(), 1);
		list->insertElement(el2, 0);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(list->numberOfElements(), 2);


		TestClass * t = list->element(1);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t->element, 10);

		t = list->element(0);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t->element, 30);

		return result;

	}

	bool testremove()
	{
		bool result = AVRUNIT_ASSERT(list->isEmpty());

		list->append(el0);
		list->append(el1);
		list->append(el2);

		TestClass * t = list->element(0);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t->element, 10);

		t = list->element(1);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t->element, 20);

		result &= AVRUNIT_ASSERT(list->remove(el0));

		t = list->element(0);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(t->element, 20);

		return result;
	}

	bool testnumberOfElements()
	{
		bool result = AVRUNIT_ASSERT_EQUALS_LONG(list->numberOfElements(), 0);

		list->append(el0);
		list->append(el1);
		list->append(el2);
		list->append(el0);
		list->append(el0);
		list->append(el0);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(list->numberOfElements(), 6);
		return result;
	}

	bool testisEmpty()
	{
		bool result = AVRUNIT_ASSERT(list->isEmpty());

		list->append(el0);
		list->append(el1);
		list->append(el2);

		result &= AVRUNIT_ASSERT(!list->isEmpty());

		list->remove(el0);
		list->remove(el1);
		list->remove(el2);

		result &= AVRUNIT_ASSERT(list->isEmpty());

		return result;
	}

	bool testelement()
	{
		list->append(el0);
		list->append(el1);
		list->append(el2);

		TestClass * t = list->element(0);
		bool result = AVRUNIT_ASSERT_EQUALS_LONG(t->element, 10);

		t = list->element(10);

		result &= AVRUNIT_ASSERT(isNull(t));

		return result;
	}

	bool testposition()
	{
		list->append(el0);
		list->append(el1);
		list->append(el2);

		size_t pos = list->position(el1);
		bool result = AVRUNIT_ASSERT_EQUALS_LONG(pos, 1);

		list->remove(el0);
		pos = list->position(el0);
		result &= AVRUNIT_ASSERT_EQUALS_LONG(pos, SIZE_MAX);

		return result;

	}

	bool testAssign()
	{
		list->append(el0);
		list->append(el1);
		list->append(el2);

		List<TestClass> copy = *list;
		TestClass * t = copy.element(0);
		bool result = AVRUNIT_ASSERT_EQUALS_LONG(t->element, 10);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(copy.numberOfElements(), 3);

		return result;
	}

	bool testElements()
	{
		list->append(el0);
		list->append(el1);
		list->append(el2);

		List<TestClass>::ListIterator iter = list->elements();

		TestClass * t = iter.current();

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(t->element, 10);

		t = iter.next();

		result &= AVRUNIT_ASSERT_EQUALS_LONG(t->element, 20);

		iter.next();

		result &= AVRUNIT_ASSERT(!iter.hasNext());

		return result;
	}

};

#endif /* LISTTEST_H_ */
