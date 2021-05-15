
#define F_CPU 16000000UL

#include <avr/io.h>

#include <util/delay.h>

#include "ExternalHardware/HD44780.h"

int main() {

HD44780 lcd4(&PORTE, &DDRE, &PINE, 4, 1, 2, 3);	//(PORTx, DDRx, PINx, data start pin, RS, RW, E)

_delay_ms(500);
lcd4.initDisplay();
lcd4.displaySetup(1, 0, 0);
lcd4.clearDisplay();

while(1){

	lcd4.printLineAt(0, 5, "MainBoard");
	lcd4.printLineAt(2, 4, "Bonjour Max!");

	_delay_ms(500);
	lcd4.clearDisplay();

}
	return 0;
}


