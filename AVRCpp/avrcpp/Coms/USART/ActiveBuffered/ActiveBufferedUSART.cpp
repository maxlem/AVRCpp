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

#include "ActiveBufferedUSART.h"
#include "ActiveBufferedUSARTFrameReceivedCallback.h"
#include "ActiveBufferedUSARTTransmitterReadyCallback.h"

namespace Coms
{

namespace USART
{

ActiveBufferedUSART::ActiveBufferedUSART(USARTHardware * usart) :
currentTransmitBuffer(NULL), currentReceiveBuffer(NULL), usart(usart)
{
	usart->connectFrameReceivedCallback(new ActiveBufferedUSARTFrameReceivedCallback(this));

	usart->connectTransmitterReadyCallback(new ActiveBufferedUSARTTransmitterReadyCallback(this));
}

ActiveBufferedUSART::~ActiveBufferedUSART()
{
	delete usart->disconnectFrameReceivedCallback();

	delete usart->disconnectTransmitterReadyCallback();
}

void ActiveBufferedUSART::waitReceiver()
{
	while(!usart->isFrameReceived() && currentReceiveBuffer->isOpen());
}


void ActiveBufferedUSART::readOperation()
{
	if(isNull(currentReceiveBuffer))
		return;

	waitReceiver();

	LOCK_INTERRUPTS;

	if(!currentReceiveBuffer->isOpen())
		disableFrameReceivedInterrupts();
	else
	{
		currentReceiveBuffer->handleStatus(usart->status());
		currentReceiveBuffer->receiveByte(usart->readFrame());
	}

	UNLOCK_INTERRUPTS;
}

void ActiveBufferedUSART::fillCurrentReceiveBuffer()
{
	disableFrameReceivedInterrupts();

	if(!isNull(currentReceiveBuffer))
		while(currentReceiveBuffer->isOpen())
			readOperation();


}

void ActiveBufferedUSART::setCurrentReceiveBuffer(ActiveReceiveBuffer * receiveBuffer)
{
	LOCK_INTERRUPTS;

	if(!isNull(receiveBuffer))
	{
		currentReceiveBuffer = receiveBuffer;

		currentReceiveBuffer->setObserver(this);
	}

	UNLOCK_INTERRUPTS;

}

void ActiveBufferedUSART::enableReceiver()
{
	LOCK_INTERRUPTS;

	if(!isNull(currentReceiveBuffer))
		usart->enableReceiver();

	UNLOCK_INTERRUPTS;

}

void ActiveBufferedUSART::enableFrameReceivedInterrupts()
{

	LOCK_INTERRUPTS;

	if(!isNull(currentReceiveBuffer))
		usart->enableFrameReceivedInterrupts();

	UNLOCK_INTERRUPTS;

}

ActiveReceiveBuffer * ActiveBufferedUSART::reclaimCurrentReceiveBuffer()
{

	ActiveReceiveBuffer * currentReceiveBuffer;

	LOCK_INTERRUPTS;

	currentReceiveBuffer = this->currentReceiveBuffer;

	releaseCurrentReceiveBuffer();

	UNLOCK_INTERRUPTS;

	return currentReceiveBuffer;
}


void ActiveBufferedUSART::releaseCurrentReceiveBuffer()
{
	LOCK_INTERRUPTS;

	disableFrameReceivedInterrupts();

	disableReceiver();


	if(!isNull(currentReceiveBuffer))
		currentReceiveBuffer->setObserver(NULL);

	currentReceiveBuffer = NULL;

	UNLOCK_INTERRUPTS;
}

void ActiveBufferedUSART::disableReceiver()
{
	LOCK_INTERRUPTS;
	usart->disableReceiver();
	UNLOCK_INTERRUPTS;
}

void ActiveBufferedUSART::disableFrameReceivedInterrupts()
{
	LOCK_INTERRUPTS;
	usart->disableFrameReceivedInterrupts();
	UNLOCK_INTERRUPTS;
}

void ActiveBufferedUSART::waitTransmitter()
{
	while(!usart->isTransmitterReady() && currentTransmitBuffer->isOpen());
}

void ActiveBufferedUSART::writeOperation()
{
	if(isNull(currentTransmitBuffer))
		return disableTransmitterReadyInterrupts();

	waitTransmitter();

	LOCK_INTERRUPTS;

	if(!currentTransmitBuffer->isOpen())
		disableTransmitterReadyInterrupts();
	else
		usart->writeFrame(currentTransmitBuffer->transmitByte());

	UNLOCK_INTERRUPTS;
}

void ActiveBufferedUSART::writeBaudSleepSafe()
{

	if(isNull(currentTransmitBuffer))
		return disableTransmitterReadyInterrupts();

	waitTransmitter();

	LOCK_INTERRUPTS;

	if(!currentTransmitBuffer->isOpen())
		disableTransmitterReadyInterrupts();
	else
	{
		usart->clearFrameTransmittedFlag();

		usart->writeFrame(currentTransmitBuffer->transmitByte());

		UNLOCK_INTERRUPTS;

		while(!usart->isFrameTransmitted());
	}

	UNLOCK_INTERRUPTS; // no harm in unlocking twice
}
void ActiveBufferedUSART::flushCurrentTransmitBuffer()
{
	disableTransmitterReadyInterrupts();

	if(!isNull(currentTransmitBuffer))
		while(currentTransmitBuffer->isOpen())
			writeOperation();

}

void ActiveBufferedUSART::setCurrentTransmitBuffer(ActiveTransmitBuffer * transmitBuffer)
{
	LOCK_INTERRUPTS;

	if(!isNull(transmitBuffer))
	{
		currentTransmitBuffer = transmitBuffer;
		currentTransmitBuffer->setObserver(this);
	}

	UNLOCK_INTERRUPTS;

}

void ActiveBufferedUSART::enableTransmitter()
{
	LOCK_INTERRUPTS;

	if(!isNull(currentTransmitBuffer))
		usart->enableTransmitter();

	UNLOCK_INTERRUPTS;

}

void ActiveBufferedUSART::enableTransmitterReadyInterrupts()
{
	LOCK_INTERRUPTS;

	if(!isNull(currentTransmitBuffer))
	{
		usart->enableTransmitterReadyInterrupts();
	}

	UNLOCK_INTERRUPTS;

}

ActiveTransmitBuffer * ActiveBufferedUSART::reclaimCurrentTransmitBuffer()
{

	ActiveTransmitBuffer * currentTransmitBuffer;

	LOCK_INTERRUPTS;

	currentTransmitBuffer = this->currentTransmitBuffer;

	releaseCurrentTransmitBuffer();

	UNLOCK_INTERRUPTS;

	return currentTransmitBuffer;
}


void ActiveBufferedUSART::releaseCurrentTransmitBuffer()
{
	LOCK_INTERRUPTS;

	disableTransmitterReadyInterrupts();

	disableTransmitter();

	if(!isNull(currentTransmitBuffer))
	{
		currentTransmitBuffer->setObserver(NULL);

		currentTransmitBuffer = NULL;
	}

	UNLOCK_INTERRUPTS;
}

void ActiveBufferedUSART::disableTransmitter()
{
	LOCK_INTERRUPTS;
	usart->disableTransmitter();
	UNLOCK_INTERRUPTS;
}


void ActiveBufferedUSART::disableTransmitterReadyInterrupts()
{
	LOCK_INTERRUPTS;
	usart->disableTransmitterReadyInterrupts();
	UNLOCK_INTERRUPTS;
}

}

}
