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

#ifndef SPIHardwareCompatibilityInterface_H_
#define SPIHardwareCompatibilityInterface_H_

#if __AVR_ATmega328P__

#define SPI_STC_vect_number 	17
#define SPI_DDR 				DDRB
#define SPI_SS_PIN 				PINB2
#define SPI_SCK_PIN				PINB5
#define SPI_MOSI_PIN			PINB3
#define SPI_MISO_PIN			PINB4

#endif

#if __AVR_ATmega1280__

#define SPI_STC_vect_number 	24
#define SPI_DDR 				DDRB
#define SPI_SS_PIN 				PINB0
#define SPI_SCK_PIN				PINB1
#define SPI_MOSI_PIN			PINB2
#define SPI_MISO_PIN			PINB3
#endif

#endif /* SPIHardwareCompatibilityInterface_H_ */
