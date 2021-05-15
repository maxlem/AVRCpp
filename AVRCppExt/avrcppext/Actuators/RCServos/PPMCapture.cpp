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

#include "PPMCapture.h"

PPMCapture::PPMCapture(Counter16 * counter, Capturer16 * capturer, float ticksPer_us, IOAddress icPinDDR, uint16_t icPinNumber, uint8_t numberOfChannels) :
counter(counter), capturer(capturer), ticksPer_us(ticksPer_us), numberOfChannels(numberOfChannels)
{
	clearBit(*icPinDDR, icPinNumber);
	pulseWidths = new uint16_t[numberOfChannels];
	capturer->enableNoiseCanceler();
	capturer->triggerOnFallingEdge();
	capturer->connectCallback(this);
	capturer->enableICRInterrupts();
}

PPMCapture::~PPMCapture()
{
	delete pulseWidths;
}


uint16_t PPMCapture::getPulseWidth(uint8_t channelNumber)
{
	return pulseWidths[channelNumber];
}
#include <stdio.h>
void PPMCapture::callback()
{
	uint16_t currentICR = capturer->readICR();

	uint16_t currentPulse = (currentICR - lastICRvalue) / ticksPer_us;

	lastICRvalue = currentICR;

	pulseWidths[currentChannel] = currentPulse;

	currentChannel++;

	if(currentChannel >= numberOfChannels || currentPulse > 3000)
	{
		counter->setValue(0);
		currentChannel = 0;
		lastICRvalue = 0;
	}

}
