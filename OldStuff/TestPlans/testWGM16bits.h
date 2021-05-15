#ifndef WGM16BITS_H_
#define WGM16BITS_H_

#include "ExternalHardware/HD44780.h"
#include "Timers/Timer16/Timer16DoubleOCR.h"
#include "Utils/Delay.h"



void testWGM16bits()
{
	HD44780 lcd(&PORTB, &DDRB, 3, 0, 1, 2);
	
	Timer16DoubleOCR* timer = Timer16DoubleOCR::getTimer1();
	
	// 10-bits Fast PWM (top at 03FF)
	uint8_t wgm0 = 1;
	uint8_t wgm1 = 1;
	uint8_t wgm2 = 1;
	uint8_t wgm3 = 0;
	
	// PWM inverted mode for output A
	uint8_t com0A = 1;
	uint8_t com1A = 1;
	
	// PWM inverted mode for output B
	uint8_t com0B = 1;
	uint8_t com1B = 1;
	
	timer->setWaveGenerationMode(wgm0, wgm1, wgm2, wgm3, com0A, com1A, com0B, com1B);

	// maximum divider == minimum clock 
	// cycle lenght = 0x03FF (10bits) *  clockDivider / F_CPU
	// for a 16Mhz crystal and 256 clock divider : cycle lenght = 16.384 ms 	
	uint16_t clockDivider = 256; 
	
	
	// if we want a 1.5ms pulse, we want our pins to toggle 1.5ms befor the end
	// or at (16.384 - 1.5) / 16.384 * 0x03FF = 930
	uint16_t compareToValue = 930;
	timer->startWaveGeneration(clockDivider, compareToValue, compareToValue);

	lcd.printLineAt(0, 0, "compareToValue:                  ");
	
	srandom(3498); //our seed


	while(true)
	{
		lcd.printNumberAt(0, 16, compareToValue);
		compareToValue = 900 + (uint8_t)abs(random())%64;
		delay(1000);
		timer->startWaveGeneration(clockDivider, compareToValue, compareToValue);
	}
}
#endif /*WGM16BITS_H_*/
