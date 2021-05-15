#ifndef GENERICCOMMONSTUFF_H_
#define GENERICCOMMONSTUFF_H_
#include <util/twi.h>
#include <avr/interrupt.h>
#include <stdlib.h> //for random()
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "Utils/Utils.h"
#include "DataStructures/DataStructureUtils.h"
#include "Utils/Delay.h"
#include "ExternalHardware/HD44780.h"
#include "Utils/Blink.h"
#include "Communication/TWI.h"
HD44780 lcd(&PORTA, &DDRA, &PINA, 3, 0, 1, 2);


void genericCallBack() {
	static uint32_t numberOfCallBacks = 0;

	//lcd.printLineAt(0, 0, "callbacks:"); lcd.printNumber(numberOfCallBacks);
	numberOfCallBacks++;
}


Blink* testB1 = new Blink(&PORTB, &DDRB, 1);
Blink* testB0 = new Blink(&PORTB, &DDRB, 0);

//bool transmission = false;
//
//void transmissionCompleteCallBack()
//{
//	lcd.printLineAt(2, 0, "slave received :");
//	lcd.printLineAt(3, 0, queueToString(TWI::getInstance()->getBuffer()));
//	transmission = true;
//}


#endif /*GENERICCOMMONSTUFF_H_*/
