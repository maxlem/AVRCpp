#ifndef TESTUSARTSLAVE_H_
#define TESTUSARTSLAVE_H_

#include "Communication/USART.h"
#include "genericCommonStuff.h"


void testUSARTSlave()
{
	//	testUSART_Init(9600);
	//	Queue<uint8_t>* ptrQueue = new Queue<uint8_t>(100);
	//	testUSART_InterruptReceive();
	//	while(true)
	//	{
	//		testB1->blink(5, 100);
	//		//ptrQueue->enQueue(testUSART_Receive());
	//
	//		if(testUSARTptrQueue->numberOfElements() > 10)
	//			lcd.printLineAt(2, 0, testUSARTptrQueue->toString());
	//
	//	}
	USART* usart0 = USART::getUSART0();
	//testUSART_Init(9600);

	usart0->enableListening();

	while(true)
	{
		testB1->blink(5, 100);
		lcd.goToPosition(2, 0);
		while(!usart0->getBuffer()->isEmpty())
		lcd.printChar(usart0->getBuffer()->deQueue());
	}
}

void testUSARTSlaveRS232()
{
	//	testUSART_Init(9600);
	//	Queue<uint8_t>* ptrQueue = new Queue<uint8_t>(100);
	//	testUSART_InterruptReceive();
	//	while(true)
	//	{
	//		testB1->blink(5, 100);
	//		//ptrQueue->enQueue(testUSART_Receive());
	//
	//		if(testUSARTptrQueue->numberOfElements() > 10)
	//			lcd.printLineAt(2, 0, testUSARTptrQueue->toString());
	//
	//	}
	USART* usart0 = USART::getUSART0();
	usart0->setBitRate(38400);
	usart0->setFrameFormat(8, 1, NO_PARITY);

	//testUSART_Init(9600);

	usart0->enableListening();

	while(true)
	{
		testB1->blink(5, 100);
		lcd.goToPosition(2, 0);
		while(!usart0->getBuffer()->isEmpty())
		{
			testB0->blink(5, 100);
			char c = usart0->getBuffer()->deQueue();
			//lcd.printNumberAt(3, 0, (int)c);
//			lcd.printChar(c);
		}
	}
}
#endif /*TESTUSARTSLAVE_H_*/
