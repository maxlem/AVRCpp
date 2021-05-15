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

#ifndef PrescalersV3_H_
#define PrescalersV3_H_

#include "../Utils/Utils.h"

namespace ADCs
{

namespace Prescalers
{

	/*! AnalogToDigital prescaler enum
	* The AnalogToDigital's frequency will be \f$ \frac{freq_{clockSource}}{prescaler} \f$
	* where \f$ freq_{clockSource} \f$ is typically the cpu frequency but can be provided externally
	*/
	enum Prescaler {
		DIV_2 = 0x00,					//!<!< divide clock source by 2
		DIV_4 = 0x02,					//!<!< divide clock source by 4
		DIV_8 = 0x03,					//!<!< divide clock source by 8
		DIV_16 = 0x04,					//!<!< divide clock source by 16
		DIV_32 = 0x05,					//!<!< divide clock source by 32
		DIV_64 = 0x06,					//!<!< divide clock source by 64
		DIV_128 = 0x07,					//!<!< divide clock source by 128
		FASTEST_2 = DIV_2,					//!<!< same as DIV2 least precise
		SLOWEST_128 = DIV_128				//!<!< same as DIV128 most precise
	};

}

}
#endif /* Prescalers_H_ */
