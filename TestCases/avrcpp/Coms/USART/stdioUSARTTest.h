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

#ifndef stdioUSARTTest_H_
#define stdioUSARTTest_H_

#include "TestCase.h"
#include "Coms/USART/stdio/stdioUSART.h"

class stdioUSARTTest : public TestCase<stdioUSARTTest>
{
public:

	stdioUSARTTest(const prog_mem * testMethodName_P, TestCase<stdioUSARTTest>::TestMethod testMethod) :
	TestCase<stdioUSARTTest>(testMethodName_P, testMethod)
	{

	}

	bool testLoopback()
	{
		bool result = true;

		FILE * stddev = Coms::USART::fdevopen(_FDEV_SETUP_RW, USARTHardware::getUSARTHardware(3));

		fprintf(stddev, "a");

		char c;

		fscanf(stddev, "%c", &c);


		result &= AVRUNIT_ASSERT_EQUALS_CHAR(c, 'a');

		Coms::USART::fdevclose(_FDEV_SETUP_RW, stddev);

		return result;

	}

private:


};

#endif /* stdioUSARTTest_H_ */
