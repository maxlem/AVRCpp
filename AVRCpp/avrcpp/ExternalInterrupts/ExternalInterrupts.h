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

#ifndef EXTERNALINTERRUPTS_H_
#define EXTERNALINTERRUPTS_H_
#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"

/*!
 * External interrupt class
 * @remarks this class is a Singleton
 */
class ExternalInterrupt {
public:

	/*!
	 * External interrupt sense modes
	 */
	enum InterruptSenseMode
	{
		LOGICAL_LOW = 0x00u, 	//!<< a logical low voltage level on this instance's pin triggers an interrupt
		ANY_CHANGE = 0x01, 		//!<< any logical voltage level change on this instance's pin triggers an interrupt
		FALLING_EDGE = 0x02, 	//!<< a logical voltage level that falls from high to low on this instance's pin triggers an interrupt
		RISING_EDGE = 0x03		//!<< a logical voltage level that rises from low to high on this instance's pin triggers an interrupt
	};

	virtual ~ExternalInterrupt(){}

	/*!
	 * Singleton accessor
	 * @param number the External interrupt pin number
	 * @return the unique instance to ExternalInterrupt for the specified pin number
	 */
	static ExternalInterrupt * getInstance(size_t number);

	/*!
	 * For interrupt service routines, not mean for the user
	 */
	void externalInterruptCallBack()
	{
		if(!isNull(interruptCallBack))
			interruptCallBack();
	}

	/*!
	 *
	 * @param interruptCallBack
	 */
	void setInterruptCallBack(void (*interruptCallBack)())
	{
		if(isNull(interruptCallBack))
		{
			clearBit(*eimsk, eie);
			this->interruptCallBack = NULL;
		}
		else
		{
			this->interruptCallBack = interruptCallBack;
			setBit(*eimsk, eie);
		}



	}

	/*!
	 * Configuration function
	 * @param mode the External interrupt sense mode
	 * @see \a InterruptSenseMode
	 */
	void configure(InterruptSenseMode mode)
	{
		setConfig(eiscr, modeMask, mode);
	}

protected:
	ExternalInterrupt(IOAddress eiscr, InterruptSenseMode mode, uint8_t modeMask, IOAddress eimsk, uint8_t eie, IOAddress eifr, uint8_t eief);
private:


	/*!
	 * External interrupt sense control
	 */
	IOAddress eiscr;

	/*!
	 * The External interrupt sense mode
	 */
	InterruptSenseMode mode;

	/*!
	 * mask for ISC#0 and ISC#1 bits in eiscr
	 */
	uint8_t modeMask;

	/*!
	 * External interrupt mask
	 */
	IOAddress eimsk;

	/*!
	 * External Interrupt enable flag number
	 */
	uint8_t eie;

	/*!
	 * External interrupt flags
	 */
	IOAddress eifr;

	/*!
	 * External interrupt flag number
	 */
	uint8_t eief;


	void (*interruptCallBack)();
};

#endif /* EXTERNALINTERRUPTS_H_ */
