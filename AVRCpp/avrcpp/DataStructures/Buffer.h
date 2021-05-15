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

#ifndef Buffer_H_
#define Buffer_H_


#include <stdio.h>
#include <string.h>

template <typename ElementType>
struct Buffer
{
	Buffer(size_t numberOfElements = 0, bool allocateMemory = true);

	Buffer(size_t numberOfElements, const ElementType * memoryToCopy);

	Buffer(size_t numberOfElements, ElementType * memoryToShare);

	Buffer(const Buffer & rhs);

	virtual ~Buffer();

	size_t numberOfElements;
	ElementType * buffer;
	bool allocateMemory;
};

#include "Buffer-definitions.h"

#endif /* Buffer_H_ */
