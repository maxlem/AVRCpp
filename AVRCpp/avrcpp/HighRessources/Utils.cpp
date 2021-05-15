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

#include "Utils.h"

#if __AVR_LIBC_VERSION__ < 10605UL
char * strdup(const char *s1)
{
    char *s2 = (char*)malloc(strlen(s1)+1);
    if (s2 != NULL)
    {
        strcpy(s2, s1);
    }
    return(s2);
}
#endif


int printf(const prog_mem * __fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	int i = vfprintf_P(stdout, (PGM_P) __fmt, ap);
	va_end(ap);
	return i;
}
int sprintf(char *__s, const prog_mem *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	int i = vsprintf_P(__s, (PGM_P) __fmt, ap);
	va_end(ap);
	return i;
}
int snprintf(char *__s, size_t __n, const prog_mem *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	int i = vsnprintf_P(__s, __n, (PGM_P) __fmt, ap);
	va_end(ap);
	return i;
}
int vsprintf(char *__s, const prog_mem *__fmt, va_list ap)
{
	return vsprintf_P(__s, (PGM_P) __fmt, ap);
}
int fprintf(FILE *__stream, const prog_mem *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	int i = vfprintf_P(__stream, (PGM_P) __fmt, ap);
	va_end(ap);
	return i;
}
int fputs(const prog_mem *__str, FILE *__stream)
{
	return fputs_P((PGM_P) __str, __stream);
}
int vfscanf(FILE *__stream, const prog_mem *__fmt, va_list __ap)
{
	return vfscanf_P(__stream, (PGM_P) __fmt, __ap);
}
int fscanf(FILE *__stream, const prog_mem *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	int i = vfscanf_P(__stream, (PGM_P) __fmt, ap);
	va_end(ap);
	return i;
}
int scanf(const prog_mem *__fmt, ...)
{
	va_list ap;
	va_start(ap, __fmt);
	int i = vfscanf_P(stdin, (PGM_P) __fmt, ap);
	va_end(ap);
	return i;
}
int sscanf(const char *__buf, const prog_mem *__fmt, ...)
{
	va_list ap;
	FILE f;
	int i;

	f.flags = __SRD | __SSTR | __SPGM;
	f.buf = (char *) __buf;
	va_start(ap, __fmt);
	i = vfscanf(&f, (PGM_P) __fmt, ap);
	va_end(ap);

	return i;
}
uintmax_t pow(size_t base, size_t exponent)
{
	uintmax_t result = base;

	if (exponent == 0)
		return 1;

	exponent--;

	while (exponent > 0)
	{
		result *= base;
		exponent--;
	}

	return result;
}

void copyWrappedAroundBuffer(char * & memory, size_t chunkSize, size_t frontIndex, size_t frontSize, size_t tailSize, size_t count)
{
    char * front = new(Allocators::STACK) char[frontSize * chunkSize];

    memcpy(front, &memory[frontIndex], frontSize * chunkSize);
    memmove(&memory[frontSize], memory, tailSize * chunkSize);
    memcpy(memory, front, frontSize * chunkSize);
}

intmax_t fromTwosCompletement(uintmax_t twosComplementValue, size_t signBitNumber)
{
	uintmax_t bitMask = bitValue(signBitNumber) - 1;

	intmax_t convertedValue = 0;

	if(twosComplementValue & bitValue(signBitNumber)) // then it is negative
		convertedValue = -((~twosComplementValue & bitMask) + 0x01);

	return convertedValue;
}
