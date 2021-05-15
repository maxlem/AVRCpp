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

#ifndef RegexTest_H_
#define RegexTest_H_

#include "TestAssert.h"
#include "Utils/Utils.h"
#include "RegularExpressions/regexp/regexp.h"
#include "RegularExpressions/RegularExpression.h"
#include "RegularExpressions/Result.h"

using RegularExpressions::RegularExpression;
using RegularExpressions::Result;


class RegexTest : public TestCase<RegexTest>
{

public:

	RegexTest(const prog_mem * testMethodName_P, TestCase<RegexTest>::TestMethod testMethod) :
	TestCase<RegexTest>(testMethodName_P, testMethod),
	simpleRegex(PROG_MEM_STRING("group_1_a")),
	groupsRegex(PROG_MEM_STRING("(group_1_[a-z]).*(2_b)")),
	text(PROG_MEM_STRING("group_1_a group_2_b"))
	{

	}

	bool testregexp()
	{

	    regexp* compiled = regcomp(simpleRegex);

	    int retval = regexec(compiled, text);

	    bool result = AVRUNIT_ASSERT_EQUALS_LONG(retval, 1);

	    size_t matchTextLenght = compiled->endp[0] - compiled->startp[0];

	    result &= AVRUNIT_ASSERT_EQUALS_LONG(matchTextLenght, 9);

	    free(compiled);

	    compiled = regcomp(groupsRegex);

	    retval = regexec(compiled, text);

	    result &= AVRUNIT_ASSERT_EQUALS_LONG(retval, 1);

	    size_t group0Lenght = compiled->endp[0] - compiled->startp[0];

	    size_t group1Lenght = compiled->endp[1] - compiled->startp[1];

	    size_t group2Lenght = compiled->endp[2] - compiled->startp[2];

	    result &= AVRUNIT_ASSERT_EQUALS_LONG(group0Lenght, strlen(text));

	    result &= AVRUNIT_ASSERT_EQUALS_LONG(group1Lenght, 9);

	    result &= AVRUNIT_ASSERT_EQUALS_LONG(group2Lenght, 3);

	    free(compiled);

	    return result;
	}


	bool testRegularExpression()
	{

		RegularExpression simpleRe(simpleRegex);

		Result * res = simpleRe.parse(text);

		bool result = AVRUNIT_ASSERT(!isNull(res));

		result &= AVRUNIT_ASSERT_EQUALS_LONG(res->getGroup(0)->lenght, 9);

	    delete res;

		RegularExpression groupsRe(groupsRegex);

		res = groupsRe.parse(text);

		result &= AVRUNIT_ASSERT(!isNull(res));

		result &= AVRUNIT_ASSERT_EQUALS_LONG(res->getGroup(0)->lenght, strlen(text));

		result &= AVRUNIT_ASSERT_EQUALS_LONG(res->getGroup(1)->lenght, 9);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(res->getGroup(2)->lenght, 3);

	    delete res;

	    return result;
	}

protected:
	const prog_mem * simpleRegex;
	const prog_mem * groupsRegex;
	const prog_mem * text;

};

#endif /* RegexTest_H_ */
