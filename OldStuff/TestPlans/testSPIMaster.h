#ifndef TESTSPIMASTER_H_
#define TESTSPIMASTER_H_
#include "AVRHardware/Communication/SPI.h"
#include "genericCommonStuff.h"

void testSPIMaster()
{
	//	testSPI_MasterInit();
	//	
	//	uint32_t count = 0;
	//	while(true)
	//	{
	//		testB1->blink(5, 100);
	//		testSPI_MasterTransmit(('a' + (count % ('x' - 'a'))));
	//		count++;
	//	}

	Queue<uint8_t>* ptrQueue = new Queue<uint8_t>(100);
	while(true)
	{
		if(ptrQueue->isEmpty())
		enQueueString(ptrQueue, "abcdefghijkl");

		if(!SPI::getInstance()->masterTransmit(ptrQueue))
		testB0->blink(10, 50);
	}
}
#endif /*TESTSPIMASTER_H_*/
