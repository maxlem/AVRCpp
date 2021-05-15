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

#ifndef USARTHardwareCompatibility_H_
#define USARTHardwareCompatibility_H_

#include "USARTInterfaceCompatibility.h"
#include "../USARTHardware.h"
#include "../../../CallbackServers/FastCallbackServer.h"

namespace Coms
{

namespace USART
{


#define USARTHardware_CREATE(number) \
	new USARTHardware(USART##number##_RX_vect_number, USART##number##_UDRE_vect_number, USART##number##_TX_vect_number, &UDR##number, &UBRR##number##H, &UBRR##number##L, &UCSR##number##A, &UCSR##number##B, &UCSR##number##C)

#define USARTHardware_CASE(number)\
	case number:		static USARTHardware * usart##number = NULL;\
						if(isNull(usart##number))\
							usart##number = USARTHardware_CREATE(number);\
						instance = usart##number;\
						break

#define USART_ISR(number)\
ISR(USART##number##_RX_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(USART##number##_RX_vect_number);\
}\
ISR(USART##number##_UDRE_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(USART##number##_UDRE_vect_number);\
}\
ISR(USART##number##_TX_vect)\
{\
	FastCallbackServer::getInstance()->dispatch(USART##number##_TX_vect_number);\
}

#ifdef USART0
	USART_ISR(0);
#endif
#ifdef USART1
	USART_ISR(1);
#endif
#ifdef USART2
	USART_ISR(2);
#endif
#ifdef USART3
	USART_ISR(3);
#endif

USARTHardware* USARTHardware::getUSARTHardware(size_t number)
{
	static USARTHardware* instance = NULL;

	switch(number)
	{
#ifdef USART0
				USARTHardware_CASE(0);
#endif
#ifdef USART1
				USARTHardware_CASE(1);
#endif
#ifdef USART2
				USARTHardware_CASE(2);
#endif
#ifdef USART3
				USARTHardware_CASE(3);
#endif

	default:	instance = NULL;
	}

	return instance;
}

}

}

#endif /* USARTHardwareCompatibility_H_ */
