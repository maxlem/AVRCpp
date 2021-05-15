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

#include "RCServo.h"


RCServo::RCServo(Comparator16 * comparator, IOAddress ocPinDDR, uint8_t ocPinNumber, uint16_t ocrValueFor1000us, uint16_t ocrValueFor2000us) :
comparator(comparator), ocrValueFor1000us(ocrValueFor1000us), ocrValueFor2000us(ocrValueFor2000us)
{

	setBit(*ocPinDDR, ocPinNumber);

	ticksPer_us = (float)ocrValueFor2000us / 2000.0;

}

RCServo::~RCServo()
{

}


void RCServo::setPulseWidth(uint16_t pulseWidth_us)
{

	uint16_t ocrValue = ticksPer_us * pulseWidth_us;

	if(ocrValue < ocrValueFor1000us)
		comparator->setOCRValue(ocrValueFor1000us);
	else if(ocrValue > ocrValueFor2000us)
		comparator->setOCRValue(ocrValueFor2000us);
	else
		comparator->setOCRValue(ocrValue);

}

