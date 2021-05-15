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



void Timer16bits3OCR::setWaveGenerationMode(uint8_t wgm3, uint8_t wgm2, uint8_t wgm1, uint8_t wgm0)
{
	changeBitValueTo(*tccra, WGM10, wgm0);

	changeBitValueTo(*tccra, WGM11, wgm1);

	changeBitValueTo(*tccrb, WGM12, wgm2);

	changeBitValueTo(*tccrb, WGM13, wgm3);

}


Counter16 * Timer16bits3OCR::getCounter()
{
	return &counter;
}

Comparator16 * Timer16bits3OCR::getComparatorA()
{
	return &comparatorA;
}

Comparator16 * Timer16bits3OCR::getComparatorB()
{
	return &comparatorB;
}

Comparator16 * Timer16bits3OCR::getComparatorC()
{
	return &comparatorC;
}

Capturer16 * Timer16bits3OCR::getCapturer()
{
	return &capturer;
}
