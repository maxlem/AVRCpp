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

#include "FastCallbackServer.h"


FastCallbackServer * FastCallbackServer::getInstance()
{
	static FastCallbackServer * instance;

	if(isNull(instance))
		instance = new FastCallbackServer();

	return instance;
}

FastCallbackServer::FastCallbackServer()
{
	// TODO Auto-generated constructor stub

}

FastCallbackServer::~FastCallbackServer()
{
	// TODO Auto-generated destructor stub
}


void FastCallbackServer::connect(size_t vectorNumber, Callback * callback)
{
	if(vectorNumber >= INTERRUPT_VECTOR_COUNT)
		return;

	callbackTable[vectorNumber] = callback;

}

void FastCallbackServer::dispatch(size_t vectorNumber)
{
	if(vectorNumber >= INTERRUPT_VECTOR_COUNT)
		return;

	Callback * callback = callbackTable[vectorNumber];

	if(!isNull(callback))
		callback->callback();

}


Callback * FastCallbackServer::disconnect(size_t vectorNumber)
{
	Callback * callback = callbackTable[vectorNumber];

	connect(vectorNumber, NULL);

	return callback;
}
