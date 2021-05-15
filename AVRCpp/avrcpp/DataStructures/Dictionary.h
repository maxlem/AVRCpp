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

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "../Utils/CppExtensions.h"
#include "BufferIterator.h"
#include <stdlib.h>

#define DICTIONARY_DEFAULT_SIZE 10
template <class KeyType, class ElementType>
struct Pair
{
	KeyType key;
	ElementType item;
};


template <class KeyType, class ElementType>
class Dictionary {

public :

	typedef BufferIterator<KeyType> KeyIterator;
	typedef BufferIterator<ElementType> ElementIterator;

	static int comparePairs(const void * lhs, const void * rhs);

	Dictionary(size_t capacity = DICTIONARY_DEFAULT_SIZE);

	Dictionary(const Dictionary<KeyType, ElementType>  & copy);

	Dictionary<KeyType, ElementType> & operator=(const Dictionary<KeyType, ElementType>  &  rhs);

	virtual ~Dictionary();


	bool insertElement(KeyType key, ElementType item);

	bool removeElement(KeyType key);

	ElementType * find(KeyType key) const;

	KeyIterator keys() const;

	ElementIterator elements() const;

	bool isFull() const;

	bool isEmpty() const;

	void removeAllElements();

	size_t numberOfElements() const;

private:
	const size_t stepSize;
	size_t capacity;
	Pair<KeyType, ElementType> * memory;
	size_t nextElementIndex;


};

#include "Dictionary-definitions.h"
#endif /* DICTIONARY_H_ */
