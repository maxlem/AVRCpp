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

#ifndef CallbackServersTest_H_
#define CallbackServersTest_H_

#include "TestCase.h"
#include "Coms/USART/USARTHardware.h"
#include "CallbackServers/DictionnaryCallbackServer.h"
#include "CallbackServers/FastCallbackServer.h"
#include <stdio.h>

#include "MockCallback.h"

using Coms::USART::USARTHardware;

class CallbackServersTest : public TestCase<CallbackServersTest>
{
public:

	CallbackServersTest(const prog_mem * testMethodName_P, TestCase<CallbackServersTest>::TestMethod testMethod) :
	TestCase<CallbackServersTest>(testMethodName_P, testMethod)
	{
		usartHardware = USARTHardware::getUSARTHardware(1);

	}

	~CallbackServersTest()
	{
	}

	bool testDictionnaryCallbackServer()
	{

		MockCallback * mockCallback = new MockCallback();
		DictionnaryCallbackServer::getInstance()->connect(USART1_UDRE_vect, mockCallback);
		usartHardware->enableTransmitter();
		usartHardware->enableTransmitterReadyInterrupts();

		bool result = AVRUNIT_ASSERT(!mockCallback->calledBack);

		enableInterrupts();
		delay(1);
		disableInterrupts();

		result &= AVRUNIT_ASSERT(mockCallback->calledBack);



		usartHardware->disableTransmitter();
		usartHardware->disableTransmitterReadyInterrupts();

		DictionnaryCallbackServer::getInstance()->disconnect(USART1_UDRE_vect);
		delete mockCallback;
		return result;
	}

	bool testFastCallbackServer()
	{
		MockCallback * mockCallback = new MockCallback();
		FastCallbackServer::getInstance()->connect(30, mockCallback);
		usartHardware->enableTransmitter();
		usartHardware->enableReceiver();
		usartHardware->enableFrameReceivedInterrupts();

		bool result = AVRUNIT_ASSERT(!mockCallback->calledBack);

		enableInterrupts();
		usartHardware->writeFrame('a');

		while(!usartHardware->isFrameReceived());
		disableInterrupts();

		result &= AVRUNIT_ASSERT(mockCallback->calledBack);



		usartHardware->disableTransmitter();
		usartHardware->disableReceiver();
		usartHardware->disableFrameReceivedInterrupts();


		FastCallbackServer::getInstance()->disconnect(30);
		delete mockCallback;
		return result;
	}


private:
	USARTHardware * usartHardware;
};



#endif /* CallbackServersTest_H_ */
