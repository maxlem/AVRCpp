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

#ifndef ChannelModesV3_H_
#define ChannelModesV3_H_

#include "../Utils/Utils.h"
namespace ADCs
{

namespace ChannelModes
{
	/*!
	 * Channel selection and gain modes
	 * - For ADCX \a toVolts() will return \f$ voltage = \frac{voltage_{ADCX} * 1024 }{voltage_{reference}} \f$
	 * - For ADCX_ADCY_xGAIN \a toVolts() will return \f$ voltage = \frac{voltage_{ADCX}^{time_{0}} - voltage_{ADCY}^{time_{1}} * GAIN * 512 }{voltage_{reference}} \f$
	 */
	enum ChannelMode {

		//!< compare to reference voltage modes :

		ADC0 = 0x00,				//!< compare voltage at pin ADC0 with the reference voltage
		ADC1 = 0x01,				//!< idem with pin ADC1
		ADC2 = 0x02,				//!< idem with pin ADC2
		ADC3 = 0x03,				//!< idem with pin ADC3
		ADC4 = 0x04,				//!< idem with pin ADC4
		ADC5 = 0x05,				//!< idem with pin ADC5
		ADC6 = 0x06,				//!< idem with pin ADC6
		ADC7 = 0x07,				//!< idem with pin ADC7


		//!< differential modes :

		ADC0_ADC0_X10 = 0x08,		//!< compare voltage at pin ADC0 with another reading at ADC0 and amplify the result by 10
		ADC1_ADC0_X10 = 0x09,		//!< compare voltage at pin ADC1 with another reading at ADC0 and amplify the result by 10
		ADC0_ADC0_X200 = 0x0A,		//!< compare voltage at pin ADC0 with another reading at ADC0 and amplify the result by 200
		ADC1_ADC0_X200 = 0x0B,		//!< compare voltage at pin ADC1 with another reading at ADC0 and amplify the result by 200
		ADC2_ADC2_X10 = 0x0C,		//!< compare voltage at pin ADC2 with another reading at ADC2 and amplify the result by 10
		ADC3_ADC2_X10 = 0x0D,		//!< compare voltage at pin ADC3 with another reading at ADC2 and amplify the result by 10
		ADC2_ADC2_X200 = 0x0E,		//!< compare voltage at pin ADC2 with another reading at ADC2 and amplify the result by 200
		ADC3_ADC2_X200 = 0x0F		//!< compare voltage at pin ADC3 with another reading at ADC2 and amplify the result by 200

	};

	size_t gain(ChannelMode mode);

}

}
#endif /* ChannelModes_H_ */
