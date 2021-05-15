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

#ifndef ActiveBufferedUSARTTest_H_
#define ActiveBufferedUSARTTest_H_

#include "TestCase.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSART.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSARTFrameReceivedCallback.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSARTTransmitterReadyCallback.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveActiveStringBuffer.h"
#include "DataStructures/ActiveBuffers/ActiveTransmitBuffers/TransmitActiveStringBuffer.h"
#include "CallbackServers/FastCallbackServer.h"
#include "Utils/Delay.h"

#include <stdio.h>


//DECLARE_CALLBACK(USART3_RX_vect);
//DECLARE_CALLBACK(USART3_UDRE_vect);
//DECLARE_CALLBACK(USART3_TX_vect);


//using Coms::USART::ActiveBufferedUSART;
using Coms::USART::USARTHardware;
using Coms::USART::ActiveBufferedUSARTFrameReceivedCallback;
using Coms::USART::ActiveBufferedUSARTTransmitterReadyCallback;
#define READ_MARGIN 10

class ActiveBufferedUSARTTest : public TestCase<ActiveBufferedUSARTTest>
{
public:

	ActiveBufferedUSARTTest(const prog_mem * testMethodName_P, TestCase<ActiveBufferedUSARTTest>::TestMethod testMethod) :
	TestCase<ActiveBufferedUSARTTest>(testMethodName_P, testMethod),
	message(PROG_MEM_STRING("Com_TEST123"))
	{
		usartHardware = USARTHardware::getUSARTHardware(3);

	}

	void setUp()
	{
		printf(PROG_MEM_STRING("Connect RX and TX together (loopback mode)\n\r"));

		comUSART = new Coms::USART::ActiveBufferedUSART(usartHardware);

		enableInterrupts();
	}

	void tearDown()
	{
		disableInterrupts();

		delete comUSART;
	}

	bool testLoopbackSingleChar()
	{


		TransmitActiveStringBuffer * tbuf = new TransmitActiveStringBuffer(1);
		*tbuf << 'a';
		comUSART->setCurrentTransmitBuffer(tbuf);
		comUSART->enableTransmitter();

		ReceiveActiveStringBuffer * rbuf = new ReceiveActiveStringBuffer(1);
		comUSART->setCurrentReceiveBuffer(rbuf);
		comUSART->enableReceiver();

		comUSART->flushCurrentTransmitBuffer(); // will write one byte
		comUSART->fillCurrentReceiveBuffer(); // will read the byte just written

		bool result = AVRUNIT_ASSERT_EQUALS_LONG(rbuf->numberOfElements(), 1);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(usartHardware->status(), 0);

		result &= AVRUNIT_ASSERT_EQUALS_CHAR(rbuf->deQueue(), 'a');

		delete rbuf;

		delete tbuf;

		return result;
	}

	bool testLoopbackCallback()
	{
		ReceiveActiveStringBuffer * rbuf = new ReceiveActiveStringBuffer(strlen(message));
		comUSART->setCurrentReceiveBuffer(rbuf);
		comUSART->enableReceiver();
		comUSART->enableFrameReceivedInterrupts();

		TransmitActiveStringBuffer * tbuf = new TransmitActiveStringBuffer(strlen(message) + 10);
		*tbuf << message;
		comUSART->setCurrentTransmitBuffer(tbuf);
		comUSART->enableTransmitter();
		comUSART->enableTransmitterReadyInterrupts();



//		comUSART->flushCurrentTransmitBuffer(); // NOTE : the buffers would fill/flush by themselves anyway without this call because of callbacks
//
//		comUSART->fillCurrentReceiveBuffer();

		delay(500);

		ActiveReceiveBuffer * released = comUSART->reclaimCurrentReceiveBuffer();

		bool result = AVRUNIT_ASSERT_EQUALS_PTR(released, rbuf);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(rbuf->getErrorCount(), 0);

		result &= AVRUNIT_ASSERT_EQUALS_LONG(rbuf->numberOfElements(), strlen(message));

		char * received = NULL; // = new char[25];

		received << *rbuf;

		result &= AVRUNIT_ASSERT_EQUALS_STRING_P(received, message);

		delete received;

		delete rbuf;

		delete tbuf;

		result &= AVRUNIT_ASSERT(isNull(comUSART->reclaimCurrentTransmitBuffer()));

		result &= AVRUNIT_ASSERT(isNull(comUSART->reclaimCurrentReceiveBuffer()));

		return result;
	}

	bool benchmark()
	{
		TransmitActiveStringBuffer * tbuf = new TransmitActiveStringBuffer(100);
		comUSART->setCurrentTransmitBuffer(tbuf);
		comUSART->enableTransmitter();
		while(true)
		{
			if(!tbuf->isFull())
				*tbuf << "0123456789";

			comUSART->enableTransmitterReadyInterrupts();
		}
	}



private:

	const prog_mem * message;

	USARTHardware * usartHardware;

	Coms::USART::ActiveBufferedUSART * comUSART;



	ReceiveActiveStringBuffer * rbuf;
};



#endif /* ActiveBufferedUSARTTest_H_ */
