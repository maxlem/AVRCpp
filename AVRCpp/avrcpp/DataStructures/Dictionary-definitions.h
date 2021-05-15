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

#include <string.h>

template <class KeyType, class ElementType>
int Dictionary<KeyType, ElementType>::comparePairs(const void * lhs, const void * rhs)
{
	Pair<KeyType, ElementType> * lhsPair = (Pair<KeyType, ElementType> *)lhs;
	Pair<KeyType, ElementType> * rhsPair = (Pair<KeyType, ElementType> *)rhs;

	if(lhsPair->key < rhsPair->key)
		return -1;
	else if (lhsPair->key > rhsPair->key)
		return 1;

	return 0;
}

template <class KeyType, class ElementType>
Dictionary<KeyType, ElementType>::Dictionary(size_t capacity) : stepSize(sizeof(Pair<KeyType, ElementType>)), capacity(capacity), nextElementIndex(0)
{
	memory = new Pair<KeyType, ElementType>[capacity];
}

template <class KeyType, class ElementType>
Dictionary<KeyType, ElementType>::Dictionary(const Dictionary<KeyType, ElementType>  & copy) : stepSize(copy.stepSize)
{
	capacity = copy.capacity;
	nextElementIndex = copy.nextElementIndex;
	memory = new Pair<KeyType, ElementType>[capacity];
	memcpy((uint8_t*)memory, (const uint8_t*)copy.memory, capacity * stepSize);
}

template <class KeyType, class ElementType>
Dictionary<KeyType, ElementType> & Dictionary<KeyType, ElementType>::operator=(const Dictionary<KeyType, ElementType>  &  rhs)
{
	capacity = rhs.capacity;
	nextElementIndex = rhs.nextElementIndex;

	memory = new(memory) Pair<KeyType, ElementType>[capacity]; //realloc!

	memcpy((uint8_t*)memory, (const uint8_t*)rhs.memory, capacity * stepSize);

	return *this;
}
template <class KeyType, class ElementType>
Dictionary<KeyType, ElementType>::~Dictionary()
{
	delete memory;
}


template <class KeyType, class ElementType>
bool Dictionary<KeyType, ElementType>::insertElement(KeyType key, ElementType item)
{
	// veryfy the key is unique :

	if (isFull())
		return false;

	if(!isNull(bsearch(&key, memory, nextElementIndex, stepSize, comparePairs)))
		return false;

	memory[nextElementIndex].key = key;
	memory[nextElementIndex].item = item;
	nextElementIndex++;

	qsort(memory, nextElementIndex, stepSize, comparePairs);

	return true;
}

template <class KeyType, class ElementType>
bool Dictionary<KeyType, ElementType>::removeElement(KeyType key)
{
	// veryfy the key is unique :

	if (isEmpty())
		return false;

	uint8_t * foundElement = (uint8_t*)bsearch(&key, memory, nextElementIndex, stepSize, comparePairs);

	if(isNull(foundElement))
		return false;

	size_t foundElementIndex = (foundElement - (uint8_t*)memory) / stepSize;


	memmove(foundElement, foundElement + stepSize, (nextElementIndex - foundElementIndex - 1) * stepSize);

	nextElementIndex--;
	//elements are still sorted

	return true;
}

template <class KeyType, class ElementType>
ElementType * Dictionary<KeyType, ElementType>::find(KeyType key) const
{
	Pair<KeyType, ElementType> * search = (Pair<KeyType, ElementType> *)bsearch(&key, memory, nextElementIndex, stepSize, comparePairs);

	if(isNull(search))
		return NULL;

	return &search->item;
}

template <class KeyType, class ElementType>
bool Dictionary<KeyType, ElementType>::isFull() const
{
	return nextElementIndex == capacity;
}

template <class KeyType, class ElementType>
bool Dictionary<KeyType, ElementType>::isEmpty() const
{
	return nextElementIndex == 0;
}

template <class KeyType, class ElementType>
void Dictionary<KeyType, ElementType>::removeAllElements()
{
	nextElementIndex = 0;
}

template <class KeyType, class ElementType>
size_t Dictionary<KeyType, ElementType>::numberOfElements() const
{
	return nextElementIndex;
}

template <class KeyType, class ElementType>
typename Dictionary<KeyType, ElementType>::KeyIterator Dictionary<KeyType, ElementType>::keys() const
{
	return KeyIterator(memory, nextElementIndex, stepSize);
}

template <class KeyType, class ElementType>
typename Dictionary<KeyType, ElementType>::ElementIterator Dictionary<KeyType, ElementType>::elements() const
{
	return ElementIterator( (uint8_t*)memory + (size_t)sizeof(KeyType), nextElementIndex, stepSize);
}
