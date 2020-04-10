/*
 * stdStringTest.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: echgchi
 */
#include <string>
#include <iostream>
#include "stdStringTest.h"

// ./MyTest --gtest_filter=stdStringTest.*

void stdStringTest::SetUpTestCase() {

}

void stdStringTest::TearDownTestCase() {

}

TEST_F (stdStringTest, sizeofAString) {

	std::string s("Perse1111111111111111111111111111111");
	std::cout << sizeof(s) << std::endl;
}

void Tokenize(const std::string& str, std::vector<std::string>& tokens,
		const std::string& delimiters) {
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

TEST_F (stdStringTest, testTokenize) {
	std::string str("====aaa==bbb=ccc=ddd====");
	std::vector<std::string> tokens;
	Tokenize(str, tokens, "=");

	for (size_t i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i] << std::endl;
	}

}


TEST_F (stdStringTest, find) {
	std::string str("^_^@12345@teststring@hostname_6789");
	std::size_t found = str.rfind("@");
	std::string result;
	if (found!=std::string::npos)
		result = str.substr(++found);

	  std::cout << result << '\n';

}
