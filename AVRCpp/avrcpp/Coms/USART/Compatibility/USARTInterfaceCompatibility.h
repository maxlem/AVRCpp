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

#ifndef USARTINTERFACECOMPATIBILITY_H_
#define USARTINTERFACECOMPATIBILITY_H_

#if __AVR_ATmega16__
	#define SINGLE_USART
#endif

#if __AVR_ATmega644__
	#define SINGLE_USART
#endif
#if __AVR_ATmega328P__

	#define USART0
	#define USART0_RX_vect_number 18
	#define USART0_UDRE_vect_number 19
	#define USART0_TX_vect_number 20

	#define USART0_RXC_vect USART_RXC_vect
	#define USART0_TXC_vect USART_TXC_vect
	#define USART0_UDRE_vect USART_UDRE_vect
// UCSRA :
	#define RXC    7
	#define TXC    6
	#define UDRE   5
	#define FE     4
	#define DOR    3
	#define UPE    2
	#define U2X    1
	#define MPCM   0

// UCSRB :
	#define RXCIE  7
	#define TXCIE  6
	#define UDRIE  5
	#define RXEN   4
	#define TXEN   3
	#define UCSZ2  2
	#define RXB8   1
	#define TXB8   0

// UCSRC :
	#define UMSEL1 7 //Master SPI
	#define UMSEL0 6
	#define UMSEL	UMSEL0
	#define UPM1   5
	#define UPM0   4
	#define USBS   3
	#define UCSZ1  2
	#define UCSZ0  1
	#define UCPOL  0
//
//#define MPCM MPCM0
//#define U2X U2X0
//#define UPE UPE0
//#define DOR DOR0
//#define FE FE0
//#define UDRE UDRE0
//#define TXC TXC0
//#define RXC RXC0
//
//#define TXB8 TXB80
//#define RXB8 RXB80
//#define UCSZ2 UCSZ02
//#define TXEN TXEN0
//#define RXEN RXEN0
//#define UDRIE UDRIE0
//#define TXCIE TXCIE0
//#define RXCIE RXCIE0
//
//#define UCPOL UCPOL
//#define UCSZ0 UCSZ00
//#define UCPHA UCPHA0
//#define UCSZ1 UCSZ01
//#define UDORD UDORD
//#define USBS USBS0
//#define UPM0 UPM00
//#define UPM1 UPM01
//#define UMSEL0 UMSEL00
//#define UMSEL1 UMSEL01
//#define UMSEL UMSEL0

//#define UBRR0 UBRR0_0
//#define UBRR1 UBRR0_1
//#define UBRR2 UBRR0_2
//#define UBRR3 UBRR0_3
//#define UBRR4 UBRR0_4
//#define UBRR5 UBRR0_5
//#define UBRR6 UBRR0_6
//#define UBRR7 UBRR0_7
//
//#define UBRR8 UBRR0_8
//#define UBRR9 UBRR0_9
//#define UBRR10 UBRR0_10
//#define UBRR11 UBRR0_11

#endif

#if __AVR_ATmega128__
	#define USART0
	#define USART1
#endif

#ifdef SINGLE_USART

	#define USART0

	#define UDR0	UDR
	#define UBRR0H	UBRRH
	#define UBRR0L	UBRRL
	#define UCSR0A	UCSRA
	#define UCSR0B	UCSRB
	#define UCSR0C	UCSRC

	#define USART0_RXC_vect USART_RXC_vect
	#define USART0_TXC_vect USART_TXC_vect
	#define USART0_UDRE_vect USART_UDRE_vect

#endif

#if __AVR_ATmega1280__

	#define USART0
	#define USART0_RX_vect_number 25
	#define USART0_UDRE_vect_number 26
	#define USART0_TX_vect_number 27

	#define USART1
	#define USART1_RX_vect_number 36
	#define USART1_UDRE_vect_number 37
	#define USART1_TX_vect_number 38

	#define USART2
	#define USART2_RX_vect_number 51
	#define USART2_UDRE_vect_number 52
	#define USART2_TX_vect_number 53

	#define USART3
	#define USART3_RX_vect_number 54
	#define USART3_UDRE_vect_number 55
	#define USART3_TX_vect_number 56

// UCSRA :
	#define RXC    7
	#define TXC    6
	#define UDRE   5
	#define FE     4
	#define DOR    3
	#define UPE    2
	#define U2X    1
	#define MPCM   0

// UCSRB :
	#define RXCIE  7
	#define TXCIE  6
	#define UDRIE  5
	#define RXEN   4
	#define TXEN   3
	#define UCSZ2  2
	#define RXB8   1
	#define TXB8   0

// UCSRC :
	#define UMSEL1 7 //Master SPI
	#define UMSEL0 6
	#define UMSEL	UMSEL0
	#define UPM1   5
	#define UPM0   4
	#define USBS   3
	#define UCSZ1  2
	#define UCSZ0  1
	#define UCPOL  0

#endif

#endif /* USARTINTERFACECOMPATIBILITY_H_ */
