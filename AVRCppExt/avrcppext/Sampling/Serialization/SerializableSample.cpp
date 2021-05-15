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

#include "SerializableSample.h"

SerializableSample::SerializableSample(char label, uint16_t sample) :
label(label), sample(sample), buffer(sizeof(label) + sizeof(sample) + sizeof(checksum), &label)
{
	// TODO Auto-generated constructor stub

}

SerializableSample::SerializableSample(const SerializableSample & rhs) :
label(rhs.label), sample(rhs.sample), buffer(sizeof(label) + sizeof(sample) + sizeof(checksum), &label)
{
}

SerializableSample::~SerializableSample()
{
	// TODO Auto-generated destructor stub
}

void SerializableSample::updateValues(char label, uint16_t sample)
{
	this->label = label;
	this->sample = sample;
}

Buffer<char> & SerializableSample::serialize()
{
	buffer.buffer = &label;

    checksum = computeChecksum<char,uint8_t>(buffer.buffer, buffer.numberOfElements - sizeof (checksum));

    return buffer;
}

size_t SerializableSample::serializedSize()
{
	return buffer.numberOfElements;
}
