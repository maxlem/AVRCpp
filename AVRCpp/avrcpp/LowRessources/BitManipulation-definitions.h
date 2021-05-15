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

bool interruptsEnabled()
{
	return SREG & bitValue(SREG_I);
}


uint8_t buildMask(uint8_t bitName1, uint8_t bitName2, uint8_t bitName3, uint8_t bitName4, uint8_t bitName5, uint8_t bitName6, uint8_t bitName7, uint8_t bitName8)
{
	return ((1 << bitName1) | (1 << bitName2) | (1 << bitName3) | (1 << bitName4) | (1 << bitName5) | (1 << bitName6) | (1 << bitName7) | (1 << bitName8)) & 0xFF;
}


bool bitIsSet(uint8_t mask, uint8_t bit)
{
	return (mask >> bit) & 0x01u;
}

void enableInterrupts()
{
	asm(" sei;");
}

void disableInterrupts()
{
	asm(" cli;");
}
