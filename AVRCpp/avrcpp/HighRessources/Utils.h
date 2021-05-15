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

#ifndef Utils_H_
#define Utils_H_

#include "CppExtensions.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <avr/version.h>


class prog_mem{};

#if __AVR_LIBC_VERSION__ < 10605UL
char * strdup(const char *s1);
#endif

inline const prog_mem * memchr(const prog_mem * p1, int __val, size_t __len){return (const prog_mem*)memchr_P((PGM_VOID_P)p1, __val, __len);}
inline int memcmp(const void *p1, const prog_mem *p2, size_t p3) {return memcmp_P(p1, (PGM_VOID_P)p2, p3);}
inline void *memcpy(void *p1, const prog_mem *p2, size_t __len){return memcpy_P(p1, (PGM_VOID_P)p2, __len);}
inline void *memmem(const void *p1, size_t __len1, const prog_mem *p2, size_t __len2){return memmem_P(p1, __len1, (PGM_VOID_P)p2, __len2);}
inline const prog_mem * memrchr(const prog_mem *p1, int __val, size_t __len){return (const prog_mem*)memrchr_P((PGM_VOID_P)p1, __val, __len);}
inline char *strcat(char *p1, const prog_mem *p2){return strcat_P(p1, (PGM_P)p2);}
inline const prog_mem * strchr(const prog_mem *p1, int __val){return (const prog_mem*)strchr_P((PGM_P)p1, __val);}
inline const prog_mem * strchrnul(const prog_mem *p1, int __val){return (const prog_mem*)strchrnul_P((PGM_P)p1, __val);}
inline int strcmp(const char *p1, const prog_mem *p2){return strcmp_P(p1, (PGM_P)p2);}
inline char *strcpy(char *p1, const prog_mem *p2){return strcpy_P(p1, (PGM_P)p2);}
inline int strcasecmp(const char *p1, const prog_mem *p2){return strcasecmp_P(p1, (PGM_P)p2);}
inline char *strcasestr(const char *p1, const prog_mem *p2){return strcasestr_P(p1, (PGM_P)p2);}
inline size_t strcspn(const char *__s, const prog_mem * __reject){return strcspn_P(__s,  (PGM_P)__reject);}
inline size_t strlcat (char *p1, const prog_mem *p2, size_t __len){return strlcat_P(p1, (PGM_P)p2, __len);}
inline size_t strlcpy (char *p1, const prog_mem *p2, size_t __len){return strlcpy_P(p1, (PGM_P)p2, __len);}
inline size_t strlen(const prog_mem *p1){return strlen_P((PGM_P)p1);}
inline size_t strnlen(const prog_mem *p1, size_t __len){return strnlen_P((PGM_P)p1, __len);}
inline int strncmp(const char *p1, const prog_mem *p2, size_t __len){return strncmp_P(p1, (PGM_P)p2, __len);}
inline int strncasecmp(const char *p1, const prog_mem *p2, size_t __len) {return strncasecmp_P(p1, (PGM_P)p2, __len);}
inline char *strncat(char *p1, const prog_mem *p2, size_t __len){return strncat_P(p1, (PGM_P)p2, __len);}
inline char *strncpy(char *p1, const prog_mem *p2, size_t __len){return strncpy_P(p1, (PGM_P)p2, __len);}
inline char *strpbrk(const char *__s, const prog_mem * __accept){return strpbrk_P(__s, (PGM_P) __accept);}
inline const prog_mem * strrchr(const prog_mem *p1, int __val){return (const prog_mem*)strrchr_P((PGM_P)p1, __val);}
inline char *strsep(char **__sp, const prog_mem * __delim){return strsep_P(__sp, (PGM_P)__delim);}
inline size_t strspn(const char *__s, const prog_mem * __accept) {return strspn_P(__s, (PGM_P)__accept);}
inline char *strstr(const char *p1, const prog_mem *p2){ return strstr_P(p1, (PGM_P)p2);}

int	printf(const prog_mem * __fmt, ...);
int	sprintf(char *__s, const prog_mem *__fmt, ...);
int	snprintf(char *__s, size_t __n, const prog_mem *__fmt, ...);
int	vsprintf(char *__s, const prog_mem *__fmt, va_list ap);
int	fprintf(FILE *__stream, const prog_mem *__fmt, ...);
int	fputs(const prog_mem *__str, FILE *__stream);
int	vfscanf(FILE *__stream, const prog_mem *__fmt, va_list __ap);
int	fscanf(FILE *__stream, const prog_mem *__fmt, ...);
int	scanf(const prog_mem *__fmt, ...);
int	sscanf(const char *__buf, const prog_mem *__fmt, ...);

#define PROG_MEM_STRING(s) (prog_mem*) PSTR(s)


static const char PROGRESS_CHARS[] = "\\|/-";

#define PROGRESS_CHARS_COUNT 4

/*! Simple power function, accepts positive integers only
 * @param base the base of the expression
 * @param exponent the \a base will be multiplyed by itsef \a exponent times
 * @return the sum, trucated to 16 bits
 */
uintmax_t pow(size_t base, size_t exponent);

void copyWrappedAroundBuffer(char * & memory, size_t chunkSize, size_t frontIndex, size_t frontSize, size_t tailSize, size_t count);

using Allocators::Allocator;

/*!
 * Duplicates a program string
 * @param string the string to duplicate
 * @param allocator the allocator
 * @return the duplicated string
 * @see \a Allocator
 */

inline char * strdup(const prog_mem * string, Allocator allocator = Allocators::MALLOC) __attribute__((always_inline)); //if is not inlined, alloca (of course) can't work



/*!
 * Duplicates a string
 * @param string the string to duplicate
 * @param allocator the allocator
 * @return the duplicated string
 * @see \a Allocator
 */
inline char * strdup(const char * string, Allocator allocator) __attribute__((always_inline)); //if is not inlined, alloca (of course) can't work

inline char * strdupn(const char * string, size_t maxLenght, Allocator allocator = Allocators::MALLOC) __attribute__((always_inline)); //if is not inlined, alloca (of course) can't work

inline char * strdup(void * memoryToRealloc, const prog_mem * string) __attribute__((always_inline));

template <typename UnsignedIntType>
UnsignedIntType strToUnsignedInt(const char * string);

/*!
 * Classic computeChecksum function
 * @param array the array of bytes
 * @param size the size of the array
 * @return the sum of the bytes, if it is under \f$ maxSum = 2^{8*sizeof\left(\mathbf{SumType}\right)} \f$,
 * \f$ sum%maxSum\f$ otherwise (i.e. carry out to 0)
 */
template<typename ValueType, typename SumType>
inline SumType computeChecksum(ValueType * array, size_t size) FORCE_INLINE;

template<typename SumType>
inline SumType checksum(SumType sum) FORCE_INLINE;

template<typename ValueType, typename SumType>
inline SumType sum(ValueType * array, size_t size) FORCE_INLINE;

intmax_t fromTwosCompletement(uintmax_t twosComplementValue, size_t signBitNumber);

#define STRINGNIFY(toString) #toString

#define STRINGNIFY_P(to_prog_mem_string) PROG_MEM_STRING(#to_prog_mem_string)

#define setupParseValue(sentinelChar)\
	size_t value_MACRO = 0;\
	const prog_mem * enumString_P_MACRO;\
	char * enumString_MACRO = NULL;\
	char sentinel_MACRO = sentinelChar

#define parseValue(enumToStringnify, size_t_varaiable) \
	enumString_P_MACRO = (const prog_mem *)strrchr(PROG_MEM_STRING(#enumToStringnify), sentinel_MACRO) + 1;\
	enumString_MACRO = strdup(enumString_P_MACRO, Allocators::STACK);\
	sscanf(enumString_MACRO, PROG_MEM_STRING("%u"), &size_t_varaiable)

#define parseEnumValue(enumToStringnify) parseValue(enumToStringnify, value_MACRO)

#define beginEnumSwitchCase(enumVariable, sentinelChar)\
	setupParseValue(sentinelChar);\
	switch(enumVariable)\
{

#define endEnumSwitchCase(defaultValue)\
	default : value_MACRO = defaultValue;\
}\
	return value_MACRO

#define buildCaseEnumValue(enumToStringnify)\
		case enumToStringnify : 	parseEnumValue(enumToStringnify);\
									break



#include "Utils-definitions.h"

#endif /*Utils_H_*/
