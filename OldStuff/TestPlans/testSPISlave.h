#ifndef TESTSPISLAVE_H_
#define TESTSPISLAVE_H_
#include "AVRHardware/Communication/SPI.h"
#include "genericCommonStuff.h"

void testSPISlave()
{
	//	testSPI_SlaveInit();
	//	Queue<uint8_t>* ptrQueue = new Queue<uint8_t>(100);
	//	testSPI_InterruptReceive();
	//	while(true)
	//	{
	//		testB1->blink(5, 100);
	//	}	

	SPI* spi = SPI::getInstance();

	spi->enableListening();

	while (true) {
		testB0->blink(5, 100);
		disableInterrupts;
		if (!spi->getBuffer()->isEmpty())
		{
			uint8_t byte = spi->getBuffer()->deQueue();
			lcd.printCharAt(3, 0, byte);
			lcd.printLineAt(2, 0, queueToString<unsigned char> (spi->getBuffer()));
		}
		enableInterrupts;
	}
}
#endif /*TESTSPISLAVE_H_*/
