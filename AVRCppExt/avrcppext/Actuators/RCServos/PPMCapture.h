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

#ifndef PPMCapture_H_
#define PPMCapture_H_

#include "Utils/CppExtensions.h"
#include "Utils/BitManipulation.h"
#include "Timers/Counter.h"
#include "Timers/Capturer.h"
#include "CallbackServers/Callback.h"

using Timers::Capturer16;
using Timers::Counter16;

class PPMCapture : public Callback
{
public:
	PPMCapture(Counter16 * counter, Capturer16 * capturer, float ticksPer_us, IOAddress icPinDDR, uint16_t icPinNumber, uint8_t numberOfChannels);
	virtual ~PPMCapture();

	uint16_t getPulseWidth(uint8_t channelNumber);

	void callback();

protected:

	Counter16 * counter;
	Capturer16 * capturer;
	float ticksPer_us;

	uint8_t numberOfChannels;

	uint16_t * pulseWidths;
	uint8_t currentChannel;
	uint8_t lastICRvalue;
};

#endif /* PPMCapture_H_ */