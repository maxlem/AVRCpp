/*
Copyright (c) 2007-2021 Maxime Lemonnier

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "HD44780.h"
#include <util/delay.h>
#include <stdlib.h>
/*!
*	Addressing
*/
#define DDRAM_BASE bitValue(7)
#define CGRAM_BASE bitValue(6)

/*!
 * 	Timing
 */
#define SHORT_OP_DELAY _delay_us(500)
#define LONG_OP_DELAY _delay_ms(10.0f)
#define BOOT_UP_DELAY _delay_ms(40.0f)

HD44780::HD44780(IOAddress dataPort, IOAddress dataDDR, IOAddress dataPIN, IOAddress controlPort, IOAddress controlDDR, uint8_t RS, uint8_t RW, uint8_t E) : dataPort(dataPort), dataDDR(dataDDR), dataPIN(dataPIN), controlPort(controlPort), controlDDR(controlDDR)//, RS(RS), RW(RW), E(E)
{
	eightBitsMode = true;
	startingBitForFourBitMode = 0;
	this->maskRS = bitValue( RS );
	this->maskRW = bitValue( RW );
	this->maskE = bitValue( E );
	initDisplay();
}

HD44780::HD44780(IOAddress port, IOAddress ddr, IOAddress pin, uint8_t startingBitForFourBitMode, uint8_t RS, uint8_t RW, uint8_t E) : dataPort(port), dataDDR(ddr), dataPIN(pin), controlPort(port), controlDDR(ddr)//, RS(RS), RW(RW), E(E)
{
	eightBitsMode = false;
	this->startingBitForFourBitMode = startingBitForFourBitMode;
	this->maskRS = bitValue( RS );
	this->maskRW = bitValue( RW );
	this->maskE = bitValue( E );
	initDisplay();
}

void HD44780::initDisplay(){

	setDataIOMode(0xFF);
	setControlIOMode(0xFF);
	clearDataPort();
	clearControlPort();

	_delay_ms(30);
	*dataPort = 0x03;
	pulse();

	_delay_ms(5);
	*dataPort = 0x03;
	pulse();

	_delay_us(110);
	*dataPort = 0x03;
	pulse();

	_delay_us(40);
	if(!eightBitsMode)
	{
		*dataPort = 0x02;
		pulse();
	}

	functionSet(true, false);
	clearDisplay();
	displaySetup(true, true, true);
	useCursorMode(RIGHT);
	cursorHome();
}

void HD44780::waitBusyFlag()
{

	*dataDDR = 0x7F; //(uint8_t)~bitValue(7);		//put pin 7 in input
	clearBit(*dataPort, 7);		//to remove the pull-up resistor
	//clearBit(*controlPort, maskRS);	//not sure it work the way i want...

	*controlPort |= maskRW;
	*controlPort |= maskE;

	while (bitIsSetInRegister(*dataPIN, 7)) {	// TODO: timeout just in case
		*controlPort &= ~maskE;		//toggle the E pin to check again
		_delay_us(5);
		*controlPort |= maskE;
		_delay_us(5);
	}
	*controlPort &= ~maskE;
//	_delay_us(10);
	*controlPort &= ~maskRW;

	*dataDDR = 0xFF; //|= bitValue(7);		//put back pin 7 as output
	_delay_us(10);

}

void HD44780::pulse()
{

	*controlPort |= maskE;
	_delay_us(5);
	*controlPort &= ~maskE;

}

void HD44780::clearDataPort()
{
	*dataPort = 0x00;
}

void HD44780::clearControlPort()
{
	*controlPort = 0x00;
}

void HD44780::setDataIOMode(uint8_t mask)
{
	*dataDDR = mask;
}

void HD44780::setControlIOMode(uint8_t mask)
{
	*controlDDR = mask;
}

void HD44780::transmit(uint8_t data, uint8_t control)
{
	bool interruptEnabled = false;
	if(bitIsSetInRegister(SREG, SREG_I))
	{
		interruptEnabled = true;
		clearBit(SREG, SREG_I);	// we don't want to be interrupted here
	}

	clearDataPort();
	clearControlPort();

	if(eightBitsMode)
	{
		*dataPort = data;
		*controlPort = control;
		pulse();

	}
	else
	{
		//high nibble
		uint8_t temp = (0x0F & (data >> 4));
		temp <<= startingBitForFourBitMode;
		*dataPort |= temp;


		*controlPort |= control;
		pulse();
//		waitBusyFlag();

		temp = 0x0F << startingBitForFourBitMode;
		*dataPort &= ~(temp); // clear only data lines

		//low nibble
		temp = (0x0F & (data));
		temp <<= startingBitForFourBitMode;
		*dataPort |= temp;

		pulse();
//		waitBusyFlag();
	}

	clearDataPort();
	clearControlPort();


	if(interruptEnabled)
		enableInterrupts();
}

void HD44780::clearDisplay()
{
	uint8_t data = bitValue(0);
	uint8_t control = maskE;
	transmit(data, control);
	LONG_OP_DELAY;
}

void HD44780::cursorHome()
{
	uint8_t data = bitValue(1);
	uint8_t control = maskE;
	transmit(data, control);
	LONG_OP_DELAY;
}


void HD44780::useCursorMode(Direction direction)
{
	shiftMode(direction, false);
	cursorOrShiftDisplay(false, false);
}


void HD44780::useShiftDisplayMode(Direction direction)
{
	shiftMode(direction, true);
	cursorOrShiftDisplay(true, direction);
}

void HD44780::shiftMode(bool cursorIncrement, bool shiftDisplay)
{
	uint8_t data = bitValue(2);
	uint8_t control = maskE;

	if (cursorIncrement)
	{
		data |= bitValue(1);
	}

	if (shiftDisplay)
	{
		data |= bitValue(0);
	}

	transmit(data, control);
}

void HD44780::displaySetup(bool displayOn, bool cursorOn, bool blinkOn) {

	uint8_t data = bitValue(3);
	uint8_t control = maskE;

	if (displayOn)
	{
		data |= bitValue(2);
	}
	if (cursorOn)
	{
		data |= bitValue(1);
	}
	if (blinkOn)
	{
		data |= bitValue(0);
	}
	transmit(data, control);
}

void HD44780::cursorOrShiftDisplay(bool shiftDisplay, bool right) {
	uint8_t data = bitValue(4);
	uint8_t control = maskE;

	if (shiftDisplay)
	{
		data |= bitValue(3);
	}

	if (right)
	{
		data |= bitValue(2);
	}

	transmit(data, control);
}

void HD44780::functionSet(bool fourLines, bool highDefFont) {

	uint8_t data = bitValue(5);
	uint8_t control = maskE;

	if (eightBitsMode)
	{
		data |= bitValue(4);
	}

	if (fourLines)
	{
		data |= bitValue(3);
	}

	if (highDefFont)
	{
		data |= bitValue(2);
	}

	transmit(data, control);
}




uint8_t HD44780::getAddressOf(uint8_t lineNumber, uint8_t rowNumber)
{

		switch (lineNumber) {
			case 0 : 	lineNumber = 0x00;
				break;
			case 1 : 	lineNumber = 0x40;
				break;
			case 2 : 	lineNumber = 0x14;
				break;
			case 3 : 	lineNumber = 0x54;
				break;
			default : lineNumber = 0x00;
		}
		return lineNumber + rowNumber;
}

void HD44780::goToPosition(uint8_t lineNumber, uint8_t rowNumber) {
	uint8_t address = getAddressOf(lineNumber, rowNumber);
	// set DRAM address
	uint8_t data = DDRAM_BASE | address;
	uint8_t control = maskE;
	transmit(data, control);
}

void HD44780::printChar(char character) {

	uint8_t control = (maskRS | maskE);
	uint8_t data = character;

	transmit(data, control);
}

void HD44780::printCharAt(uint8_t lineNumber, uint8_t rowNumber, char character) {
	goToPosition(lineNumber, rowNumber);
	printChar(character);
}



/*! Prints up to 20 characters
*	@param lineNumber : the display has 4 lines, lines 0, 1, 2 and 3
*	@param startingRow : the row at wich the string starts
*	@param sentence : the string
*	@param stopChar : the character that tells where to stop
*/
void HD44780::printLineAt (uint8_t lineNumber, uint8_t rowNumber, const char * string)
{
	goToPosition(lineNumber, rowNumber);

	printLine(string);
}


void HD44780::printLine (const char * string)
{
	uint8_t index = 0;

	while (string[index] != '\0')
	{
		printChar(string[index]);
		index++;
	}
}

void HD44780::printNumber(long number, uint8_t radix)
{
	char buffer[20];
	printLine(ltoa(number, buffer, radix));

}

void HD44780::printNumber(float number, uint8_t minLenght, uint8_t precision)
{
	char buffer[20];
	printLine(dtostrf(number, minLenght, precision, buffer));

}

void HD44780::printNumberAt(uint8_t lineNumber, uint8_t rowNumber, long number, uint8_t radix)
{
	goToPosition(lineNumber, rowNumber);
	printNumber(number, radix);

}

void HD44780::printNumberAt(uint8_t lineNumber, uint8_t rowNumber, float number, uint8_t minLenght, uint8_t precision)
{
	goToPosition(lineNumber, rowNumber);
	printNumber(number, minLenght, precision);
}

