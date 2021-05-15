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

#ifndef PollUSART_H_
#define PollUSART_H_

#include "../USARTHardware.h"
#include "../../../DataStructures/ActiveBuffers/ActiveReceiveBuffers/ActiveReceiveBuffer.h"
#include "../../../DataStructures/ActiveBuffers/ActiveReceiveBuffers/ActiveReceiveBufferObserver.h"
#include "../../../DataStructures/ActiveBuffers/ActiveTransmitBuffers/ActiveTransmitBuffer.h"
#include "../../../DataStructures/ActiveBuffers/ActiveTransmitBuffers/ActiveTransmitBufferObserver.h"
namespace Coms
{

namespace USART
{

class ActiveBufferedUSART : public ActiveReceiveBufferObserver, public ActiveTransmitBufferObserver
{
public:

	ActiveBufferedUSART(USARTHardware * usart);

	virtual ~ActiveBufferedUSART();

	void setCurrentReceiveBuffer(ActiveReceiveBuffer * receiveBuffer);

	void enableReceiver();

	void enableFrameReceivedInterrupts();

	void fillCurrentReceiveBuffer();

	void readOperation();

	void disableReceiver();

	void disableFrameReceivedInterrupts();

	ActiveReceiveBuffer * reclaimCurrentReceiveBuffer();

	void releaseCurrentReceiveBuffer();

	void setCurrentTransmitBuffer(ActiveTransmitBuffer * transmitBuffer);

	void enableTransmitter();

	void enableTransmitterReadyInterrupts();

	void flushCurrentTransmitBuffer();

	void writeOperation();

	void writeBaudSleepSafe();

	void disableTransmitter();

	void disableTransmitterReadyInterrupts();

	ActiveTransmitBuffer * reclaimCurrentTransmitBuffer();

	void releaseCurrentTransmitBuffer();

protected :

	void waitTransmitter();

	void waitReceiver();

	ActiveTransmitBuffer * currentTransmitBuffer;

	ActiveReceiveBuffer * currentReceiveBuffer;

	USARTHardware * usart;
};

}

}

#endif /* PollUSART_H_ */
