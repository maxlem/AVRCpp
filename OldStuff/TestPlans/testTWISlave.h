#ifndef TESTTWISLAVE_H_
#define TESTTWISLAVE_H_
#include "AVRHardware/Communication/TWI.h"
#include "genericCommonStuff.h"

void testTWISlave()
{
	Queue<uint8_t>* queue = new Queue<uint8_t>(8);
	TWI::getInstance()->setBuffer(queue);
	
	enQueueString(queue, "1234567");
	while(!transmission)
	{
		TWI::getInstance()->listen();
		delay(100);
	}
}
#endif /*TESTTWISLAVE_H_*/
