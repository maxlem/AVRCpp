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

#include "Compatibility/USARTHardwareCompatibility.h"
#include "../../Utils/BitManipulation.h"
#include "../../CallbackServers/FastCallbackServer.h"
namespace Coms
{

namespace USART
{

#define USART_UBRR_MASK 				0x0FFFul
#define UCSRB_READ_WRITE_CONTROL_MASK	0xF8	// 0b11111000


USARTHardware::USARTHardware(uint8_t USART_RX_vect_number, uint8_t USART_UDRE_vect_number, uint8_t USART_TX_vect_number, IOAddress udr, IOAddress ubrrh, IOAddress ubrrl, IOAddress ucsra, IOAddress ucsrb, IOAddress ucsrc) :
USART_RX_vect_number(USART_RX_vect_number), USART_UDRE_vect_number(USART_UDRE_vect_number), USART_TX_vect_number(USART_TX_vect_number), udr(udr), ubrrh(ubrrh), ubrrl(ubrrl), ucsra(ucsra), ucsrb(ucsrb), ucsrc(ucsrc)
{
	configureDefaults();
}

uintmax_t USARTHardware::getBitRate()
{

	uintmax_t divider;

	if(bitIsSetInRegister(*ucsrc, UMSEL))
		divider = 2;
	else if(bitIsSetInRegister(*ucsra, U2X))
		divider = 8;
	else
		divider = 16;

	uint16_t ubrr = *ubrrl;

	ubrr += ((uint16_t)*ubrrh) << 8;

	return F_CPU /(divider * (ubrr + 1));
}


void USARTHardware::connectFrameReceivedCallback(Callback * frameReceivedCallback)
{
	FastCallbackServer::getInstance()->connect(USART_RX_vect_number, frameReceivedCallback);
}

Callback * USARTHardware::disconnectFrameReceivedCallback()
{
	return FastCallbackServer::getInstance()->disconnect(USART_RX_vect_number);
}


void USARTHardware::connectTransmitterReadyCallback(Callback * transmitterReadyCallback)
{
	FastCallbackServer::getInstance()->connect(USART_UDRE_vect_number, transmitterReadyCallback);
}

Callback * USARTHardware::disconnectTransmitterReadyCallback()
{
	return FastCallbackServer::getInstance()->disconnect(USART_UDRE_vect_number);
}


void USARTHardware::connectFrameTransmittedCallback(Callback * frameTransmittedCallback)
{
	FastCallbackServer::getInstance()->connect(USART_TX_vect_number, frameTransmittedCallback);
}

Callback * USARTHardware::disconnectFrameTransmittedCallback()
{
	return FastCallbackServer::getInstance()->disconnect(USART_TX_vect_number);
}

}

}
