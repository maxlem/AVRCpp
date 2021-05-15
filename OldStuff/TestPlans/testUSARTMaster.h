#include "Utils/Blink.h"
#include "Communication/USART.h"
#include "DataStructures/DataStructureUtils.h"
//#include "A2DSampling.h"




Blink d3(&PORTD, &DDRD, 3);
USART* usart0 = USART::getUSART0();
Queue<uint8_t>* ptrQueue = new Queue<uint8_t>(15);

volatile uint8_t i = 0;


void testUsartNoInterrupts()
{
	usart0->enableTransmission();

	for (int i = 0; i < 5; i++)
	{
		enQueueString(ptrQueue, "|_no_int__|");

		usart0->transmit(ptrQueue);
		d3.blink(6, 25);
	}
}

void bufferEmptyCallBack()
{
	disableInterrupts;
	d3.blink(4, 100);
}

void testUsartAutomaticMode()
{

	enQueueString(ptrQueue, "|___int___|");
	usart0->setTransmissionBuffer(ptrQueue);
	usart0->enableTransmission(bufferEmptyCallBack, true);

	while(true)
	{
		d3.blink(6, 25);


		if (usart0->getTransmissionBuffer()->isEmpty())
		{
			enQueueString(usart0->getTransmissionBuffer(), "|___int___|"); //TODO : hangs randomly here!!
			usart0->enableTransmission(bufferEmptyCallBack, true);
		}

	}

}

void transMissionCompleteCallback()
{
	if(ptrQueue->isEmpty())
	{
		enQueueString(ptrQueue, "|___int___|");
		ptrQueue->enQueue(++i);
	}


	usart0->transmit(ptrQueue->deQueue());
}
void testInterruptCallback()
{
	enQueueString(ptrQueue, "|___int___|");
	usart0->enableTransmission();
	usart0->setTransmissionCompleteCallback(transMissionCompleteCallback);

	while(true)
	{
		d3.blink(4, 50);
	}
}
