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

#ifndef Result_H_
#define Result_H_

#include "regexp/regexp.h"
#include "DataStructures/List.h"

namespace RegularExpressions
{

struct Group
{
	Group(char * string, size_t lenght) : string(string), lenght(lenght)
	{

	}
	char * string;
	size_t lenght;
};

class Result
{
public:
	Result(const regexp * regexp);
	virtual ~Result();

	Group * getGroup(size_t number);

	size_t numberOfGroups();

protected:

	void toGroups(const regexp * regexp);

	List<Group> groups;
};

}
#endif /* Result_H_ */