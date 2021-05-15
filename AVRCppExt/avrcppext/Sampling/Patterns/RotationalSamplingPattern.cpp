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

#include "RotationalSamplingPattern.h"


#include <string.h>

RotationalSamplingPattern::RotationalSamplingPattern(const char * name, const prog_mem * pattern, size_t repetitions) :
SamplingPattern(name, strlen(pattern), repetitions), patternIndex(0)
{
	this->pattern = strdup(pattern);
}

RotationalSamplingPattern::RotationalSamplingPattern(const char * name, const char * pattern, size_t repetitions) :
SamplingPattern(name, strlen(pattern), repetitions), patternIndex(0)
{
	this->pattern = strdup(pattern);
}

RotationalSamplingPattern::RotationalSamplingPattern(const char * name, uint8_t numberOfLabel, size_t repetitions) :
SamplingPattern(name, numberOfLabel, repetitions), patternIndex(0)
{
	this->pattern = new char[size];
	for (uint8_t i = 0; i < size; i++)
		pattern[i] = 'a' + i;
}


RotationalSamplingPattern::~RotationalSamplingPattern()
{
	delete pattern;
}

char RotationalSamplingPattern::nextLabel()
{
	patternIndex = (patternIndex + 1);

	if (patternIndex >= this->size)
	{
		this->repetitionsLeft--;

		if (this->repetitionsLeft == 0)
			this->exhausted = true;

		patternIndex %= size;
	}

	return pattern[patternIndex];
}

char RotationalSamplingPattern::currentLabel() const
{
	return pattern[patternIndex];
}

void RotationalSamplingPattern::reset()
{
	patternIndex = 0;
	this->repetitionsLeft = this->repetitions;
	this->exhausted = false;
}
