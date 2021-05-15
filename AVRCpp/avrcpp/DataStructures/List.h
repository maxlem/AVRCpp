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

#ifndef LIST_H_
#define LIST_H_

#include "../Utils/CppExtensions.h"
#include "Node.h"
#include "LinkedListIterator.h"


template <typename ElementType>
class List {
public:

	typedef LinkedListIterator<ElementType> ListIterator;

	List();

	List(const List& rhs);

	virtual ~List();

	bool append(const ElementType & element);

	bool insertElement(const ElementType & element, size_t position);

	bool remove(const ElementType & element);

	bool remove(size_t position);

	size_t numberOfElements() const;

	bool isEmpty() const;

	ElementType * element(size_t position) const;

	size_t position(const ElementType & element) const;

	List<ElementType>& operator = (const List<ElementType>& rhs);

	ListIterator elements() const;

private:
	typedef Node<ElementType> ListNode;

	Node<ElementType> * nodeAt(size_t position) const;

	void removeAllNodes();

	ListNode * begin;

	size_t size;
};

#include "List-definitions.h"



#endif
