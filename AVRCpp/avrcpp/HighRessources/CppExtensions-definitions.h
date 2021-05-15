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


#include "../Utils/Logging.h"


#include <stdlib.h>
#include <alloca.h>

inline void* stackNewOp(size_t size)  __attribute__((always_inline));

void* stackNewOp(size_t size)
{
	LOCK_INTERRUPTS;

	if(distanceHeapFromStack() < size)
	{
		OUT_OF_STACK_MEMORY(size);
		return NULL;
	}

	void * memory = alloca(size);

	UNLOCK_INTERRUPTS;

	return memory;
}

inline void * newOp(size_t size)
{

	LOCK_INTERRUPTS;

	void* memory = malloc(size);

	updateHeapTop(size, memory);

#ifdef MEMORY_LOGGING
	mallocLog(size, memory);
#endif

	UNLOCK_INTERRUPTS;

	return memory;
}

inline void * callocOp(size_t size)
{

	LOCK_INTERRUPTS;

	void* memory = calloc(1, size);

	updateHeapTop(size, memory);

#ifdef MEMORY_LOGGING
	mallocLog(size, memory);
#endif

	UNLOCK_INTERRUPTS;

	return memory;
}

inline void* reallocOp(size_t size, void* memory)
{


	LOCK_INTERRUPTS;

	void* reallocatedMemory;

	if( __malloc_heap_start < (char*)memory && (char*)memory < getHeapTop())
		reallocatedMemory = realloc(memory, size);
	else
		reallocatedMemory = malloc(size);

	updateHeapTop(size, memory);

#ifdef MEMORY_LOGGING
	reallocLog(size, memory, reallocatedMemory);
#endif

	UNLOCK_INTERRUPTS;

	return reallocatedMemory;
}

inline void delOp(void* memory)
{

	LOCK_INTERRUPTS;

#ifdef MEMORY_LOGGING
	freeLog(memory);
#endif

	free(memory);

	UNLOCK_INTERRUPTS;
}

inline void * allocateOp(size_t size, Allocator allocator) __attribute__((always_inline));

void * allocateOp(size_t size, Allocator allocator)
{
	using namespace Allocators;

	switch(allocator)
	{
		case MALLOC:	return newOp(size);

		case CALLOC:	return callocOp(size);

		case STACK:		return stackNewOp(size);

		default :		return NULL;
	}
}

void* operator new(size_t size, Allocator allocator)
{
	return allocateOp(size, allocator);
}

void* operator new[](size_t size, Allocator allocator)
{
	return allocateOp(size, allocator);
}
