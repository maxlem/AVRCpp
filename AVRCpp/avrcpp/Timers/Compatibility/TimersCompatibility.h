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

#ifndef TimersCompatibility_H_
#define TimersCompatibility_H_

#if __AVR_ATtiny45__

#define Timer8bits2OCR0

#define TIMER0_COMPA_vect_number 10
#define TIMER0_COMPB_vect_number 11
#define TIMER0_OVF_vect_number 5
#define TIFR0 TIFR
#define TIMSK0 TIMSK

#define Timer8bits2OCR1

#define TIMER1_COMPA_vect_number 3
#define TIMER1_COMPB_vect_number 9
#define TIMER1_OVF_vect_number 4
#define TIFR1 TIFR
#define TIMSK1 TIMSK
#endif

#if __AVR_ATmega128__

#define Timer8OCRA0
#define Timer16bits3OCR0
#endif

#if __AVR_ATmega328P__

#define Timer8bits2OCR0

#define TIMER0_COMPA_vect_number 14
#define TIMER0_COMPB_vect_number 15
#define TIMER0_OVF_vect_number 16

#define Timer16bits2OCR1

#define TIMER1_CAPT_vect_number 10
#define TIMER1_COMPA_vect_number 11
#define TIMER1_COMPB_vect_number 12
#define TIMER1_OVF_vect_number 13

#define Timer8bits2OCR2

#define TIMER2_COMPA_vect_number 7
#define TIMER2_COMPB_vect_number 8
#define TIMER2_OVF_vect_number 9

#endif

#if __AVR_ATmega1280__

#define WGM0	WGM10

#define Timer8bits2OCR0

#define TIMER0_COMPA_vect_number 21
#define TIMER0_COMPB_vect_number 22
#define TIMER0_OVF_vect_number 23

#define Timer16bits3OCR1

#define TIMER1_CAPT_vect_number 16
#define TIMER1_COMPA_vect_number 17
#define TIMER1_COMPB_vect_number 18
#define TIMER1_COMPC_vect_number 19
#define TIMER1_OVF_vect_number 20

#define Timer8bits2OCR2

#define TIMER2_COMPA_vect_number 13
#define TIMER2_COMPB_vect_number 14
#define TIMER2_OVF_vect_number 15

#define Timer16bits3OCR3

#define TIMER3_CAPT_vect_number 31
#define TIMER3_COMPA_vect_number 32
#define TIMER3_COMPB_vect_number 33
#define TIMER3_COMPC_vect_number 34
#define TIMER3_OVF_vect_number 35

#define Timer16bits3OCR4

#define TIMER4_CAPT_vect_number 41
#define TIMER4_COMPA_vect_number 42
#define TIMER4_COMPB_vect_number 43
#define TIMER4_COMPC_vect_number 44
#define TIMER4_OVF_vect_number 45

#define Timer16bits3OCR5

#define TIMER5_CAPT_vect_number 46
#define TIMER5_COMPA_vect_number 47
#define TIMER5_COMPB_vect_number 48
#define TIMER5_COMPC_vect_number 49
#define TIMER5_OVF_vect_number 50

#endif
#endif /* TimersCompatibility_H_ */
