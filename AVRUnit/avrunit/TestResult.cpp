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

#include "TestResult.h"
#include "Utils/Utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

TestResult::TestResult(size_t summaryBufferLenght, size_t logBufferLenght):
errorCount(0), runCount(0), summaryBufferLenght(summaryBufferLenght), logBufferLenght(logBufferLenght),
summary(NULL), log(NULL),
summaryFormat(PROG_MEM_STRING("%s run, %s failed")), logFormat(PROG_MEM_STRING("Test \'%s\' failed!\n\r"))
{



	if(logBufferLenght > 0)
	{
		log = new char[logBufferLenght];
		log[0] = '\0';
	}
}



TestResult::~TestResult()
{
	if(!isNull(summary))
		delete summary;

	if(!isNull(log))
		delete log;
}
void TestResult::testStarted()
{
	runCount++;
}

void TestResult::testFailed(const char * testName)
{
	errorCount++;

	if(logBufferLenght == 0)
		return;

	size_t logLenght = strlen(log);

	if(!isNull(testName) && (logBufferLenght > (logLenght + strlen(logFormat) + strlen(testName) + 1)) )
	{
		sprintf(&log[logLenght], logFormat, testName);
		printf(log);
	}


}

size_t TestResult::getRunCount()
{
	return runCount;
}

size_t TestResult::getErrorCount()
{
	return errorCount;
}

const char * TestResult::getSummary()
{
	char * runString = new(Allocators::STACK) char[15];
	char * errString = new(Allocators::STACK) char[15];

	ultoa(getRunCount(), runString, 10);
	ultoa(getErrorCount(), errString, 10);

	size_t runStringLen = strlen(runString);
	size_t errStringLen = strlen(errString);


	size_t summaryLen = strlen(summaryFormat) + runStringLen + errStringLen + 1; // NEVER FORGET THAT NULL CHAR AGAIN

	if(summaryBufferLenght > summaryLen)
	{
		if(isNull(summary))
			summary = new char[summaryLen];
		else
			summary = new(summary) char[summaryLen];

		sprintf(summary, summaryFormat, runString, errString);
		return summary;
	}

	return "No Summary";
}

const char * TestResult::getLog()
{
	return log;
}
