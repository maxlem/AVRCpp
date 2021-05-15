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

template <class TestCaseType>
TestCase<TestCaseType>::TestCase(const prog_mem * testMethodName, TestMethod testMethod): testMethodName(testMethodName), testMethod(testMethod), testCase((TestCaseType*)this)
{
}

template <class TestCaseType>
TestCase<TestCaseType>::~TestCase()
{

}

template <class TestCaseType>
void TestCase<TestCaseType>::setUp()
{

}

template <class TestCaseType>
void TestCase<TestCaseType>::tearDown()
{

}

template <class TestCaseType>
void TestCase<TestCaseType>::run(TestResult * result)
{
	AVRUNIT_SET_TESTNAME_P(testMethodName);
	setUp();
	result->testStarted();
	if(!(testCase->*testMethod)()) 	// In most xUnit implementation we would use exceptions, but it is not an option on AVR's
	{
		char * testMethodNameBuffer = strdup(testMethodName, Allocators::STACK);
		result->testFailed(testMethodNameBuffer);
	}
	tearDown();
}
