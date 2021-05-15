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

#include "StringBuffer.h"

StringBuffer::StringBuffer(size_t size, char errorSentinel) : Queue<char>(size, errorSentinel)
{
	// TODO Auto-generated constructor stub

}

StringBuffer::~StringBuffer()
{
	// TODO Auto-generated destructor stub
}

char * StringBuffer::operator >>(char * & lhs) const
{
	if (isEmpty())
	{
		lhs[0] = '\0';
	}
	else
	{
		lhs = new char[count + 1]; // TODO : use realloc

		if(frontIndex <= tailIndex)
		{
			memcpy(lhs, &memory[frontIndex], count);
		}
		else //we have wrapped around we must copy it two steps :
		{
			memcpy(lhs, &memory[frontIndex], (size - frontIndex));
			memcpy(& lhs[(size - frontIndex) + 1], memory, tailIndex - 1);
		}
		lhs[count] = '\0';
	}

	return lhs;
}

StringBuffer & StringBuffer::operator <<(const char * rhs)
{
	for(size_t index = 0; index < strlen(rhs) + 1; index++)
		this->enQueue((char&)rhs[index]);

	return *this;
}


StringBuffer & StringBuffer::operator <<(const char rhs)
{
	this->enQueue((char&)rhs);

	return *this;
}

StringBuffer & StringBuffer::operator <<(const prog_mem * rhs)
{
	const char * dup = strdup(rhs, Allocators::STACK);

	*this << dup;

	return *this;
}

StringBuffer & StringBuffer::operator <<(const Buffer<char> & rhs)
{
	return (StringBuffer &)Queue<char>::operator <<(rhs);
}

StringBuffer & StringBuffer::operator <<(StringBuffer & rhs)
{
	for(size_t index = 0; index < rhs.numberOfElements(); index++)
		this->enQueue((char&)rhs[index]);

	return *this;
}

