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

#include <stdio.h>
#include <string.h>

template <typename ElementType>
Buffer<ElementType>::Buffer(size_t numberOfElements, bool allocateMemory) :
numberOfElements(numberOfElements), allocateMemory(allocateMemory)
{
	if(allocateMemory)
		buffer = new ElementType[numberOfElements];
}
template <typename ElementType>
Buffer<ElementType>::Buffer(size_t numberOfElements, const ElementType * memoryToCopy) :
numberOfElements(numberOfElements), allocateMemory(true)
{
	buffer = new ElementType[numberOfElements];

	memcpy(buffer, memoryToCopy, numberOfElements * sizeof(ElementType));

}

template <typename ElementType>
Buffer<ElementType>::Buffer(size_t numberOfElements, ElementType * memoryToShare) :
numberOfElements(numberOfElements), allocateMemory(false)
{
	buffer = memoryToShare;
}

template <typename ElementType>
Buffer<ElementType>::Buffer(const Buffer & rhs) : numberOfElements(rhs.numberOfElements), allocateMemory(allocateMemory)
{
	if(allocateMemory)
	{
		buffer = new ElementType[numberOfElements];
		memcpy(buffer, rhs.buffer, numberOfElements * sizeof(ElementType));
	}
	else
	{
		buffer = rhs.buffer;
	}
}

template <typename ElementType>
Buffer<ElementType>::~Buffer()
{
	if(allocateMemory)
		delete buffer;
}
