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

#ifndef MockAccelerometer_H_
#define MockAccelerometer_H_

#include "Sensors/Sensor.h"

using Timers::Timestamp64;

class MockAccelerometer: public Sensor<uintmax_t>
{
public:
	MockAccelerometer(TimestampTimer<uintmax_t> * timer = Timestamp64::getInstance(1));
	virtual ~MockAccelerometer();

protected:

	float read(char label);
};

MockAccelerometer::MockAccelerometer(TimestampTimer<uintmax_t> * timer) : Sensor<uintmax_t>(timer)
{
	// TODO Auto-generated constructor stub
	Timers::Timestamp64::getInstance(1); // TODO : weird include bug fix/hack : Sensor.cpp : timer->read() undefined
}

MockAccelerometer::~MockAccelerometer()
{
	// TODO Auto-generated destructor stub
}


float MockAccelerometer::read(char label)
{
	switch(label)
	{
		case 'x' : return 0.10;
		case 'y' : return -0.10;
		case 'z' : return 1.0;
	}

	return 0.0;
}

#endif /* MockAccelerometer_H_ */
