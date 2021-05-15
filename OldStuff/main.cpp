#include "includes.h"


#define BUFFER_SIZE 100

bool flash = false;



int main() {

	DDRB = 0xFF;

	testB0->blink(10, 100);
	testB1->blink(10, 100);

//	xUnitListener();

//	HD44780 lcd(&PORTA, &DDRA, 3, 0, 1, 2);

//	lcd.printLine("USART test");

//	testHD44780();


//	demoSDD();

//	testTom tom;

//
//	testWGM8bits();
//
//	testWGM16bits();
//
//	testPWM8bits();
//
//	testHD44780();
//
//	testTWIMaster();
//
//	testTWISlave();
//
//	testSPIMaster();
//
//	testSPISlave();
//
//	testUSARTMaster();
//
//	testUSARTSlaveRS232();
//
//	testPPM();
//
//	testA2D();

	return 0;
}

