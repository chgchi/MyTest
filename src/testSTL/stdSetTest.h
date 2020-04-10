/*
 * stdSetTest.h
 *
 *  Created on: Mar 7, 2017
 *      Author: echgchi
 */

#ifndef UT_STDSETTEST_H_
#define UT_STDSETTEST_H_
#include <string>
#include <functional>
#include <algorithm>
#include <gtest/gtest.h>

bool fncomp(int lhs, int rhs) {
	return lhs < rhs;
}

struct classcomp {
	bool operator()(const int& lhs, const int& rhs) const {
		return lhs < rhs;
	}
};

int ciCharCompare(char c1, char c2) // 忽略大小写比较字符
		{
	int Ic1 = tolower(static_cast<unsigned char>(c1));
	int Ic2 = tolower(static_cast<unsigned char>(c2));
	if (Ic1 < Ic2)
		return -1;
	if (Ic1 > Ic2)
		return 1;
	return 0;
}


int ciStringCompareImpl(const std::string& s1, const std::string& s2) {
	typedef std::pair<std::string::const_iterator, std::string::const_iterator> PSCI; // PSCI = “pair of string::const_iterator”

	PSCI p = std::mismatch(s1.begin(), s1.end(), s2.begin(), std::not2(std::ptr_fun(ciCharCompare))); // 下文解释了为什么我们需要not2；参见条款41解释了为什么我们需要ptr_fun

	if (p.first == s1.end()) {
		if (p.second == s2.end())
			return 0;
		else
			return -1;

	}
	return ciCharCompare(*p.first, *p.second);
}

int ciStringCompare(const std::string& s1, const std::string& s2) {
	if (s1.size() <= s2.size())
		return ciStringCompareImpl(s1, s2);
	else
		return -ciStringCompareImpl(s2, s1);
}




bool ciCharLess(char c1, char c2) // 返回在忽略大小写的情况下c1是否在c2前面；
{
	return tolower(static_cast<unsigned char>(c1)) < tolower(static_cast<unsigned char>(c2));
}



bool ciStringCompare1(const std::string& s1, const std::string& s2)
{
    return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharLess);
}


struct CIStringCompare: public std::binary_function<std::string, std::string,bool>
{
	bool operator()(const std::string& lhs, const std::string& rhs) const {
		return ciStringCompare1(lhs, rhs);
	}
};



class stdSetTest: public testing::Test {
public:
	static void SetUpTestCase();

	static void TearDownTestCase();
};

#endif /* UT_STDSETTEST_H_ */
