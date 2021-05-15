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

#include "DictionnaryCallbackServer.h"






DictionnaryCallbackServer * DictionnaryCallbackServer::getInstance()
{
	static DictionnaryCallbackServer * instance;

	if(isNull(instance))
		instance = new DictionnaryCallbackServer;

	return instance;
}

DictionnaryCallbackServer::DictionnaryCallbackServer()
{
	interruptToCallback = new Dictionary<void(*)(), Callback *>(INTERRUPT_VECTOR_COUNT);
}

DictionnaryCallbackServer::~DictionnaryCallbackServer()
{
	// TODO Auto-generated destructor stub
}

void DictionnaryCallbackServer::connect(void(*interrupt)(), Callback * callback)
{
	Callback ** callbackSlot = interruptToCallback->find(interrupt);

	if(isNull(callbackSlot))
		interruptToCallback->insertElement(interrupt, callback);
	else
		*callbackSlot = callback;

}

void DictionnaryCallbackServer::dispatch(void(*interrupt)())
{
	Callback ** callbackSlot = interruptToCallback->find(interrupt);

	if(!isNull(callbackSlot))
	{
		Callback * callback = *callbackSlot;

		if(!isNull(callback))
			callback->callback();
	}

}

void DictionnaryCallbackServer::disconnect(void(*interrupt)())
{
	Callback ** callbackSlot = interruptToCallback->find(interrupt);

	if(!isNull(callbackSlot))
		*callbackSlot = NULL;
}

//void DictionnaryCallbackServer::initialize(void(*interrupt)())
//{
//	interruptToCallback->insertElement(interrupt, NULL);
//
//}
