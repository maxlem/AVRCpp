#ifndef TESTHD44780_H_
#define TESTHD44780_H_

#include "genericCommonStuff.h"
#include "ExternalHardware/HD44780.h"

void testHD44780()
{

	HD44780 lcd(&PORTA, &DDRA, &PINA, 3, 0, 1, 2);
//	HD44780 lcd(&PORTB, &DDRB, 3, 0, 1, 2);
//	HD44780 lcd(&PORTC, &DDRC, 3, 0, 1, 2);
//	HD44780 lcd(&PORTD, &DDRD, 3, 0, 1, 2);
	char string[] = "0123456789";
	uint16_t index = 0;

	/********************/
	lcd.useCursorMode();
	lcd.clearDisplay();
	lcd.printLineAt(0, 0, "cursor (right) : ");
	lcd.useCursorMode(RIGHT);
	lcd.goToPosition(2, 0);

	index = 0;
	while (string[index] != '\0')
	{
		lcd.printChar(string[index]);
		index++;
		delay(500);
	}

	/********************/
	lcd.useCursorMode();
	lcd.clearDisplay();
	lcd.printLineAt(0, 0, "cursor (left) : ");

	lcd.useCursorMode(LEFT);
	lcd.goToPosition(2, 0);

	index = 0;
	while (string[index] != '\0')
	{
		lcd.printChar(string[index]);
		index++;
		delay(500);
	}

	/********************/
	lcd.useCursorMode();
	lcd.clearDisplay();
	lcd.printLineAt(0, 0, "shift (right) : ");

	lcd.useShiftDisplayMode(LEFT);
	lcd.goToPosition(2, 0);

	index = 0;
	while (string[index] != '\0')
	{
		lcd.printChar(string[index]);
		index++;
		delay(500);
	}

	/********************/
	lcd.useCursorMode();
	lcd.clearDisplay();
	lcd.printLineAt(0, 0, "shift (left) : ");

	lcd.useShiftDisplayMode(RIGHT);
	lcd.goToPosition(2, 0);

	index = 0;
	while (string[index] != '\0')
	{
		lcd.printChar(string[index]);
		index++;
		delay(500);
	}
}
#endif /*TESTHD44780_H_*/
