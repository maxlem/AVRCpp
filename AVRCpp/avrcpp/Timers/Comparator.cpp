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

#include "Comparator.h"

namespace Timers
{

template <typename IOAddressType, typename uint_t>
Comparator<IOAddressType, uint_t>::Comparator(uint8_t callbackVectorNumber, IOAddressType ocr, IOAddress tccra, uint8_t comMask, IOAddress timsk, uint8_t ocie, IOAddress tifr, uint8_t ocf) :
CallbackConnector(callbackVectorNumber),
ocr(ocr), tccra(tccra), comMask(comMask), timsk(timsk), ocie(ocie), tifr(tifr), ocf(ocf)
{
	// TODO Auto-generated constructor stub

}

template <typename IOAddressType, typename uint_t>
Comparator<IOAddressType, uint_t>::~Comparator()
{
	// TODO Auto-generated destructor stub
}

template class Comparator<IOAddress, uint8_t>;

template class Comparator<IOAddress16, uint16_t>;

}
