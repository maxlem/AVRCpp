#ifndef TESTPPM_H_
#define TESTPPM_H_
#include "ExternalHardware/PPMListener.h"
#include "genericCommonStuff.h"

void testPPM()
{
	PPMListener::getInstance()->listen(100);
	uint32_t readings = 0;

	while(true)
	{
		if (!PPMListener::getInstance()->getPulses()->isEmpty())
		{
			readings++;
			lcd.printLineAt(1, 0, "                      ");
			lcd.printNumberAt(3, 0, PPMListener::getInstance()->getPulses()->deQueue());
			lcd.printNumberAt(3, 10, readings);
		}
		else
		{
			testB0->blink(5, 100);
		}
	}
}
#endif /*TESTPPM_H_*/
