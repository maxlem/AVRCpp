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

#ifndef QUEUE_H_
#define QUEUE_H_
#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "../Utils/Utils.h"
#include "Buffer.h"

/*! Queue datastructure.
 * A fixed sized, array-based queue
 */

template<class ElementType>
class Queue
{

public:
	/*! Constructor
	 * @param capacity the number of elements the \a Queue can contain
	 * @remarks the Queue can only hold \a capacity elements
	 */
	Queue(size_t capacity, ElementType errorSentinel = ElementType());
	
	Queue(Queue<ElementType> &);

	virtual ~Queue();


	void resize(size_t newCapacity);

	const ElementType * inspect();

	/*!
	 * Enqueue an element
	 * @param element the element to enqueue
	 * @return false if the Queue is full
	 */
	bool enQueue(ElementType & element);
	
	/*!
	 * Dequeue an element
	 * @return the element
	 */
	ElementType & deQueue();
	
	/*!
	 *
	 * @return true if the Queue is full
	 */
	inline bool isFull() const __attribute__((always_inline));
	
	/*!
	 *
	 * @return true if the Queue is empty
	 */
	inline bool isEmpty() const __attribute__((always_inline));
	


	/*!
	 *
	 * @return the number of element contained in the Queue
	 */
	inline size_t numberOfElements() const __attribute__((always_inline));
	
	/*!
	 *
	 * @return the capacity of the Queue
	 */
	inline size_t capacity() const __attribute__((always_inline));


	/*!
	 * Reinitialize the Queue
	 */
	void init();
	
	void clearMemory();

	ElementType & front() const;

	ElementType & tail() const;

	ElementType & operator [] (size_t index) const;

	Queue<ElementType> & operator <<(ElementType & rhs);

	Queue<ElementType> & operator <<(const Buffer<ElementType> & rhs);

	Queue<ElementType> & operator <<(Queue<ElementType> & rhs);

protected:

	ElementType * errorSentinel;

	ElementType * memory;
	size_t size;
	size_t frontIndex;
	size_t tailIndex;
	size_t count;
};



#include "Queue-definitions.h"


#endif /*QUEUE_H_*/
