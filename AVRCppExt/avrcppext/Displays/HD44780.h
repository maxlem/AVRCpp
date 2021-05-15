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

#ifndef HD44780_H
#define HD44780_H

#include "Utils/CppExtensions.h"
#include "Utils/BitManipulation.h"

/*! Popular HD44780 LCD driving class.
 * It can work with 4 or 8 bits interface
 * @warning \a F_CPU must be set with the right frequency as timing is critical for the code
 */
class HD44780
{
private:

	IOAddress dataPort;		// the port where D0~D7 pins are connected (ex &PORTA)
	IOAddress dataDDR;		// the data port's DDR (ex. &DDRA)
	IOAddress dataPIN;		// the input pins address (ex. &PINA)
	IOAddress controlPort;	// the port where the E, RS, RW pins are connected (can be the same as dataPort is 4-bits mode is used)
	IOAddress controlDDR;	// the control port's DDR


	bool eightBitsMode;
	uint8_t startingBitForFourBitMode;	// if 4 bits mode is used, pins D4~D7 must be connected in growing order from \a startingBitForFourBitMode to <code> startingBitForFourBitMode + 4 </code> on \a dataPort
	uint8_t maskRS;	// ready to send pin number (on controlPort)
	uint8_t maskRW;	// read or write (currently unused) pin number (on controlPort)
	uint8_t maskE; 	// enable/pulse pin number (on controlPort)



public:
	/*! 8-bit interface constructor.
	 * @param dataPort		the port where D0~D7 pins are connected (ex &PORTA)
	 * @param dataDDR		the data port's DDR (ex. &DDRA)
	 * @param dataPIN		the input pins address (ex. &PINA)
	 * @param controlPort	the port where the E, RS, RW pins are connected (can be the same as dataPort if 4-bits mode is used)
	 * @param controlDDR	the control port's DDR
	 * @param RS			ready to send pin number (on controlPort)
	 * @param RW			read or write (currently unused) pin number (on controlPort)
	 * @param E				enable/pulse pin number (on controlPort)
	 * @warning don't forget to give the port's \b address not \b name (ex. : &PORTA, not PORTA)
	 */
	HD44780(IOAddress dataPort, IOAddress dataDDR, IOAddress dataPIN, IOAddress controlPort, IOAddress controlDDR, uint8_t RS, uint8_t RW, uint8_t E);

	/*! 4-bit interface constructor.
	 * @param port						the port where D4~D7, RS, RW and E pins are connected (ex &PORTA)
	 * @param ddr						the data port's DDR (ex. &DDRA)
	 * @param pin						the input pins address (ex. &PINA)
	 *
	 * @param startingBitForFourBitMode if 4 bits mode is used, pins D4~D7 must be connected in growing order from \a startingBitForFourBitMode to
	 * 									<code> startingBitForFourBitMode + 4 </code> on \a dataPort
	 * @param RS						ready to send pin \b number (on controlPort)
	 * @param RW						read or write (currently unused) pin \b number (on controlPort)
	 * @param E							enable/pulse pin \b number (on controlPort)
	 * @warning don't forget to give the port's \b address not \b name (ex. : &PORTA, not PORTA)
	 */
	HD44780(IOAddress port = &PORTA, IOAddress ddr = &DDRA, IOAddress pin = &PINA, uint8_t startingBitForFourBitMode = 3, uint8_t RS = 0, uint8_t RW = 1, uint8_t E = 2);

	/*! Initialize the Display.
	 * @remark this function is called by the constructor, but you can call it to reinitialize
	 */
	void initDisplay();

	/*! Clears the Display.
	 */
	void clearDisplay();

	/*! Returns the cursor to position (0,0).
	 */
	void cursorHome();


	/*! Use the cursor mode.
	 * The cursor will move when a character is entered.
	 * @param direction the cursor will move \a RIGHT or \a LEFT
	 * @see \a useShiftDisplayMode()
	 */
	void useCursorMode(Direction direction = RIGHT);

	/*! Use the display shift mode.
	 * The display will shift when a character is entered.
	 * @param direction the cursor will move \a RIGHT or \a LEFT
	 * @see useCursorMode()
	 */
	void useShiftDisplayMode(Direction direction = LEFT);

	/*! General display setup.
	 * @param displayOn powers up/ shutdowns display (not backlight)
	 * @param cursorOn the cursor will show up on the display if true
	 * @param blinkOn the cursor will blink if true
	 */
	void displaySetup(bool displayOn, bool cursorOn, bool blinkOn);

	/*! Diasplay type and font mode.
	 * @param fourLines used for 20x4 displays
	 * @param highDefFont used for 5x10 dots display (that apparently doesn't exists!)
	 */
	void functionSet(bool fourLines, bool highDefFont);

	/*! Moves the cursor to a new position.
	 * @param lineNumber the new line number
	 * @param rowNumber the new row number
	 * @pre <code> 0 <= lineNumber <= 4 </code> and <code> 0 <= rowNumber <= 20</code> for 20x4 displays
	*/
	void goToPosition(uint8_t lineNumber, uint8_t rowNumber);

	/*! Prints a character at current cursor's position.
	 * @param character an ascii character
	 */
	void printChar(char character);

	/*! Prints a characte at specified position.
	 * @param lineNumber see \a goToPosition()
	 * @param rowNumber see \a goToPosition()
	 * @param character see see \a printChar()
	 */
	void printCharAt(uint8_t lineNumber, uint8_t rowNumber, char character);

	/*! Prints a C-style string at current cursor's position.
	 * @param string a char buffer composed of ascii codes that ends with the end string char
	 */
	void printLine(const char * string);

	/*! Prints a C-style string at specified position.
	 * @param lineNumber see \a goToPosition()
	 * @param rowNumber see \a goToPosition()
	 * @param string see see \a printLine()
	 */
	void printLineAt(uint8_t lineNumber, uint8_t rowNumber, const char * string);

	/*! Prints a long number using specified radix at current cursor's position.
	 * @param number a long integer signed or not
	 * @param radix the radix (ex. 2 for binary, 10 for decimal, 16 for hexadecimal)
	 */
	void printNumber(long number, uint8_t radix = 10);

	/*! Prints a float (or single) precision floating number.
	 * @param number the float (or single) precision floating number
	 * @param minLenght the minimal number of character that must be displayed (ex. 5 for 343.00, 2 for 34 E00)
	 * @param precision the number of significative digits
	 * @see \a dtostrf()
	 */
	void printNumber(float number, uint8_t minLenght, uint8_t precision);

	/*! Prints a long number using specified radix at at specified position.
	 * @param lineNumber see \a goToPosition()
	 * @param rowNumber see \a goToPosition()
	 * @param number see \a printNumber()
	 * @param radix see \a printNumber()
	 */
	void printNumberAt(uint8_t lineNumber, uint8_t rowNumber, long number, uint8_t radix = 10);

	/*! Prints a long number using specified radix at specified position.
	 * @param lineNumber see \a goToPosition()
	 * @param rowNumber see \a goToPosition()
	 * @param number see \a printNumber()
	 * @param minLenght see \a printNumber()
	 * @param precision see \a printNumber()
	 */
	void printNumberAt(uint8_t lineNumber, uint8_t rowNumber, float number, uint8_t minLenght = 4, uint8_t precision = 4);

private:

	void waitBusyFlag();
	void pulse();
	void clearDataPort();
	void clearControlPort();
	void setDataIOMode(uint8_t mask);
	void setControlIOMode(uint8_t mask);
	void transmit(uint8_t data, uint8_t control);
	uint8_t getAddressOf(uint8_t lineNumber, uint8_t rowNumber);

	/*! Sets the cursor move direction and whether display must shift.
	 * @param cursorIncrement cursor will move right when a caracter is printed if true, left if false
	 * @param shiftDisplay the display will shift when a new character is entered if true, if false, the cursor will shift
	 */
	void shiftMode(bool cursorIncrement, bool shiftDisplay);

	/*! Sets cursor mode or display shift mode.
	 * @param shiftDisplay
	 * @param right shift direction, right if true
	 */
	void cursorOrShiftDisplay(bool shiftDisplay, bool right);


};

#endif
