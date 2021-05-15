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

#include "CppExtensions.h"
#include "BitManipulation.h"
#include "../Utils/Logging.h"

#include <alloca.h>
#include <stdlib.h>
int __cxa_guard_acquire(__guard *g)
{
	return !*(char *)(g);
}

void __cxa_guard_release (__guard *g)
{
	*(char *)g = 1;
}

void __cxa_guard_abort (__guard *)
{

}
void __cxa_pure_virtual(void)
{
}

void* operator new(size_t size)
{
	return newOp(size);
}

void* operator new(size_t size, void* memory)
{
	return reallocOp(size, memory);
}

void* operator new[](size_t size)
{
	return newOp(size);
}

void* operator new[](size_t size, void* memory)
{
	return reallocOp(size, memory);
}

void operator delete(void* memory)
{
	delOp(memory);
}

void operator delete[](void* memory)
{
	delOp(memory);
}


