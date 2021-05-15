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


#ifndef Logging_H_
#define Logging_H_

//#include "Utils.h"
#include "BitManipulation.h"

#ifdef MEMORY_LOGGING
	#define MEM_LOG_SIZE 100
#else
	#define MEM_LOG_SIZE 5
#endif

void OUT_OF_HEAP_MEMORY(size_t requested);
void OUT_OF_STACK_MEMORY(size_t requested);
void PRINT_MEMORY_STATUS();

void initLogging(void* mallocHeapStart);

size_t maxMemoryChunkLeft();

void * getHeapTop();

void updateHeapTop(size_t size, void* memory);

size_t heapSize();

void reallocLog(size_t size, void* memoryAsked, void* memoryObtained);

void mallocLog(size_t size, void* memory);

void freeLog(void* memory);

void printMemoryLog();

void verifyChecksum();

inline size_t stackSize() __attribute__((always_inline));

inline size_t distanceHeapFromStack() __attribute__((always_inline));

#include "Logging-definitions.h"

#endif /* Logging_H_ */
