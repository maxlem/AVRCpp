#ifndef PWM8BITS_H_
#define PWM8BITS_H_
#include "ExternalHardware/PWM8bits.h"
#include "AVRHardware/AnalogToDigital/AnalogToDigital.h"
#include "genericCommonStuff.h"

void testPWM8bits()
{
	//lcd.printLineAt(0, 0, "salut");
	//lcd.printLineAt(1, 0, "gen");
	PWM8bits pwm(Timer8SingleOCR::getTimer0(), FastPWM, false);
//	PWM8bits pwm(Timer8::getTimer0(), PhaseCorrectPWM, false);
	
	lcd.printNumberAt(0,0, pwm.setCycleLenght(20.0f), 3, 2);
	lcd.printNumberAt(1,0, pwm.setPulseWidth(1.80f), 3, 2);
	
	//delay(3000);
	
	AnalogToDigital* a2d = AnalogToDigital::getInstance();
	a2d->configure(128, 0x01);
	a2d->powerOn();
		
		
//	delay(3000);
	while(true)
	{
		pwm.startPWM();
		
		float reading = a2d->eightBitsRead(7);
		lcd.printNumberAt(1,0, pwm.setPulseWidth(1.0f + ((float) reading / (float) 255)), 3, 2);
		
		delay(50);
		
	}
}

#endif /*PWM8BITS_H_*/
