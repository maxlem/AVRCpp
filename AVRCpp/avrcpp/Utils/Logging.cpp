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


#include "Logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "BitManipulation.h"
#include "Utils.h"
struct MemoryAllocOp
{
	union
	{
		size_t size;
		size_t allocHistoryIndex;
	};

	union
	{
		size_t mallocHistoryIndex; // SIZE_MAX for malloc()
		void* memoryFreed;
	};

	void* memoryObtained; // NULL for free()
};

void OUT_OF_HEAP_MEMORY(size_t requested)
{
	LOCK_INTERRUPTS;

	if(!isNull(stderr))
		fprintf(stderr, PROG_MEM_STRING("\n\rInsuficient heap memory, %d Bytes requested, but only %d Bytes left\n\r"), requested, maxMemoryChunkLeft());

	UNLOCK_INTERRUPTS;

}

void OUT_OF_STACK_MEMORY(size_t requested)
{
	LOCK_INTERRUPTS;

	if(!isNull(stderr))
		fprintf(stderr, PROG_MEM_STRING("\n\rInsuficient stack memory, %d Bytes requested, but only %d Bytes left\n\r"), requested, distanceHeapFromStack());

	UNLOCK_INTERRUPTS;
}

void PRINT_MEMORY_STATUS()
{
	LOCK_INTERRUPTS;

	if(!isNull(stderr))
		fprintf(stderr, PROG_MEM_STRING("Stack size : %u, Heap size : %u, margin : %u\n\r"), stackSize(), heapSize(), distanceHeapFromStack());

	UNLOCK_INTERRUPTS;
}


static void* heapTop = __malloc_heap_start;
static size_t heapCheckSum;
static MemoryAllocOp history[MEM_LOG_SIZE];
static size_t historyCount = 0;

size_t maxMemoryChunkLeft()
{

	size_t maxNewChunck = distanceHeapFromStack() - __malloc_margin;

	if(maxNewChunck > heapSize())
		return maxNewChunck;
	else
	{
		void* memory = NULL;

		size_t size = heapSize();

		while(isNull(memory))
		{
			memory = malloc(size);
			size--;
		}

		free(memory);
		return size;
	}
}


void * getHeapTop()
{
	return heapTop;
}
void updateHeapTop(size_t size, void* memory)
{
	if(isNull(memory))
		 OUT_OF_HEAP_MEMORY(size);
	else
	{
		char* endOfChunk = (char*)memory + size;
		if(endOfChunk > heapTop)
			heapTop = endOfChunk;
	}
}
size_t heapSize()
{
	return ((char*)heapTop - (char*)__malloc_heap_start);
}



size_t findIndexInHistory(void* memory)
{
	size_t historyIndexSearched = 0;

	while(history[historyIndexSearched].memoryObtained != memory)
	{
		if(historyIndexSearched > historyCount)
		{

			if(!isNull(stderr) && !interruptsEnabled())
				fprintf(stderr, PROG_MEM_STRING("// WARNING : couldn't find address %p in history!\n\r"), memory);

			historyIndexSearched = SIZE_MAX;
			break;
		}

		historyIndexSearched++;
	}

	return historyIndexSearched;
}


void reallocLog(size_t size, void* memoryAsked, void* memoryObtained)
{
	PRINT_MEMORY_STATUS();

	history[historyCount].size = size;
	history[historyCount].mallocHistoryIndex = findIndexInHistory(memoryAsked);
	history[historyCount].memoryObtained = memoryObtained;
	historyCount++;
	historyCount %= MEM_LOG_SIZE;
}

void mallocLog(size_t size, void* memory)
{
	PRINT_MEMORY_STATUS();

	history[historyCount].size = size;
	history[historyCount].mallocHistoryIndex = SIZE_MAX;
	history[historyCount].memoryObtained = memory;
	historyCount++;
	historyCount %= MEM_LOG_SIZE;

}


void freeLog(void* memory)
{
	PRINT_MEMORY_STATUS();

	if(isNull(memory))
		if(!isNull(stderr) && !interruptsEnabled())
			fprintf(stderr, PROG_MEM_STRING("WARNING : trying to free a NULL, index is %u\n\r"), historyCount);

	history[historyCount].allocHistoryIndex = findIndexInHistory(memory);
	history[historyCount].memoryFreed = memory;
	history[historyCount].memoryObtained = NULL;
	historyCount++;
	historyCount %= MEM_LOG_SIZE;
}



void printMemoryLog()
{

	for(size_t historyIndex = 0; historyIndex < historyCount; historyIndex++)
	{
		if(isNull(history[historyIndex].memoryObtained)) // then it's a delete() <<free()>> operation
		{
			if(!isNull(stderr) && !interruptsEnabled())
				fprintf(stderr, PROG_MEM_STRING("free(p%u);// adress is %p\n\r"), history[historyIndex].allocHistoryIndex, history[historyIndex].memoryFreed);
		}
		else if (history[historyIndex].mallocHistoryIndex == SIZE_MAX) // it's a new() <<malloc()>> operation
		{
			if(!isNull(stderr) && !interruptsEnabled())
				fprintf(stderr, PROG_MEM_STRING("void* p%u = malloc(%u);// adress is %p\n\r"), historyIndex, history[historyIndex].size, history[historyIndex].memoryObtained);

		}
		else //its a new(&)() <<realloc()>> operation
		{
			if(!isNull(stderr) && !interruptsEnabled())
				fprintf(stderr, PROG_MEM_STRING("void* p%u = realloc(p%u, %u);// asked to realloc at %p and was allocated at %p\n\r"), historyIndex, history[historyIndex].mallocHistoryIndex, history[historyIndex].size, history[history[historyIndex].mallocHistoryIndex].memoryObtained, history[historyIndex].memoryObtained);
		}
	}


}


void verifyChecksum()
{
	size_t checkSum = computeChecksum<size_t, size_t>((size_t*)__malloc_heap_start, heapSize());

	if(checkSum != heapCheckSum)
		if(!isNull(stderr) && !interruptsEnabled())
				fprintf(stderr, PROG_MEM_STRING("<<< checksums don't match >>>\n\r"));

}

