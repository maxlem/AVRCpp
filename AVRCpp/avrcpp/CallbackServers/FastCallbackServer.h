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

#ifndef FastCallbackServer_H_
#define FastCallbackServer_H_
#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "Callback.h"
#include "Compatibility/CallbackServerMacros.h"

class FastCallbackServer
{
public:
	static FastCallbackServer * getInstance();

	virtual ~FastCallbackServer();

	void connect(size_t vectorNumber, Callback * callback);

	Callback * disconnect(size_t vectorNumber);

	void dispatch(size_t vectorNumber);

protected :
	FastCallbackServer();
	Callback * callbackTable[INTERRUPT_VECTOR_COUNT];
};

#define DEFINE_FAST_CALLBACK(vectorName, vectorNumber)\
	void vectorName (void)\
	{\
		FastCallbackServer::getInstance()->dispatch(vectorNumber);\
	}\

#endif /* FastCallbackServer_H_ */
