/*
 * stringTest.h
 *
 *  Created on: Jan 28, 2015
 *      Author: echgchi
 */

#ifndef STRINGTEST_H_
#define STRINGTEST_H_

#include <gtest/gtest.h>

class stringTest: public testing::Test {
protected:
    static void SetUpTestCase();

    static void TearDownTestCase();

    // Some expensive resource shared by all tests.

};
#endif /* STRINGTEST_H_ */
