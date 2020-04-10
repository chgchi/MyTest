/*
 * alignTest.h
 *
 *  Created on: May 9, 2017
 *      Author: echgchi
 */

#ifndef UT_ALIGNTEST_H_
#define UT_ALIGNTEST_H_

#include <gtest/gtest.h>
#include<iostream>
using namespace std;


class alignTest: public testing::Test {
protected:
	static void SetUpTestCase();

	static void TearDownTestCase();

	// Some expensive resource shared by all tests.

};


#endif /* UT_ALIGNTEST_H_ */
