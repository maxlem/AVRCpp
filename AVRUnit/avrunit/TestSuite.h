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

#ifndef TESTSUITE_H_
#define TESTSUITE_H_
#include "Utils/Utils.h"
#include "DataStructures/List.h"
#include "TestResult.h"
#include "TestAssert.h"

template <class TestCaseType>
class TestSuite {

public:
	TestSuite(const prog_mem * testSuiteName, bool deleteTestCasesInDestructor = true);

	virtual ~TestSuite();


	bool add(TestCaseType * testCase);

	void run(TestResult * result);

private:

	const prog_mem * testSuiteName;
	List<TestCaseType * > * testMethods;
	bool deleteTestCasesInDestructor;
};

#include "TestSuite-definitions.h"

#define AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, methodNameNoQuotes)\
	testSuitePtr->add(new TestCaseClass(PROG_MEM_STRING(#methodNameNoQuotes), &TestCaseClass::methodNameNoQuotes))

#define AVRUNIT_SUITE_ADD_2_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes)\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method1NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method2NameNoQuotes)

#define AVRUNIT_SUITE_ADD_3_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes)\
	AVRUNIT_SUITE_ADD_2_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method3NameNoQuotes)

#define AVRUNIT_SUITE_ADD_4_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes)\
	AVRUNIT_SUITE_ADD_3_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method4NameNoQuotes)

#define AVRUNIT_SUITE_ADD_5_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes)\
	AVRUNIT_SUITE_ADD_4_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method5NameNoQuotes)

#define AVRUNIT_SUITE_ADD_6_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes)\
	AVRUNIT_SUITE_ADD_5_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method6NameNoQuotes)

#define AVRUNIT_SUITE_ADD_7_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes)\
	AVRUNIT_SUITE_ADD_6_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method7NameNoQuotes)

#define AVRUNIT_SUITE_ADD_8_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes)\
	AVRUNIT_SUITE_ADD_7_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method8NameNoQuotes)

#define AVRUNIT_SUITE_ADD_9_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes, method9NameNoQuotes)\
	AVRUNIT_SUITE_ADD_8_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method9NameNoQuotes)

#define AVRUNIT_SUITE_ADD_10_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes, method9NameNoQuotes, method10NameNoQuotes)\
	AVRUNIT_SUITE_ADD_9_TESTS(testSuitePtr, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes, method9NameNoQuotes);\
	AVRUNIT_SUITE_ADD_TEST(testSuitePtr, TestCaseClass, method10NameNoQuotes)


#define AVRUNIT_DECLARE_SUITE(TestCaseClass)\
	TestCaseClass::SuiteType * suiteOf##TestCaseClass = new TestCaseClass::SuiteType(STRINGNIFY_P(suiteOf##TestCaseClass), true)

#define AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)\
	suiteOf##TestCaseClass->run(resultPtr);\
	delete suiteOf##TestCaseClass

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE(TestCaseClass, resultPtr, methodNameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_TEST(suiteOf##TestCaseClass, TestCaseClass, methodNameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_2_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_2_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_3_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_3_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_4_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_4_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_5_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_5_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_6_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_6_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_7_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_7_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_8_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_8_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_9_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes, method9NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_9_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes, method9NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)

#define AVRUNIT_DECLARE_RUN_DELETE_SUITE_10_TESTS(TestCaseClass, resultPtr, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes, method9NameNoQuotes, method10NameNoQuotes)\
	AVRUNIT_DECLARE_SUITE(TestCaseClass);\
	AVRUNIT_SUITE_ADD_10_TESTS(suiteOf##TestCaseClass, TestCaseClass, method1NameNoQuotes, method2NameNoQuotes, method3NameNoQuotes, method4NameNoQuotes, method5NameNoQuotes, method6NameNoQuotes, method7NameNoQuotes, method8NameNoQuotes, method9NameNoQuotes, method10NameNoQuotes);\
	AVRUNIT_RUN_DELETE_SUITE(TestCaseClass, resultPtr)
#endif /* TESTSUITE_H_ */
