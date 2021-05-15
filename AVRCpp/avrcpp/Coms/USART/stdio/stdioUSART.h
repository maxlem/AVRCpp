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

#ifndef stdioUSART_H_
#define stdioUSART_H_

#include <stdio.h>
#include "../USARTHardware.h"

namespace Coms
{
namespace USART
{



FILE * fdevopen(uint8_t mode, USARTHardware * usartHardware);

void fdevclose(uint8_t mode, FILE * stream);

/*!
 * stdio-compliant put_char function
 * @param c the character to print
 * @param stream the stream that called the function
 * @return 0 if all went well
 * @warning not meant to be used, \a see \fdevopen()
 */
int put_char(char c, FILE * stream);

/*!
 * stdio-compliant get_char function
 * @param stream the stream that called the function
 * @return the character read
 * @warning not meant to be used, \a see \fdevopen()
 */
int get_char(FILE * stream);

}

}

#endif /* stdioUSART_H_ */
