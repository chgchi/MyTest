/*
 * sleepTest.h
 *
 *  Created on: Apr 11, 2017
 *      Author: echgchi
 */

#ifndef UT_SLEEPTEST_H_
#define UT_SLEEPTEST_H_

#include <gtest/gtest.h>
#include "CriticalSection.h"

class sleepTest:public testing::Test {
public:
	static void SetUpTestCase();

	static void TearDownTestCase();

public:

};

#endif /* UT_SLEEPTEST_H_ */
