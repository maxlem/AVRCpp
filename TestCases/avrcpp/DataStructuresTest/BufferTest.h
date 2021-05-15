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

#ifndef BufferTest_H_
#define BufferTest_H_

#include "DataStructures/Buffer.h"
#include "TestCase.h"
#include "../../TestClass.h"

class BufferTest :  public TestCase<BufferTest>
{
public:
	BufferTest(const prog_mem * testMethodName_P, TestCase<BufferTest>::TestMethod testMethod) :
	TestCase<BufferTest>(testMethodName_P, testMethod)
	{

	}

	Buffer<char> builder(const char * string)
	{
		Buffer<char> buf(10, string);

		Buffer<char> buf2 = buf;

		printf(buf2.buffer);

		return buf;
	}

	bool testConstructorsDestructors()
	{
		char string[] = "123456789";

		Buffer<char> * buf = new Buffer<char>(10, string);

		bool result = AVRUNIT_ASSERT(buf->buffer != string);

		result &= AVRUNIT_ASSERT(!isNull(buf->buffer));

		result &= AVRUNIT_ASSERT_EQUALS_LONG_AUTONAME(buf->numberOfElements, 10);

		delete buf;

		Buffer<char> buf2 = builder(string);

		result &= AVRUNIT_ASSERT_AUTONAME(!isNull(buf2.buffer));

		result &= AVRUNIT_ASSERT_EQUALS_STRING_NAMED_TESTVALUE(buf2.buffer, string);


		return result;
	}

};
#endif /* BufferTest_H_ */
