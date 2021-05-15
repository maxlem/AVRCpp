#ifndef TESTTWIMASTER_H_
#define TESTTWIMASTER_H_
#include "AVRHardware/Communication/TWI.h"
#include "genericCommonStuff.h"


void testTWIMaster()
{
	while(true)
	{

		//twi.masterTransmit(Queue(memoryHeap, 100, "abcdef"), 111);
		testB0->blink(5, 100);
		TWI::getInstance()->masterReceive(1);
		testB0->blink(5, 100);
		lcd.printCharAt(3, 0, TWI::getInstance()->getBuffer()->deQueue());
		lcd.printChar(TWI::getInstance()->getBuffer()->deQueue());
		lcd.printChar(TWI::getInstance()->getBuffer()->deQueue());
		lcd.printChar(TWI::getInstance()->getBuffer()->deQueue());
		delay(1000);
	}
}
#endif /*TESTTWIMASTER_H_*/
