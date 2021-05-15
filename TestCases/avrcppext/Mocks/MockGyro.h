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

#ifndef MockGyro_H_
#define MockGyro_H_

#include "Sensors/Sensor.h"

using Timers::Timestamp64;

class MockGyro: public Sensor<uintmax_t>
{
public:
	MockGyro(TimestampTimer<uintmax_t> * timer = Timestamp64::getInstance(1));
	virtual ~MockGyro();

protected:

	float read(char label);
};

MockGyro::MockGyro(TimestampTimer<uintmax_t> * timer) : Sensor<uintmax_t>(timer)
{
	// TODO Auto-generated constructor stub
	Timers::Timestamp64::getInstance(1); // TODO : weird include bug fix/hack : Sensor.cpp : timer->read() undefined
}

MockGyro::~MockGyro()
{
	// TODO Auto-generated destructor stub
}


float MockGyro::read(char label)
{
	switch(label)
	{
		case 'a' : return 66.0;
		case 'b' : return -66.9;
		case 'c' : return 5.0;
	}

	return 0.0;
}

#endif /* MockGyro_H_ */
