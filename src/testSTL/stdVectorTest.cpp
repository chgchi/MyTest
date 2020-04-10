/*
 * stdVectorTest.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: echgchi
 */
#include <vector>
#include <algorithm>
#include "stdVectorTest.h"

// ./MyTest --gtest_filter=stdVectorTest.*

void stdVectorTest::SetUpTestCase() {

}

void stdVectorTest::TearDownTestCase() {

}

TEST_F (stdVectorTest, assign) {

	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;

	first.assign(7, 100);             // 7 ints with a value of 100

	std::vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1); // the 5 central values of first

	int myints[] = { 1776, 7, 4 };
	third.assign(myints, myints + 3);   // assigning from array.

	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
	std::cout << "Size of third: " << int(third.size()) << '\n';

}

TEST_F (stdVectorTest, remove_erase) {

	int myint[] = { 1, 2, 3, 5, 5, 5, 6, 7 };
	std::vector<int> myvector(myint, myint + (sizeof(myint) / sizeof(int)));

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.erase(std::remove(myvector.begin(), myvector.end(), 5),
			myvector.end());
	std::cout << "after remove_earse myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}

TEST_F (stdVectorTest, erase_in_loop) {

	int myint[] = { 1, 2, 3, 5, 5, 5, 6, 7 };
	std::vector<int> myvector(myint, myint + (sizeof(myint) / sizeof(int)));

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end();
			) {
		if (*it == 5) {
			it = myvector.erase(it);
			continue;
		}
		it++;
	}
	std::cout << "after remove_earse myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}

TEST_F (stdVectorTest, swap) {

	int myint[] = { 1, 2, 3, 5, 5, 5, 6, 7 };
	std::vector<int> myvector(myint, myint + (sizeof(myint) / sizeof(int)));

	std::cout << "myvector capacity:" << myvector.capacity() << "\n";

	myvector.erase(std::remove(myvector.begin(), myvector.end(), 5),
			myvector.end());

	std::cout << "after erase 3 elements myvector capacity:"
			<< myvector.capacity() << "\n";

	std::vector<int>(myvector).swap(myvector);

	std::cout << "used swap to clear redundant capacity,  myvector capacity:"
			<< myvector.capacity() << "\n";

}

TEST_F (stdVectorTest, reverseIterator) {

	std::vector<int> myvector;
	for (int i = 0; i < 10; i++)
		myvector.push_back(i);

	std::vector<int>::reverse_iterator ri = myvector.rbegin();

	std::cout << "the element on rbegin():"	<< *ri << "\n";

	std::cout << "the element on ri.base():"	<< *(ri.base()) << "\n";

	std::cout << "the element on (++ri).base():"	<< *(++ri).base() << "\n";

}

