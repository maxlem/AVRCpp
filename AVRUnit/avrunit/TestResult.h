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

#ifndef TESTRESULT_H_
#define TESTRESULT_H_

#include "Utils/CppExtensions.h"
#include "Utils/Utils.h"
#include <avr/pgmspace.h>

class TestResult
{

public :

	TestResult(size_t summaryBufferLenght = 200, size_t logBufferLenght = 0);
	~TestResult();

	void testStarted();
	void testFailed(const char * testName = NULL);

	size_t getRunCount();

	size_t getErrorCount();

	const char * getSummary();

	const char * getLog();


private:
	size_t errorCount;
	size_t runCount;

	const size_t summaryBufferLenght;
	const size_t logBufferLenght;

	char * summary;
	char * log;

	const prog_mem * summaryFormat;
	const prog_mem * logFormat;
};

#endif /* TESTRESULT_H_ */
