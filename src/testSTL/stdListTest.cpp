/*
 * stdListTest.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: echgchi
 */
#include <list>
#include "stdListTest.h"

// ./MyTest --gtest_filter=stdListTest.*

void stdListTest::SetUpTestCase() {

}

void stdListTest::TearDownTestCase() {

}

TEST_F (stdListTest, remove) {

	int myints[] = { 17, 89, 7, 14 };
	std::list<int> mylist(myints, myints + 4);

	mylist.remove(89);

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

// a predicate implemented as a function:
bool single_digit(const int& value) {
	return (value < 10);
}

// a predicate implemented as a class:
struct is_odd {
	bool operator()(const int& value) {
		return (value % 2) == 1;
	}
};

TEST_F (stdListTest, removeif) {

	int myints[] = { 15, 36, 7, 17, 20, 39, 4, 1 };
	std::list<int> mylist(myints, myints + 8);   // 15 36 7 17 20 39 4 1

	mylist.remove_if(single_digit);           // 15 36 17 20 39

	mylist.remove_if(is_odd());               // 36 20

	std::cout << "mylist contains:";
	for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}
