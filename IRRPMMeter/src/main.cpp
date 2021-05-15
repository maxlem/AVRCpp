/*
 * main.cpp
 *
 *  Created on: 2011-12-22
 *      Author: Maxime Lemonnier
 */


#include "CallbackServers/Callback.h"
#include "ExternalInterrupts/ExternalInterrupts.h"
#include "Utils/Utils.h"
#include "Utils/Blink.h"
#include "Utils/Delay.h"
#include "Timers/Timer16bits3OCR.h"
#include "Coms/USART/stdio/stdioUSART.h"
using Timers::Timer16bits3OCR;

Blink orange(&PORTB, &DDRB, 7, 1, 100);

class ExternalInterruptCallback : public Callback
{

public :

	ExternalInterruptCallback() :
		counter(Timer16bits3OCR::getTimer16bits3OCR(1)->getCounter()),
		last(0), current(1)
	{

		counter->setPrescaler(Timers::Prescalers::DIV_8);
		prescaler = 8;
	}
	void callback()
	{
		last = current;
		current = counter->read();

	}
	Timers::Counter16 * counter;

	volatile uint16_t last;
	volatile uint16_t current;
	uint16_t prescaler;

};

int main()
{
	stderr = Coms::USART::fdevopen(_FDEV_SETUP_RW, Coms::USART::USARTHardware::getUSARTHardware(0));

	stdin = stdout = Coms::USART::fdevopen(_FDEV_SETUP_RW, Coms::USART::USARTHardware::getUSARTHardware(0));


	printf(PROG_MEM_STRING("---------------RPM Meter -------------------\n\r"));
	printf(PROG_MEM_STRING("For a 880kV motor at supplied 15V, max should be 13200rpm\n\n\n\r"));

	ExternalInterruptCallback callbackInt0;

	ExternalInterrupt * int0 = ExternalInterrupt::getInstance(0);


	int0->configure(InterruptSenseModes::RISING_EDGE);

	int0->connectCallback(&callbackInt0);

	changeBitValueTo(DDRD, PD0, INPUT);
	changeBitValueTo(PORTD, PD0, 0);
	int0->enableInterrupt();
	enableInterrupts();

	orange.blink();
	uint16_t elapsed;
	uint32_t dividend = (60ul * F_CPU) / (uint32_t)callbackInt0.prescaler;
	uint16_t current, last;
	while(true)
	{


		current = callbackInt0.current;
		last = callbackInt0.last;
		if (current < last)
			elapsed = (current + ((uint16_t)0xFFFF - last));
		else
			elapsed = (current - last);

		printf("rpm = %u, elapsed = %u \n", (uint16_t)(dividend/elapsed), elapsed);

		orange.blink(1,10);
	}
}





