/*
 * TestClass.h
 *
 *  Created on: 2009-06-28
 *      Author: malem303
 */

#ifndef TESTCLASS_H_
#define TESTCLASS_H_
#include "Utils/Utils.h"

class TestClass
{
public:
	TestClass(size_t element, const prog_mem * string) : element(element), string(string)
	{

	}

	TestClass(const TestClass & rhs) : element(rhs.element), string(rhs.string)
	{

	}

	TestClass() : element(-1), string(PROG_MEM_STRING("Default TestClass()"))
	{

	}

	const TestClass & operator =(const TestClass & rhs)
	{
		this->element = rhs.element;
		this->string = rhs.string;
		return *this;
	}

	bool operator ==(const TestClass & rhs)
	{
		if ((this->element == rhs.element) && (this->string == rhs.string))
			return true;

		return false;
	}

	bool operator !=(const TestClass & rhs)
	{
		return !this->operator ==(rhs);
	}


	size_t element;
	const prog_mem * string;
};

#endif /* TESTCLASS_H_ */
