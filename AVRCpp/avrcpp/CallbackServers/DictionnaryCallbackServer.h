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

#ifndef CallbackServer_H_
#define CallbackServer_H_

#include "../Utils/CppExtensions.h"
#include "../DataStructures/Dictionary.h"
#include "Callback.h"
#include "Compatibility/CallbackServerMacros.h"


class DictionnaryCallbackServer
{
public:
	static DictionnaryCallbackServer * getInstance();

	virtual ~DictionnaryCallbackServer();

	void connect(void(*interrupt)(), Callback * callback);

	void disconnect(void(*interrupt)());

	void dispatch(void(*interrupt)());

//	void initialize(void(*interrupt)());

protected:

	DictionnaryCallbackServer();

	Dictionary<void(*)(), Callback *> * interruptToCallback;
};

#define DEFINE_DICTIONNARY_CALLBACK(vectorName)\
	void vectorName (void)\
	{\
		DictionnaryCallbackServer::getInstance()->dispatch(vectorName);\
	}\



#endif /* CallbackServer_H_ */
