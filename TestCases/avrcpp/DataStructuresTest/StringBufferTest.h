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

#ifndef STRINGBUFFERTEST_H_
#define STRINGBUFFERTEST_H_


#include "DataStructures/Queue.h"
#include "DataStructures/StringBuffer.h"
#include "TestCase.h"
#include "Utils/Utils.h"

class StringBufferTest :  public TestCase<StringBufferTest>
{

	const prog_mem * el0;
	const prog_mem * el1;
	const prog_mem * el2;
	StringBuffer * buffer;

public:


	StringBufferTest(const prog_mem * testMethodName_P, TestCase<StringBufferTest>::TestMethod testMethod) :
	TestCase<StringBufferTest>(testMethodName_P, testMethod),
	el0(PROG_MEM_STRING("const prog_mem *1")), el1(PROG_MEM_STRING("const prog_mem *2")), el2(PROG_MEM_STRING("const prog_mem *3"))
	{

	}

	void setUp()
	{
		buffer = new StringBuffer(10);
	}
	void tearDown()
	{
		delete buffer;
	}

	bool testoperators()
	{
		const char * string = "const string";

		StringBuffer q(20);

		q << string;

		char * qString = NULL;

		qString << q;

		bool result = AVRUNIT_ASSERT_EQUALS_STRING(qString, string);


		const prog_mem * string_P = PROG_MEM_STRING("testoperators");

		q.init();

		q << string_P;

		qString << q;

		result &= AVRUNIT_ASSERT_EQUALS_STRING_P(qString, string_P);

		return result;

	}

};

#endif /* STRINGBUFFERTEST_H_ */
