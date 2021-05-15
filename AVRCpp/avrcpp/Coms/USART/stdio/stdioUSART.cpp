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

#include "stdioUSART.h"

namespace Coms
{
namespace USART
{

FILE* fdevopen(uint8_t mode, USARTHardware * usartHardware)
{
	FILE * stream = new FILE();


	if(mode & _FDEV_SETUP_WRITE)
	{
		usartHardware->enableTransmitter();
		stream->put = put_char;
	}

	if(mode & _FDEV_SETUP_READ)
	{
		usartHardware->enableReceiver();
		stream->get = get_char;
	}

	stream->flags = mode;

	stream->udata = usartHardware;

	return stream;
}


void fdevclose(uint8_t mode, FILE * stream)
{
	USARTHardware * usartHardware = (USARTHardware *)stream->udata;

	if(mode & _FDEV_SETUP_WRITE)
	{
		usartHardware->disableTransmitter();
		stream->put = NULL;

		stream->flags &= ~_FDEV_SETUP_WRITE;
	}

	if(mode & _FDEV_SETUP_READ)
	{
		usartHardware->disableReceiver();
		stream->get = NULL;

		stream->flags &= ~_FDEV_SETUP_READ;
	}

	if(!stream->flags)
	{
		delete stream;
	}
}


int put_char(char c, FILE* stream)
{
	USARTHardware * usartHardware = (USARTHardware *)stream->udata;

	while(!usartHardware->isTransmitterReady());

	usartHardware->writeFrame(c);

	return 0;
}

int get_char(FILE* stream)
{
	USARTHardware * usartHardware = (USARTHardware *)stream->udata;

	while(!usartHardware->isFrameReceived());

	return usartHardware->readFrame();
}

}

}

