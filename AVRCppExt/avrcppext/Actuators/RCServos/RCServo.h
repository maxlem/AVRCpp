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

#ifndef RCServo_H_
#define RCServo_H_

#include "Utils/CppExtensions.h"
#include "Utils/BitManipulation.h"
#include "Timers/Comparator.h"

using Timers::Comparator16;

class RCServo
{
public:
	RCServo(Comparator16 * comparator, IOAddress ocPinDDR, uint8_t ocPinNumber, uint16_t ocrValueFor1000us, uint16_t ocrValueFor2000us);
	virtual ~RCServo();

	void setPulseWidth(uint16_t pulseWidth_us);

protected:
	Comparator16 * comparator;

	uint16_t ocrValueFor1000us;
	uint16_t ocrValueFor2000us;
	float ticksPer_us;

};

#endif /* RCServo_H_ */
