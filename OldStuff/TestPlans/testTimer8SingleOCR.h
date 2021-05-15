#ifndef TESTTIMER8_H_
#define TESTTIMER8_H_

#include "AVRHardware/Timers/Timer8/Timer8SingleOCR.h"
#include "genericCommonStuff.h"


void testTimer8SingleOCR()
{
	Timer8SingleOCR* timer0 = Timer8SingleOCR::getTimer0();
	
	lcd.printLineAt(2, 0, "num of ticks: ");
	timer0->setTimerOverflowCallBack(genericCallBack);
	timer0->startBasicTimer(1024); // F_CPU/1024 is ~ 16 000 ticks per secs

	srandom(3498); //our seed

	while(true)
	{

		uint8_t random_ms = (uint8_t)abs(random())%100;
		lcd.printNumberAt(1, 0, random_ms);
		testB0->blink(2, 10);
		lcd.printLineAt(3, 0, "             ");
		lcd.printNumberAt(3, 0, timer0->readTimer());

	}
}

#endif /*TESTTIMER8_H_*/
