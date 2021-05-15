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

#ifndef STRINGBUFFER_H_
#define STRINGBUFFER_H_

#include "Queue.h"

class StringBuffer: public Queue<char>
{
public:
	StringBuffer(size_t size, char errorSentinel = '\0');
	virtual ~StringBuffer();

	char * operator >>(char * & lhs) const;

	StringBuffer & operator <<(const char rhs);

	StringBuffer & operator <<(const char * rhs);

	StringBuffer & operator <<(const prog_mem * rhs);

	StringBuffer & operator <<(const Buffer<char> & rhs);

	StringBuffer & operator <<(StringBuffer & rhs);

};

inline char * operator <<(char * & lhs, const StringBuffer & rhs)
{
	return rhs >> lhs;
}

#endif /* STRINGBUFFER_H_ */
