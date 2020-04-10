/*
 * stdSetTest.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: echgchi
 */
#include <iostream>
#include <set>

#include "stdSetTest.h"

// ./MyTest --gtest_filter=stdSetTest.*

void stdSetTest::SetUpTestCase() {

}

void stdSetTest::TearDownTestCase() {

}

TEST_F (stdSetTest, pointerInSet) {

	std::set<std::string*> ssp; // ssp = “set of string ptrs”
	ssp.insert(new std::string("Anteater"));
	ssp.insert(new std::string("Combat"));
	ssp.insert(new std::string("Bemur"));
	ssp.insert(new std::string("Denguin"));

	std::copy(ssp.begin(), ssp.end(),
			std::ostream_iterator<std::string*>(std::cout, "\n")); // 把ssp中的字符串拷贝到cout

	for (std::set<std::string*>::const_iterator i = ssp.begin(); i != ssp.end();
			++i)
		std::cout << **i << std::endl;
}

TEST_F (stdSetTest, less_equal) {

	std::set<int, std::less_equal<int> > s; // s以“<=”排序
	s.insert(10); // 插入10
	s.insert(10); // insert 10 again
	//print invaild set content
	for (std::set<int, std::less_equal<int> >::iterator it = s.begin();
			it != s.end(); it++) {
		std::cout << *it << "\n";
	}
}

typedef std::multiset<int>::iterator It;

TEST_F (stdSetTest, equalRangeWithLessEqual) {

	std::multiset<int, std::less_equal<int> > s; // s仍然以“<=”排序
	s.insert(10); // 插入10A
	s.insert(10); // 插入10B

	std::pair<It, It> ret = s.equal_range(10);    //get an incorrect range
	s.erase(ret.first, ret.second);
	std::cout << "multiset contains:" << s.size() << "\n";   //still remain 2 elements
}

TEST_F (stdSetTest, equal_range) {

	int myints[] = { 77, 30, 16, 2, 30, 30 };
	std::multiset<int> mymultiset(myints, myints + 6);  // 2 16 30 30 30 77

	std::pair<It, It> ret = mymultiset.equal_range(30); //      ^        ^

	mymultiset.erase(ret.first, ret.second);

	std::cout << "mymultiset contains:";
	for (It it = mymultiset.begin(); it != mymultiset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

}
