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

#ifndef DICTIONARYTEST_H_
#define DICTIONARYTEST_H_


#include "DataStructures/Dictionary.h"
#include "TestCase.h"
#define DICTIONARYTEST_SIZE 10

class DictionaryTest :  public TestCase<DictionaryTest>
{

	Dictionary<char, float> * dict;

public:


	DictionaryTest(const prog_mem * testMethodName_P, TestCase<DictionaryTest>::TestMethod testMethod) :
	TestCase<DictionaryTest>(testMethodName_P, testMethod)
	{

	}

	void setUp()
	{
		dict = new Dictionary<char, float>(DICTIONARYTEST_SIZE);
	}
	void tearDown()
	{
		delete dict;
	}

	bool testinsertElement()
	{
		bool result = AVRUNIT_ASSERT_TESTNAME(dict->insertElement('c', 2.2f), "dict->insertElement('c', 2.2f)");

		result = AVRUNIT_ASSERT_TESTNAME(!dict->insertElement('c', 2.2f), "dict->insertElement('c', 2.2f) again");

		return result;
	}

	bool testfind()
	{
		dict->insertElement('c', 2.2f);
		dict->insertElement('d', 2.3f);
		dict->insertElement('e', 2.4f);
		dict->insertElement('f', 2.5f);
		dict->insertElement('g', 2.6f);

		bool result = AVRUNIT_ASSERT_EQUALS_DOUBLE(*dict->find('c'), 2.2f);
		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE(*dict->find('f'), 2.5f);
		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE(*dict->find('g'), 2.6f);

		return result & AVRUNIT_ASSERT_EQUALS_PTR_TESTNAME(dict->find('h'), NULL, "find non-existant");
	}

	bool testremoveElement()
	{
		dict->insertElement('c', 2.2f);
		dict->insertElement('d', 2.3f);
		dict->insertElement('e', 2.4f);
		dict->insertElement('f', 2.5f);
		dict->insertElement('g', 2.6f);

		AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(*dict->find('c'), 2.2f, "removeElement:dict->find('c')");

		bool result = AVRUNIT_ASSERT_TESTNAME(dict->removeElement('d'), "removeElement:dict->removeElement('d')");


		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(*dict->find('c'), 2.2f, "removeElement:dict->find('c')");
		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(*dict->find('f'), 2.5f, "removeElement:dict->find('f')");

		result &= AVRUNIT_ASSERT_TESTNAME(dict->insertElement('d', 2.3f), "removeElement:reinsert");

		dict->removeElement('c');
		dict->removeElement('d');
		dict->removeElement('f');
		dict->removeElement('g');
		dict->removeElement('e');


		result &= AVRUNIT_ASSERT_EQUALS_CHAR_TESTNAME(dict->numberOfElements(), 0, "removeElement:numberOfElements() == 0");

		result &= AVRUNIT_ASSERT_TESTNAME(!dict->removeElement('d'), "removeElement: try to remove unexistant");

		return result;
	}

	bool testremoveAllElements()
	{

		dict->insertElement('c', 2.2f);
		dict->insertElement('d', 2.3f);
		dict->insertElement('e', 2.4f);

		dict->removeAllElements();

		return AVRUNIT_ASSERT_EQUALS_LONG(dict->numberOfElements(), 0);
	}

	bool testclone()
	{
		dict->insertElement('c', 2.2f);
		dict->insertElement('d', 2.3f);
		dict->insertElement('e', 2.4f);

		Dictionary<char, float> dictClone(*dict);


		bool result = AVRUNIT_ASSERT_EQUALS_DOUBLE(*dictClone.find('c'), *dict->find('c'));

		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE(*dictClone.find('d'), *dict->find('d'));

		return result & AVRUNIT_ASSERT_EQUALS_DOUBLE(*dictClone.find('e'), *dict->find('e'));
	}

	bool testassign()
	{
		dict->insertElement('c', 2.2f);
		dict->insertElement('d', 2.3f);
		dict->insertElement('e', 2.4f);
		dict->insertElement('f', 2.5f);
		dict->insertElement('g', 2.6f);
		dict->insertElement('h', 2.2f);
		dict->insertElement('i', 2.3f);
		dict->insertElement('j', 2.4f);
		dict->insertElement('k', 2.5f);
		dict->insertElement('l', 2.6f);

		Dictionary<char, float>  dictClone(DICTIONARYTEST_SIZE/2); // it should grow to the right size

		dictClone = *dict;


		bool result = AVRUNIT_ASSERT_EQUALS_DOUBLE(*dictClone.find('c'), *dict->find('c'));

		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE(*dictClone.find('d'), *dict->find('d'));

		return result & AVRUNIT_ASSERT_EQUALS_DOUBLE(*dictClone.find('l'), *dict->find('l'));
	}

	bool testkeys()
	{
		dict->insertElement('c', 2.2f);
		dict->insertElement('d', 2.3f);
		dict->insertElement('e', 2.4f);

		Dictionary<char, float>::KeyIterator keyIter = dict->keys();

		bool result = AVRUNIT_ASSERT_EQUALS_CHAR_TESTNAME(*keyIter.current(), 'c', "key 1");

		result &= AVRUNIT_ASSERT_EQUALS_CHAR_TESTNAME(*keyIter.next(), 'd', "key 2");

		result &= AVRUNIT_ASSERT_EQUALS_CHAR_TESTNAME(*keyIter.previous(), 'c', "key 1 (previous)");

		keyIter.next();

		result &= AVRUNIT_ASSERT_EQUALS_CHAR_TESTNAME(*keyIter.next(), 'e', "key 3 (2 next)");

		return result;
	}

	bool testelements()
	{
		dict->insertElement('c', 2.2f);
		dict->insertElement('d', 2.3f);
		dict->insertElement('e', 2.4f);

		Dictionary<char, float>::ElementIterator elemIter = dict->elements();

		bool result = AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(*elemIter.current(), 2.2f, "elem 1");

		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(*elemIter.next(), 2.3f, "elem 2");

		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(*elemIter.previous(), 2.2f, "elem 1 (previous)");

		elemIter.next();

		result &= AVRUNIT_ASSERT_EQUALS_DOUBLE_TESTNAME(*elemIter.next(), 2.4f, "elem 3 (2 next)");

		return result;
	}

};

#endif /* DICTIONARYTEST_H_ */
