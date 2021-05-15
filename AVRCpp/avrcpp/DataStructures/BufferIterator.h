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

#ifndef BUFFER_ITERATOR_H_
#define BUFFER_ITERATOR_H_

#include "Iterator.h"

template <class ElementType>
class BufferIterator : public Iterator<ElementType> {

public :
	bool hasNext()
	{
		return (position < size);
	}

	bool hasPrevious()
	{
		return (position > 0);
	}

	ElementType * current()
	{
		return (ElementType *)(memory + position * stepSize);
	}

	ElementType * next()
	{
		if(!hasNext())
			return NULL;

		position++;

		return current();
	}

	ElementType * previous()
	{
		if(!hasPrevious())
			return NULL;

		position--;

		return current();
	}

	BufferIterator(ElementType * memory, size_t size) : memory(memory), size(size), stepSize(sizeof(ElementType)), position(0)
	{

	}

	BufferIterator(void * memory, size_t size, size_t stepSize) : memory((uint8_t*)memory), size(size), stepSize(stepSize), position(0)
	{

	}

private:
	uint8_t * memory;
	size_t size;
	size_t stepSize;
	uintmax_t position;
};
#endif /* BUFFER_ITERATOR_H_ */
