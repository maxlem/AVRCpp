/*
 * xUnit.h
 *
 *  Created on: 5-May-2009
 *      Author: malem303
 */

#ifndef XUNIT_H_
#define XUNIT_H_

void clear()
{
	flash = false;

	set2Bits(PORTB, 0, 1);
//	clearBit(PORTB, 0);
//	clearBit(PORTB, 1);
//	PORTB = 0x03;
}

void red()
{
	setBit(PORTB, 0);
	clearBit(PORTB, 1);
}

void green()
{
	clearBit(PORTB, 0);
	setBit(PORTB, 1);
}

void xUnitListener()
{
//	DDRA = 0x00;
	USART* usart0 = USART::getUSART0();
	usart0->setBitRate(9600);
	usart0->setFrameFormat(8, 1, NO_PARITY);
	usart0->enableListening();



	char buffer[BUFFER_SIZE + 1];
	int index = 0;

	clear();
	while(true)
	{
		if (flash)
		{
			red();
			delay(100);
			green();
			delay(100);

		}
//		testB1->blink(1, 100);
//		lcd.goToPosition(2, 0);
//		testB1->blink(10, 100);

		delay(100);
		index = 0;
		buffer[index] = '\0';
		while(!usart0->getBuffer()->isEmpty() && index < BUFFER_SIZE)
		{

			buffer[index] = usart0->getBuffer()->deQueue();

			if(buffer[index] == '.')
				break;

			index++;

			//lcd.printNumberAt(3, 0, (int)c);
//			lcd.printChar(c);
		}

		buffer[index] = '\0';

		if (!strcmp(buffer, "CLEAR"))
			clear();
		else if (!strcmp(buffer, "RED"))
			red();
		else if (!strcmp(buffer, "GREEN"))
			green();
		else if (!strcmp(buffer, "FLASH"))
			flash = true;



	}

}
#endif /* XUNIT_H_ */
