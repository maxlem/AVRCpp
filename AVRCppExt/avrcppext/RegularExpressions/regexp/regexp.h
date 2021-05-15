/*
 * Definitions etc. for regexp(3) routines.
 *
 * Caveat:  this is V8 regexp(3) [actually, a reimplementation thereof],
 * not the System V one.
 */

#ifndef regexp_H_
#define regexp_H_

#include "Utils/Utils.h"


#define NSUBEXP  10

struct regexp
{
	char *startp[NSUBEXP];
	char *endp[NSUBEXP];
	char regstart;		/* Internal use only. */
	char reganch;		/* Internal use only. */
	char *regmust;		/* Internal use only. */
	int regmlen;		/* Internal use only. */
	char program[1];	/* Unwarranted chumminess with compiler. */
};

regexp *regcomp(const char *re);

regexp *regcomp(const prog_mem * re);

int regexec(regexp *rp, const char *s);

int regexec(regexp *rp, const prog_mem *s);

void regsub(const regexp *rp, const char *src, char *dst);

void regerror(char *message);

#endif /*regexp_H_*/
