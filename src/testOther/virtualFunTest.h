/*
 * virtualFunTest.h
 *
 *  Created on: Nov 30, 2016
 *      Author: echgchi
 */

#ifndef UT_VIRTUALFUNTEST_H_
#define UT_VIRTUALFUNTEST_H_

#include <gtest/gtest.h>


class virtualFunTest: public testing::Test {
protected:
	static void SetUpTestCase();

	static void TearDownTestCase();

	// Some expensive resource shared by all tests.

};


#endif /* UT_VIRTUALFUNTEST_H_ */
