#ifndef WGM8BITS_H_
#define WGM8BITS_H_

#include "AVRHardware/Timers/Timer8/Timer8SingleOCR.h"

#include "genericCommonStuff.h"

void testWGM8bits()
{
	Timer8SingleOCR* timer = Timer8SingleOCR::getTimer0();

	lcd.printLineAt(0, 0, "timer id:       ");
	lcd.printNumber((int)timer);

	timer->setWaveGenerationMode(1, 1, 1, 1);

	lcd.printLineAt(0, 0, "after set :");

	lcd.printNumberAt(1,8,timer->readTimer());

	timer->startWaveGeneration(1024, 235);

	lcd.printLineAt(0, 0, "after start :");

	while(true)
	{
		lcd.printNumberAt(1,0,timer->readTimer());
		delay(100);
	}
}
#endif /*WGM8BITS_H_*/
