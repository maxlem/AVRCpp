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

#define SIZE_MAX 0xFFFFul // TODO find out why SIZE_MAX from <stdint.h> isn't declared here

template <typename ElementType>
List<ElementType>::List() : begin(NULL), size(0)
{

}

template <typename ElementType>
List<ElementType>::List(const List<ElementType>& rhs) : begin(NULL), size(0)
{
	this->operator =(rhs);
}

template <typename ElementType>
List<ElementType>::~List()
{
	removeAllNodes();
}

template <typename ElementType>
List<ElementType>& List<ElementType>::operator = (const List<ElementType>& rhs)
{
	removeAllNodes();

	size = rhs.size;

	if (isNull(rhs.begin))
		begin = NULL;
	else
	{
		begin = new ListNode(rhs.begin->el);

		ListNode * newNode = begin;
		for (ListNode * temp = rhs.begin->next; !isNull(temp); temp = temp->next )
		{
			newNode->next = new ListNode(temp->el);
			newNode = newNode->next;
			newNode->next = NULL;
		}
		newNode->next = NULL;

	}
	return (*this);
}


template <typename ElementType>
size_t List<ElementType>::numberOfElements() const
{
	return size;
}



template <typename ElementType>
ElementType * List<ElementType>::element(size_t position) const
{
	ListNode * nodeSearched = nodeAt(position);

	if(isNull(nodeSearched))
		return NULL;

	return &(nodeSearched->el);
}


template <typename ElementType>
size_t List<ElementType>::position(const ElementType & element) const
{
	ListNode * nodeSearched = begin;
	size_t positionSearched(0);

	while (!isNull(nodeSearched) && nodeSearched->el != element )
	{
		nodeSearched = nodeSearched->next;
		positionSearched++;
	}

	if (isNull(nodeSearched))
		return -1;

	return positionSearched;
}

template <typename ElementType>
bool List<ElementType>::isEmpty() const
{
	return isNull(begin);
}
template <typename ElementType>
bool List<ElementType>::append(const ElementType & element)
{
	return insertElement(element, numberOfElements());

}

template <typename ElementType>
bool List<ElementType>::insertElement(const ElementType & element, size_t position)
{
	ListNode *  newNode;

	if(position > numberOfElements())
		return false;


	newNode = new ListNode(element);

	if(position == 0)
	{
		newNode->changeNext(begin);
		begin = newNode;
	}
	else
	{
		ListNode *  previousNode = nodeAt(position - 1);

		if(isNull(previousNode))
			return false;

		previousNode->changeNext(newNode);
	}

	size++;
	return true;
}


template <typename ElementType>
bool List<ElementType>::remove(const ElementType & element)
{
	size_t pos = position(element);

	if(pos == SIZE_MAX)
		return false;

	return remove(pos);
}

template <typename ElementType>
bool List<ElementType>::remove(size_t position)
{
	ListNode * nodeSearched;

	if(position > numberOfElements())
		return false;

	if(position == 0)
	{
		nodeSearched = begin;
		if(isNull(nodeSearched))
			return false;
		begin = begin->next;

	}
	else
	{
		ListNode *  nodeSearched = nodeAt(position);

		if(isNull(nodeSearched))
			return false;
	}

	nodeSearched->unlink();
	delete nodeSearched;

	size--;
	return true;
}

template <typename ElementType>
typename List<ElementType>::ListIterator List<ElementType>::elements() const
{
	return ListIterator(begin);
}

template <typename ElementType>
Node<ElementType> * List<ElementType>::nodeAt(size_t position) const
{
	ListNode *  nodeSearched = begin;
	for (size_t previousNodePosition = 0; !isNull(nodeSearched) && previousNodePosition != position; previousNodePosition++)
		nodeSearched = nodeSearched->next;

	return nodeSearched;
}

template <typename ElementType>
void List<ElementType>::removeAllNodes()
{
	ListNode * current = begin;
	while(!isNull(current))
	{
		begin = begin->next;
		delete current;
		current = begin;
	}
	size = 0;
}
