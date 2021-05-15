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

template <typename ElementType>
Node<ElementType>::Node (const ElementType& el, Node<ElementType>  * next, Node<ElementType>  * previous) :
next(next), previous(previous), el(el)
{
}

template <typename ElementType>
void Node<ElementType>::changeNext(Node<ElementType> * newNext)
{
	if(isNull(newNext))
	{
		this->next = NULL;
	}
	else
	{
		newNext->next = this->next;
		if(!isNull(newNext->next))
			newNext->next->previous = newNext;
		this->next = newNext;
		newNext->previous = this;
	}

}

template <typename ElementType>
void Node<ElementType>::changePrevious(Node<ElementType> * newPrevious)
{
	if(isNull(newPrevious))
	{
		this->previous = NULL;
	}
	else
	{
		newPrevious->previous = this->previous;
		if(!isNull(newPrevious->previous))
			newPrevious->previous->next = newPrevious;

		this->previous = newPrevious;
		newPrevious->next = this;
	}
}

template <typename ElementType>
void Node<ElementType>::unlink()
{
	if(!isNull(this->previous))
		this->previous->next = this->next;
	if(!isNull(this->next))
		this->next->previous = this->previous;

}
