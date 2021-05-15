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

#ifndef ENUM_H_
#define ENUM_H_
#include "Utils.h"





/*!
 * Enum base class, meant to reproduce Java's Enum type behaviour
 *
 */
template<class ValueType>
class Enum {
public:

/*!
 * Getter for this Enum's instance value
 * @return this Enum's instance value
 */
	ValueType getConstant() const{return constant;}

	bool operator==(const Enum<uint8_t>  & rhs)
	{
		return (this->constant == rhs.constant);
	}
protected:
	/*!
	 * Protected default constructor (to prevent usage)
	 */
	Enum(): constant(0){};

	/*!
	 * Protected constructor (to prevent usgae)
	 * @param constant this Enum's instance value
	 */
	Enum(ValueType constant) : constant(constant){}
private:
	ValueType constant;
};

typedef Enum<uint8_t> Enum8u;


class Prescaler : public Enum8u
{
public:

	uintmax_t toHertz() const
	{
		return clockSource / prescaler;
	}

	double toSeconds() const
	{
		return 1.0 / (double)(toHertz());
	}
protected:
	/*!
	 * @overload
	 */
	Prescaler(uint8_t constant, uintmax_t prescaler, uintmax_t clockSource = F_CPU) : Enum<uint8_t>(constant), prescaler(prescaler), clockSource(clockSource)
	{

	}
	uintmax_t prescaler;
	uintmax_t clockSource;
};


#endif /* ENUM_H_ */
