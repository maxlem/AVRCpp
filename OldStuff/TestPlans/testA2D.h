#ifndef TESTA2D_H_
#define TESTA2D_H_
#include "AnalogToDigital/AnalogToDigital.h"
#include "genericCommonStuff.h"

void testA2D()
{
	AnalogToDigital *a2d = AnalogToDigital::getInstance();
	//twi.enableSlave();
	while(true)
	{
		lcd.goToPosition(1, 0);
		lcd.printLine("8-bits : ");
		lcd.printNumber(a2d->eightBitsRead(0));

		lcd.goToPosition(2, 0);
		lcd.printLine("10-bits : ");
		lcd.printNumber(a2d->toVolts(a2d->tenBitsRead(0)), 3, 5);
	}

}
#endif /*TESTA2D_H_*/
