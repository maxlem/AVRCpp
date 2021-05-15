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

#ifndef TESTASSERT_H_
#define TESTASSERT_H_

#define MAX_DIGITS 25

#include "Utils/CppExtensions.h"
#include "Utils/Utils.h"
#include <stddef.h>
#include <avr/pgmspace.h>

class TestAssert
{
protected:

	/*!
	 * This class is a singleton
	 * @see \a getInstance() and \a configure()
	 */
	TestAssert();

	~TestAssert();

public:



	void failure();

	void success();

	void failure(char * message);

	void success(char * message);

	/*!
	 * The singleton accessor
	 * @return the unique instance to the class TestAssert
	 * @warning <b> Don't forget to configure the class, or you won't see nothing! </b>
	 */
	static TestAssert * getInstance();

	/*!
	 * Configures the result presentation medium
	 * @param failureCallBack called back upon failures
	 * @param successCallBack called cakc upon success
	 * @param messageCallBack called back with a output message
	 */
	void configure(	void (*failureCallBack)(void), void (*successCallBack)(void), void (*messageCallBack)(const char*) = NULL);


	bool assertEquals(void* testValue, void* targetValue, const prog_mem * testName = NULL);

	bool assertEquals(long long testValue, long long targetValue, const prog_mem * testName = NULL);

	bool assertEquals(double testValue, double targetValue, const prog_mem * testName = NULL);

	bool assertEquals(const char* testValue, const char * targetValue, const prog_mem * testName = NULL);

	bool assertEquals(const char* testValue, const prog_mem * targetValue, const prog_mem * testName = NULL);

	bool assertEquals(char testValue, char targetValue, const prog_mem * testName = NULL);

	bool assertInRange(long long testValue, long long targetValue, long long delta, const prog_mem * testName = NULL);

	bool assertInRange(double testValue, double targetValue, double delta, const prog_mem * testName = NULL);

	void printErrorDetails(const char* testValue, const char * targetValue);

	void printErrorDetails(const char* testValue, const char* comparison, const char * targetValue);

	bool assert(bool value, const prog_mem * testName = NULL);

	char * setTestName(const prog_mem * testName);

	char * setSuiteName(const prog_mem * suiteName);
private:

	void (*failureCallBack)(void);
	void (*successCallBack)(void);
	void (*messageCallBack)(const char*);

	const prog_mem * notEqualsFormatString;
	const prog_mem * notInRangeformatString;
	const prog_mem * assertFormatString;
	const prog_mem * failFormatString;
	const prog_mem * successFormatString;

	char * currentSuiteName;
	char * currentTestName;
};

#define AVRUNIT_MACRO_TO_STRING(val)	#val
#define AVRUNIT_MACRO_TO_STRING_P(val)	PROG_MEM_STRING(#val)

#define AVRUNIT_SHOULD_EQUALS(testValue, targetValue)	AVRUNIT_MACRO_TO_STRING(testValue##__should_equals_to__##targetValue)

#define AVRUNIT_CONFIGURE_ASSERT_NO_CONSOLE(failureCallBack, successCallBack)				TestAssert::getInstance()->configure(failureCallBack, successCallBack)
#define AVRUNIT_CONFIGURE_ASSERT(failureCallBack, successCallBack, consoleCallBack)			TestAssert::getInstance()->configure(failureCallBack, successCallBack, consoleCallBack)

#define AVRUNIT_SET_SUITENAME_P(suiteName)										TestAssert::getInstance()->setSuiteName(suiteName)
#define AVRUNIT_SET_TESTNAME_P(testName)										TestAssert::getInstance()->setTestName(testName)

#define AVRUNIT_FAIL(message)													TestAssert::getInstance()->failure(message)

#define AVRUNIT_ASSERT(value)													TestAssert::getInstance()->assert(value)
#define AVRUNIT_ASSERT_TESTNAME(value, testName)								TestAssert::getInstance()->assert(value, PROG_MEM_STRING(testName))
#define AVRUNIT_ASSERT_AUTONAME(value)											TestAssert::getInstance()->assert(value, PROG_MEM_STRING(#value))

#define AVRUNIT_ASSERT_EQUALS(testValue, targetValue)							TestAssert::getInstance()->assertEquals(testValue, targetValue)
#define AVRUNIT_ASSERT_EQUALS_TESTNAME(testValue, targetValue, testName)		TestAssert::getInstance()->assertEquals(testValue, targetValue, PROG_MEM_STRING(testName))
#define AVRUNIT_ASSERT_EQUALS_AUTONAME(testValue, targetValue)					TestAssert::getInstance()->assertEquals(testValue, targetValue, PROG_MEM_STRING(#testValue))

#define AVRUNIT_ASSERT_EQUALS_LONG(testValue, targetValue)						AVRUNIT_ASSERT_EQUALS((long long)testValue, (long long)targetValue)
#define AVRUNIT_ASSERT_EQUALS_LONG_TESTNAME(testValue, targetValue, testName)	AVRUNIT_ASSERT_EQUALS_TESTNAME((long long)testValue, (long long)targetValue, testName)
#define AVRUNIT_ASSERT_EQUALS_LONG_AUTONAME(testValue, targetValue)				AVRUNIT_ASSERT_EQUALS_TESTNAME((long long)testValue, (long long)targetValue, AVRUNIT_SHOULD_EQUALS(testValue, targetValue))
#define AVRUNIT_ASSERT_EQUALS_LONG_NAMED_TESTVALUE(testValue, targetValue)		AVRUNIT_ASSERT_EQUALS_TESTNAME((long long)testValue, (long long)targetValue, AVRUNIT_MACRO_TO_STRING(Value_Test_is_##testValue))
#define AVRUNIT_ASSERT_EQUALS_LONG_NAMED_ASSERT_TARGET(testValue, targetValue)	AVRUNIT_ASSERT_EQUALS_TESTNAME((long long)testValue, (long long)targetValue, AVRUNIT_MACRO_TO_STRING(Target_is_##targetValue))


#define AVRUNIT_ASSERT_IN_RANGE_LONG(testValue, targetValue, delta)							TestAssert::getInstance()->assertInRange((long long)testValue, (long long)targetValue, (long long)delta)
#define AVRUNIT_ASSERT_IN_RANGE_LONG_TESTNAME(testValue, targetValue, delta, testName)		TestAssert::getInstance()->assertInRange((long long)testValue, (long long)targetValue, (long long)delta, PROG_MEM_STRING(testName))
#define AVRUNIT_ASSERT_IN_RANGE_LONG_NAMED_TESTVALUE(testValue, targetValue, delta)			AVRUNIT_ASSERT_IN_RANGE_LONG_TESTNAME(testValue, targetValue, delta, #testValue)


#define AVRUNIT_ASSERT_EQUALS_DOUBLE(testValue, targetValue)						AVRUNIT_ASSERT_EQUALS((double)testValue, (double)targetValue)
#define AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(testValue, targetValue, testName)		AVRUNIT_ASSERT_EQUALS_TESTNAME((double)testValue, (double)targetValue, testName)
#define AVRUNIT_ASSERT_EQUALS_DOUBLE_AUTONAME(testValue, targetValue)				AVRUNIT_ASSERT_EQUALS_TESTNAME((double)testValue, (double)targetValue, AVRUNIT_SHOULD_EQUALS(testValue, targetValue))
#define AVRUNIT_ASSERT_EQUALS_DOUBLE_NAMED_TESTVALUE(testValue, targetValue)		AVRUNIT_ASSERT_EQUALS_TESTNAME((double)testValue, (double)targetValue, AVRUNIT_MACRO_TO_STRING(Value_Test_is_##testValue))
#define AVRUNIT_ASSERT_EQUALS_DOUBLE_NAMED_ASSERT_TARGET(testValue, targetValue)	AVRUNIT_ASSERT_EQUALS_TESTNAME((double)testValue, (double)targetValue, AVRUNIT_MACRO_TO_STRING(Target_is_##targetValue))

#define AVRUNIT_ASSERT_IN_RANGE_DOUBLE(testValue, targetValue, delta)							TestAssert::getInstance()->assertInRange((double)testValue, (double)targetValue, (double)delta)
#define AVRUNIT_ASSERT_IN_RANGE_DOUBLE_TESTNAME(testValue, targetValue, delta, testName)		TestAssert::getInstance()->assertInRange((double)testValue, (double)targetValue, (double)delta, PROG_MEM_STRING(testName))
#define AVRUNIT_ASSERT_IN_RANGE_DOUBLE_NAMED_TESTVALUE(testValue, targetValue, delta)			AVRUNIT_ASSERT_IN_RANGE_DOUBLE_TESTNAME(testValue, targetValue, delta, #testValue)

#define AVRUNIT_ASSERT_EQUALS_STRING(testValue, targetValue)						AVRUNIT_ASSERT_EQUALS((const char *)testValue, (const char*)targetValue)
#define AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME(testValue, targetValue, testName)		AVRUNIT_ASSERT_EQUALS_TESTNAME((const char *)testValue, (const char*)targetValue, testName)
#define AVRUNIT_ASSERT_EQUALS_STRING_NAMED_TESTVALUE(testValue, targetValue)		AVRUNIT_ASSERT_EQUALS_TESTNAME((const char *)testValue, (const char *)targetValue, AVRUNIT_MACRO_TO_STRING(Value_Test_is_##testValue))

#define AVRUNIT_ASSERT_EQUALS_STRING_P(testValue, targetValue)						TestAssert::getInstance()->assertEquals(testValue, targetValue)
#define AVRUNIT_ASSERT_EQUALS_STRING_TESTNAME_P(testValue, targetValue, testName)	TestAssert::getInstance()->assertEquals(testValue, targetValue, PROG_MEM_STRING(testName))
#define AVRUNIT_ASSERT_EQUALS_STRING_NAMED_TESTVALUE_P(testValue, targetValue)		TestAssert::getInstance()->assertEquals(testValue, targetValue, PROG_MEM_STRING(AVRUNIT_MACRO_TO_STRING(Value_Test_is_##testValue))

#define AVRUNIT_ASSERT_EQUALS_CHAR(testValue, targetValue)						AVRUNIT_ASSERT_EQUALS((char)testValue, (char)targetValue)
#define AVRUNIT_ASSERT_EQUALS_CHAR_TESTNAME(testValue, targetValue, testName)	AVRUNIT_ASSERT_EQUALS_TESTNAME((char)testValue, (char)targetValue, testName)
#define AVRUNIT_ASSERT_EQUALS_CHAR_NAMED_TESTVALUE(testValue, targetValue)		AVRUNIT_ASSERT_EQUALS_TESTNAME((char)testValue, (char)targetValue, AVRUNIT_MACRO_TO_STRING(Value_Test_is_##testValue))

#define AVRUNIT_ASSERT_EQUALS_PTR(testValue, targetValue)							AVRUNIT_ASSERT_EQUALS((void*)testValue, (void*)targetValue)
#define AVRUNIT_ASSERT_EQUALS_PTR_TESTNAME(testValue, targetValue, testName)		AVRUNIT_ASSERT_EQUALS_TESTNAME((void*)testValue, (void*)targetValue, testName)
#define AVRUNIT_ASSERT_EQUALS_PTR_AUTONAME(testValue, targetValue)				AVRUNIT_ASSERT_EQUALS_TESTNAME((void*)testValue, (void*)targetValue, AVRUNIT_SHOULD_EQUALS(testValue, targetValue))
#define AVRUNIT_ASSERT_EQUALS_PTR_NAMED_TESTVALUE(testValue, targetValue)			AVRUNIT_ASSERT_EQUALS_TESTNAME((void*)testValue, (void*)targetValue, AVRUNIT_MACRO_TO_STRING(Value_Test_is_##testValue))
#define AVRUNIT_ASSERT_EQUALS_PTR_NAMED_ASSERT_TARGET(testValue, targetValue)		AVRUNIT_ASSERT_EQUALS_TESTNAME((void*)testValue, (void*)targetValue, AVRUNIT_MACRO_TO_STRING(Target_is_##targetValue))




#endif /* TESTASSERT_H_ */
