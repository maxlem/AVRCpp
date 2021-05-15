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

#ifndef LINKEDLIST_ITERATOR_H_
#define LINKEDLIST_ITERATOR_H_

#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "Iterator.h"
#include "Node.h"

template <class ElementType>
class LinkedListIterator : public Iterator<ElementType> {

public :
	bool hasNext()
	{
		return !isNull(currentNode->next);
	}

	bool hasPrevious()
	{
		return !isNull(currentNode->previous);
	}

	ElementType * current()
	{
		if(isNull(currentNode))
			return NULL;
		return &(currentNode->el);
	}

	ElementType * next()
	{
		if(!isNull(currentNode))
			currentNode = currentNode->next;

		return current();
	}

	ElementType * previous()
	{
		if(!isNull(currentNode))
			currentNode = currentNode->previous;

		return current();
	}

	LinkedListIterator(Node<ElementType> * begin) : currentNode(begin)
	{

	}

private: //TODO put back private

	Node<ElementType> * currentNode;
};
#endif /* LINKEDLIST_ITERATOR_H_ */
