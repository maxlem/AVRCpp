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

#ifndef PRESCALERS_H_
#define PRESCALERS_H_

#include "../Utils/CppExtensions.h"

namespace Timers
{

namespace Prescalers
{
	/*!
	 * Timer prescaler enum
	 * The timer's frequency will be \f$ \frac{freq_{clockSource}}{prescaler} \f$
	 * where \f$ freq_{clockSource} \f$ is typically the cpu frequency but can be provided externally
	 */
	enum Prescaler
	{
		STOP_TIMER_0 = 0x00,		//!< stops the timer

		DIV_1 = 0x01,			//!< divide clock source by 1

		DIV_8 = 0x02,			//!< divide clock source by 8

		DIV_NO_EXT_32 = 0x03,			//!< divide clock source by 32
		DIV_EXT_64 = 0x03,			//!< divide clock source by 64

		DIV_NO_EXT_64 = 0x04,			//!< divide clock source by 64
		DIV_EXT_256 = 0x04,			//!< divide clock source by 256

		DIV_NO_EXT_128 = 0x05,			//!< divide clock source by 128
		DIV_EXT_1024 = 0x05,			//!< divide clock source by 1024

		DIV_NO_EXT_256 = 0x06,			//!< divide clock source by 256
		EXT_FALLING = 0x06,			//!< clocksource from Tn pin falling edge

		DIV_NO_EXT_1024 = 0x07,			//!< divide clock source by 1024
		EXT_RISING = 0x07,			//!< clocksource from Tn pin rising edge

		FASTEST_1 = DIV_1,			//!< same as DIV_1
		SLOWEST_NO_EXT_1024 = DIV_NO_EXT_1024,		//!< same as DIV_1024
		SLOWEST_EXT_1024 = DIV_EXT_1024		//!< same as DIV_1024

	};

}
}

#endif /* PRESCALERS_H_ */
