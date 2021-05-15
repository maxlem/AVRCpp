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

#include "../Utils/BitManipulation.h"

#include <string.h>


template<class ElementType>
Queue<ElementType>::Queue(size_t capacity, ElementType errorSentinel) :
size(capacity)
{
	this->errorSentinel = new ElementType(errorSentinel);
	memory = new ElementType[size];

	init();
}

template<class ElementType>
Queue<ElementType>::Queue(Queue<ElementType> & rhs)
{
	LOCK_INTERRUPTS;

	this->errorSentinel = new ElementType(*rhs.errorSentinel);

	memory = new ElementType[rhs.size];

	memcpy(memory, rhs.memory, rhs.size * sizeof(ElementType));

	size = rhs.size;
	frontIndex = rhs.frontIndex;
	tailIndex = rhs.tailIndex;
	count = rhs.count;

	UNLOCK_INTERRUPTS;

}

template<class ElementType>
Queue<ElementType>::~Queue()
{
	delete memory;
	delete errorSentinel;
}




template<class ElementType>
void Queue<ElementType>::resize(size_t newCapacity)
{
	LOCK_INTERRUPTS;

	size_t frontSize = size - frontIndex;
	size_t tailSize = tailIndex;

	if(newCapacity == size)
	{
		return;
	}
	else if(newCapacity > size)
	{
		ElementType * newMemory = new(memory) ElementType[newCapacity];

		if(tailIndex < frontIndex || isFull()) // the buffer wrapped around
		{
			if(newMemory != memory)
			{
				memcpy(newMemory, &memory[frontIndex], frontSize * sizeof(ElementType));

				memcpy(&newMemory[frontSize], memory, tailSize * sizeof(ElementType));
			}
			else
				copyWrappedAroundBuffer((char * &) memory, sizeof(ElementType), frontIndex, frontSize, tailSize, count);


		}
		else
		{
			if (newMemory != memory)
				memcpy(newMemory, &memory[frontIndex], count * sizeof(ElementType));
			else
				memmove(memory, &memory[frontIndex], count * sizeof(ElementType));
		}

		memory = newMemory;

	}
	else if (newCapacity < size)
	{
		if(newCapacity < count)  // we keep the oldest elements
		{
			size_t elementsToDiscard = count - newCapacity;

			count = newCapacity;

			if(tailIndex < frontIndex || isFull()) // the buffer wrapped around
			{

				if(tailIndex > elementsToDiscard)
				{
					tailSize -= elementsToDiscard;

					copyWrappedAroundBuffer((char * &) memory, sizeof(ElementType), frontIndex, frontSize, tailSize, count);

				}
				else
					memmove(memory, &memory[frontIndex], count * sizeof(ElementType));

			}
			else
				memmove(memory, &memory[frontIndex], count * sizeof(ElementType));

		}
		else
		{
			if(tailIndex < frontIndex || isFull()) // the buffer wrapped around
				copyWrappedAroundBuffer((char * &) memory, sizeof(ElementType), frontIndex, frontSize, tailSize, count);
			else
				memmove(memory, &memory[frontIndex], count * sizeof(ElementType));

		}

	}

	frontIndex = 0;
	tailIndex = count;
	size = newCapacity;

	UNLOCK_INTERRUPTS;
}
template<class ElementType>
const ElementType * Queue<ElementType>::inspect()
{
	size_t frontSize = size - frontIndex;
	size_t tailSize = tailIndex;

	if(tailIndex < frontIndex)
		copyWrappedAroundBuffer((char * &) memory, sizeof(ElementType), frontIndex, frontSize, tailSize, count);

	return memory;
}


template<class ElementType>
bool Queue<ElementType>::enQueue(ElementType & element)
{
	bool success;

	LOCK_INTERRUPTS;

	if (isFull())
		success = false;
	else
	{

		memory[tailIndex] = element;

		tailIndex = (tailIndex + 1) % size;

		count++;

		success = true;
	}

	UNLOCK_INTERRUPTS;

	return success;
}

template<class ElementType>
ElementType & Queue<ElementType>::deQueue()
{
	ElementType * element;

	LOCK_INTERRUPTS;

	if (isEmpty())
		element = errorSentinel;
	else
	{
		element = &memory[frontIndex];

		frontIndex = (frontIndex + 1) % size;
		count--;
	}

	UNLOCK_INTERRUPTS;

	return *element;
}

template<class ElementType>
bool Queue<ElementType>::isFull() const
{
	bool isFullCopy;

	LOCK_INTERRUPTS;

	isFullCopy = (count == size);

	UNLOCK_INTERRUPTS;

	return isFullCopy;
}

template<class ElementType>
bool Queue<ElementType>::isEmpty() const
{
	bool isEmptyCopy;

	LOCK_INTERRUPTS;

	isEmptyCopy = (count == 0);

	UNLOCK_INTERRUPTS;

	return isEmptyCopy;
}



template<class ElementType>
size_t Queue<ElementType>::numberOfElements() const
{
	size_t countCopy;

	LOCK_INTERRUPTS;

	countCopy = count;

	UNLOCK_INTERRUPTS;

	return countCopy;
}

template<class ElementType>
size_t Queue<ElementType>::capacity() const
{
	size_t sizeCopy;

	LOCK_INTERRUPTS;

	sizeCopy = size;

	UNLOCK_INTERRUPTS;

	return sizeCopy;
}


template<class ElementType>
void Queue<ElementType>::init()
{
	LOCK_INTERRUPTS;

	frontIndex = 0;
	tailIndex = 0;
	count = 0;

	UNLOCK_INTERRUPTS;

}


template<class ElementType>
void Queue<ElementType>::clearMemory()
{
	LOCK_INTERRUPTS;

	for(size_t index = 0; index < size; index++)
		memory[index] = (ElementType)0;

	UNLOCK_INTERRUPTS;
}

template<class ElementType>
ElementType & Queue<ElementType>::front() const
{
	ElementType * el;

	LOCK_INTERRUPTS;

	if(isEmpty())
		el = errorSentinel;
	else
		el = &memory[frontIndex];

	UNLOCK_INTERRUPTS;

	return *el;
}

template<class ElementType>
ElementType & Queue<ElementType>::tail() const
{
	ElementType * el;

	LOCK_INTERRUPTS;

	if(isEmpty())
		el = errorSentinel;
	else if(tailIndex > 0)
		el = &memory[tailIndex - 1];
	else
		el = &memory[size-1];

	UNLOCK_INTERRUPTS;

	return *el;
}

template<class ElementType>
ElementType & Queue<ElementType>::operator [] (size_t index) const
{
	ElementType * el;

	LOCK_INTERRUPTS;

	if(index >= numberOfElements())
		el = errorSentinel;
	else
		el = &memory[(frontIndex + index) % size];

	UNLOCK_INTERRUPTS;

	return *el;
}

template<class ElementType>
Queue<ElementType> & Queue<ElementType>::operator <<(ElementType & rhs)
{
	this->enQueue(rhs);

	return *this;
}

template<class ElementType>
Queue<ElementType> & Queue<ElementType>::operator <<(const Buffer<ElementType> & rhs)
{
	for(size_t index = 0; index < rhs.numberOfElements; index++)
		this->enQueue(rhs.buffer[index]);

	return *this;
}

template<class ElementType>
Queue<ElementType> & Queue<ElementType>::operator <<(Queue<ElementType> & rhs)
{
	for(size_t index = 0; index < rhs.numberOfElements(); index++)
		this->enQueue(rhs[index]);

	return *this;

}
