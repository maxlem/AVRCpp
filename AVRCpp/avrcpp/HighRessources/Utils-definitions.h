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

char * strdup(const prog_mem * string, Allocator allocator)
{
	char * dup = new(allocator) char[strlen(string) + 1];

	return strcpy(dup, string);
}

char * strdup(const char * string, Allocator allocator)
{
	char * dup = new(allocator) char[strlen(string) + 1];

	return strcpy(dup, string);
}

char * strdupn(const char * string, size_t maxLenght, Allocator allocator)
{
	char * dup = new(allocator) char[strnlen(string, maxLenght) + 1];

	return strcpy(dup, string);
}

char * strdup(void * memoryToRealloc, const prog_mem * string)
{
	//TODO fix this workaround when realloc is repaired
	char * dup = new(memoryToRealloc) char[strlen(string) + 1];
//	delete memoryToRealloc;
//	char * dup = new char[strlen(string) + 1];
	return strcpy(dup, string);
}

template <typename UnsignedIntType>
UnsignedIntType strToUnsignedInt(const char * string)
{
	UnsignedIntType number = 0;

	size_t strLenght = strlen(string);

	for(size_t index = 0; index < strLenght; index++)
	{
		number += pow(10, index) * (string[strLenght - 1 - index] - '0');
//		fprintf(stderr, "10^%u * %u, char is %c number is %u \n\r", index, (string[strLenght - 1 - index] - '0'), string[strLenght - 1 - index], number);
	}

	return number;
}

template<typename ValueType, typename SumType>
SumType computeChecksum(ValueType * array, size_t size)
{
	return checksum(sum<ValueType, SumType>(array, size));
}

template<typename SumType>
SumType checksum(SumType sum)
{
	return ~sum + 1;
}

template<typename ValueType, typename SumType>
SumType sum(ValueType * array, size_t size)
{
	SumType overflowingSum = 0;
	for(size_t i = 0; i < size; i++)
		overflowingSum += array[i];

	return overflowingSum;
}

