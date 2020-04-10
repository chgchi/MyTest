/*
 * boostOptionalTest.h
 *
 *  Created on: 2017年10月10日
 *      Author: chic
 */

#ifndef SRC_TESTBOOST_BOOSTOPTIONALTEST_H_
#define SRC_TESTBOOST_BOOSTOPTIONALTEST_H_

#include <gtest/gtest.h>
#include<iostream>
using namespace std;

class boostOptionalTest: public testing::Test {
protected:
    static void SetUpTestCase();

    static void TearDownTestCase();

    // Some expensive resource shared by all tests.

};

#endif /* SRC_TESTBOOST_BOOSTOPTIONALTEST_H_ */
