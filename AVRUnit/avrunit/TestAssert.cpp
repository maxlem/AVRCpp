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

#include "TestAssert.h"

#include "Utils/Utils.h"
#include "Utils/BitManipulation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace Allocators;

TestAssert::TestAssert() :
failureCallBack(NULL), successCallBack(NULL), messageCallBack(NULL),
notEqualsFormatString(PROG_MEM_STRING("Expected %s but was %s \n\r")), notInRangeformatString(PROG_MEM_STRING("Expected %s to be %s than %s \n\r")),
assertFormatString(PROG_MEM_STRING("%s:%s")), failFormatString(PROG_MEM_STRING("%s: FAIL!\n\n\r")), successFormatString(PROG_MEM_STRING("%s: OK!\n\n\r"))
{
	this->currentSuiteName = strdup(PROG_MEM_STRING("None"));
	this->currentTestName = strdup(PROG_MEM_STRING("None"));
}

TestAssert::~TestAssert()
{
	delete this->currentSuiteName;
	delete this->currentTestName;
}

void TestAssert::failure()
{
	if(!isNull(failureCallBack))
		failureCallBack();
}

void TestAssert::success()
{
	if(!isNull(successCallBack))
		successCallBack();
}

void TestAssert::failure(char * message)
{

	if(!isNull(messageCallBack))
	{
		char * newMessage = new(STACK) char[strlen(failFormatString) + strlen(message) + 1];
		sprintf(newMessage, failFormatString, message);
		messageCallBack(newMessage);
	}

	failure();

}

void TestAssert::success(char * message)
{

	if(!isNull(messageCallBack))
	{
		char * newMessage = new(STACK) char[strlen(successFormatString) + strlen(message) + 1];
		sprintf(newMessage, successFormatString, message);
		messageCallBack(newMessage);
	}

	success();

}
TestAssert * TestAssert::getInstance()
{
	static TestAssert * instance;

	if(isNull(instance))
	{
		instance = new TestAssert(); //TODO check if fmt string changed
	}
	return instance;
}

void TestAssert::configure(	void (*failureCallBack)(void), void (*successCallBack)(void), void (*messageCallBack)(const char*))
{
	this->failureCallBack = failureCallBack;
	this->successCallBack = successCallBack;
	this->messageCallBack = messageCallBack;
}


bool TestAssert::assertEquals(void* testValue, void* targetValue, const prog_mem * testName)
{

	if(!assert((testValue == targetValue), testName))
	{
		if(!isNull(messageCallBack))
		{
			char * testValueBuffer = new(STACK) char[MAX_DIGITS];
			char * targetValueBuffer = new(STACK) char[MAX_DIGITS];

			sprintf(testValueBuffer, "%p", testValue);
			sprintf(targetValueBuffer, "%p", targetValue);

			printErrorDetails(testValueBuffer, targetValueBuffer);
		}

		return false;
	}
	return true;
}
bool TestAssert::assertEquals(long long testValue, long long targetValue, const prog_mem * testName)
{
	if(!assert((testValue == targetValue), testName))
	{
		if(!isNull(messageCallBack))
		{
			char * testValueBuffer = new(STACK) char[MAX_DIGITS];
			char * targetValueBuffer = new(STACK) char[MAX_DIGITS];
			printErrorDetails(ltoa(testValue, testValueBuffer, 10), ltoa(targetValue, targetValueBuffer, 10));
		}

		return false;
	}
	return true;
}

bool TestAssert::assertEquals(double testValue, double targetValue, const prog_mem * testName)
{
	if(!assert((testValue == targetValue), testName))
	{
		if(!isNull(messageCallBack))
		{
			char * testValueBuffer = new(STACK) char[MAX_DIGITS];
			char * targetValueBuffer = new(STACK) char[MAX_DIGITS];
			printErrorDetails(dtostre(testValue, testValueBuffer, 10, 0x00), dtostre(targetValue, targetValueBuffer, 10, 0x00));

			return false;
		}

	return false;
	}

	return true;
}

bool TestAssert::assertEquals(const char* testValue, const char * targetValue, const prog_mem * testName)
{
	if(isNull(testValue))
		return false;

	if(!assert(strcmp(testValue, targetValue) == 0, testName))
	{
		if(!isNull(messageCallBack))
			printErrorDetails(testValue, targetValue);

		return false;
	}

	return true;
}


bool TestAssert::assertEquals(const char* testValue, const prog_mem * targetValue, const prog_mem * testName)
{
	if(isNull(testValue))
		return false;



	if(!assert(strcmp(testValue, targetValue) == 0, testName))
	{
		if(!isNull(messageCallBack))
		{
			char * targetValueBuffer = strdup(targetValue, STACK);
			printErrorDetails(testValue, targetValueBuffer);
		}
		return false;
	}

	return true;
}

bool TestAssert::assertEquals(char testValue, char targetValue, const prog_mem * testName)
{
	char testValueBuffer[4] = {'\'', testValue, '\'', '\0'};

	char targetValueBuffer[4] = {'\'', targetValue, '\'', '\0'};

	return assertEquals(testValueBuffer, targetValueBuffer, testName);

}


bool TestAssert::assertInRange(long long testValue, long long targetValue, long long delta, const prog_mem * testName)
{

	char * testValueBuffer = new(STACK) char[MAX_DIGITS];
	ltoa(testValue, testValueBuffer, 10);
	char * targetValueBuffer = new(STACK) char[MAX_DIGITS];

	if(!((targetValue - delta) < testValue))
	{
		assert(false, testName);
		ltoa((targetValue - delta), targetValueBuffer, 10);
		char * comparison= strdup(PROG_MEM_STRING("larger"), STACK);
		printErrorDetails(testValueBuffer, comparison, targetValueBuffer);
		return false;
	}
	else if (!(testValue < (targetValue + delta)))
	{
		assert(false, testName);
		ltoa(targetValue + delta, targetValueBuffer, 10);
		char * comparison = strdup(PROG_MEM_STRING("smaller"), STACK);
		printErrorDetails(testValueBuffer, comparison, targetValueBuffer);
		return false;
	}

	return assert(true, testName);
}

bool TestAssert::assertInRange(double testValue, double targetValue, double delta, const prog_mem * testName)
{

	char * testValueBuffer = new(STACK) char[MAX_DIGITS];
	dtostre(testValue, testValueBuffer, 10, 0x00);
	char * targetValueBuffer = new(STACK) char[MAX_DIGITS];

	if(!((targetValue - delta) < testValue))
	{
		assert(false, testName);
		dtostre((targetValue - delta), targetValueBuffer, 10, 0x00);
		char * comparison = strdup(PROG_MEM_STRING("larger"), STACK);
		printErrorDetails(testValueBuffer, comparison, targetValueBuffer);
		return false;
	}
	else if (!(testValue < (targetValue + delta)))
	{
		assert(false, testName);
		dtostre((targetValue + delta), targetValueBuffer, 10, 0x00);
		char * comparison = strdup(PROG_MEM_STRING("smaller"), STACK);
		printErrorDetails(testValueBuffer, comparison, targetValueBuffer);
		return false;
	}

	return assert(true, testName);
}

void TestAssert::printErrorDetails(const char* testValue, const char * targetValue)
{
	char * message = new(STACK) char[strlen(notEqualsFormatString) + strlen(testValue) + strlen(targetValue) + 1];

	sprintf(message, notEqualsFormatString, targetValue, testValue);

	messageCallBack(message);
}

void TestAssert::printErrorDetails(const char* testValue, const char* comparison, const char * targetValue)
{
	char * message = new(STACK) char[strlen(notInRangeformatString) + strlen(testValue) + strlen(targetValue) + strlen(comparison) + 1];

	sprintf(message, notInRangeformatString, testValue, comparison, targetValue);

	messageCallBack(message);
}

bool TestAssert::assert(bool value, const prog_mem * testName)
{
	currentTestName = setTestName(testName);

	char * message = new(STACK) char[strlen(assertFormatString) + strlen(currentSuiteName) + strlen(currentTestName) + 1];

	sprintf(message, assertFormatString, currentSuiteName, currentTestName);

	if(value)
		success(message);
	else
		failure(message);

	return value;
}


char * TestAssert::setTestName(const prog_mem * testName)
{
	if(!isNull(testName))
		currentTestName = strdup(currentTestName, testName);

	return currentTestName;
}

char * TestAssert::setSuiteName(const prog_mem * suiteName)
{
	if(!isNull(suiteName))
		currentSuiteName = strdup(currentSuiteName, suiteName);

	return currentSuiteName;
}
