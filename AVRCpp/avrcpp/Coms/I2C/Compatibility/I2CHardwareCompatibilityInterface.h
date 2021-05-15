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

#ifndef I2CHardwareCompatibilityInterface_H_
#define I2CHardwareCompatibilityInterface_H_

#if __AVR_ATmega328P__

#define TWI0_vect 			TWI_vect

#define TWI0_vect_number 	24
#define TW0DR TWDR
#define TW0BR TWBR
#define TW0CR TWCR
#define TW0SR TWSR
#define TW0AR TWAR

#define I2C0

#endif

#if __AVR_ATmega1280__

#define TWI0_vect 			TWI_vect

#define TWI0_vect_number 	39
#define TW0DR TWDR
#define TW0BR TWBR
#define TW0CR TWCR
#define TW0SR TWSR
#define TW0AR TWAR

#define I2C0

#endif

#endif /* I2CHardwareCompatibilityInterface_H_ */
