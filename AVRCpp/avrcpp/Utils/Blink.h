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

#ifndef BLINK_H_
#define BLINK_H_
#include "CppExtensions.h"
#include "BitManipulation.h"

/*!
 * Simple led blinking class
 */
class Blink
{
private:
	IOAddress port;
	IOAddress ddr;
	uint8_t pin;
	size_t repetitions;
	size_t delayMS;
public:
	/*!
	 * The constructor
	 * @param port the port's \b address (ex. &PORTA)
	 * @param ddr the \a port data direction register's \b address (ex. &DDRA)
	 * @param pin the pin number on port \a port
	 * @param repetitions the default number of repetition
	 * @param delayMS the default delay between repetitions (in milliseconds)
	 * @see blink()
	 */
	Blink(IOAddress port, IOAddress ddr, uint8_t pin, uint8_t repetitions = 2, size_t delayMS = 100);

	/*!
	 * Blink led funciton
	 * @param repetitions number of repetitions
	 * @param delayMS delay between repetitions (in miliseconds)
	 */
	void blink(size_t repetitions, size_t delayMS);

	/*!
	 * Blink led funciton
	 */
	void blink()
	{
		blink(repetitions, delayMS);
	}
};
#endif
