/*
 * stdAlgorithmTest.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: echgchi
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>   // std::plu
#include <numeric>
#include "stdAlgorithmTest.h"

// ./testSTL --gtest_filter=stdAlgorithmTest.*

void stdAlgorithmTest::SetUpTestCase() {

}

void stdAlgorithmTest::TearDownTestCase() {

}

// remove algorithm example
TEST_F (stdAlgorithmTest, remove) {

	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 }; // 10 20 30 30 20 10 10 20

	// bounds of range:
	int* pbegin = myints;
	int* pend = myints + sizeof(myints) / sizeof(int);

	pend = std::remove(pbegin, pend, 20);         // 10 30 30 10 10

	std::cout << "range contains:";
	for (int* p = pbegin; p != pend; ++p)
		std::cout << ' ' << *p;
	std::cout << '\n';

}

TEST_F (stdAlgorithmTest, removeforVector) {

	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 }; // 10 20 30 30 20 10 10 20

	std::vector<int> myvector(myints, myints + sizeof(myints) / sizeof(int));

	std::vector<int>::iterator pend = std::remove(myvector.begin(),
			myvector.end(), 20);         // 10 30 30 10 10

	std::cout << "vector remain :" << myvector.size() << std::endl;

	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end();
			it++)
		std::cout << *it << " ";

	std::cout << std::endl;

	myvector.erase(pend, myvector.end());

	std::cout << "after erease vector remain :" << myvector.size();
	;

	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end();
			it++)
		std::cout << *it << " ";

	std::cout << std::endl;
}

int op_increase(int i) {
	return ++i;
}
//Applies an operation sequentially to the elements of one (1) or two (2) ranges
//and stores the result in the range that begins at result.
TEST_F (stdAlgorithmTest, transform) {
	std::vector<int> foo;
	std::vector<int> bar;

	// set some values:
	for (int i = 1; i < 6; i++)
		foo.push_back(i * 10);                         // foo: 10 20 30 40 50

	bar.resize(foo.size()); // very important, if not allocate enough space,may cause segment fault

	std::transform(foo.begin(), foo.end(), bar.begin(), op_increase);
	// bar: 11 21 31 41 51

	// std::plus adds together its two arguments:
	std::transform(foo.begin(), foo.end(), bar.begin(), foo.begin(),
			std::plus<int>());
	// foo: 21 41 61 81 101

	std::cout << "foo contains:";
	for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

}

TEST_F (stdAlgorithmTest, transformNoAlloc) {
	std::vector<int> foo;
	std::vector<int> bar;

	// set some values:
	for (int i = 1; i < 6; i++)
		foo.push_back(i * 10);                         // foo: 10 20 30 40 50

	//bar.resize(foo.size());  not pre-allocate space.

	std::transform(foo.begin(), foo.end(), back_inserter(bar), op_increase);
	// bar: 11 21 31 41 51

	std::cout << "bar contains:";
	for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

}

bool myfunction(int i, int j) {
	return (i < j);
}

TEST_F (stdAlgorithmTest, partialSort) {
	int myints[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::vector<int> myvector(myints, myints + 9);

	// using default comparison (operator <):
	std::partial_sort(myvector.begin(), myvector.begin() + 5, myvector.end());

	// using function as comp
	//std::partial_sort(myvector.begin(), myvector.begin() + 5, myvector.end(), myfunction);

	// print out content:
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end();
			++it)
		std::cout << ' ' << *it;
	std::cout << '\n';  //myvector contains: 1 2 3 4 5 9 8 7 6

}

int myfunc(int x, int y) {
	return x + 2 * y;
}
struct myclass {
	int operator()(int x, int y) {
		return x + 3 * y;
	}
} myobject;

TEST_F (stdAlgorithmTest, accumulate) {
	int init = 100;
	int numbers[] = { 10, 20, 30 };

	std::cout << "using default accumulate: ";
	std::cout << std::accumulate(numbers, numbers + 3, init);
	std::cout << '\n';

	std::cout << "using functional's minus: ";
	std::cout << std::accumulate(numbers, numbers + 3, init, std::minus<int>());
	std::cout << '\n';

	std::cout << "using custom function: ";
	std::cout << std::accumulate(numbers, numbers + 3, init, myfunc);
	std::cout << '\n';

	std::cout << "using custom object: ";
	std::cout << std::accumulate(numbers, numbers + 3, init, myobject);
	std::cout << '\n';
}

void myfun3(int i) {  // function:
	std::cout << ' ' << i;
}

struct myclass2 {           // function object type:
	void operator()(int i) {
		std::cout << ' ' << i;
	}
} myobject2;

TEST_F (stdAlgorithmTest, foreach) {
	std::vector<int> myvector;
	myvector.push_back(10);
	myvector.push_back(20);
	myvector.push_back(30);

	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myfun3);
	std::cout << '\n';

	// or:
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myobject2);
	std::cout << '\n';

}
