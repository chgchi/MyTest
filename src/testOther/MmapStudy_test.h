/*
 * MmapStudy_test.h
 *
 *  Created on: Nov 9, 2016
 *      Author: echgchi
 */

#ifndef UT_MMAPSTUDY_TEST_H_
#define UT_MMAPSTUDY_TEST_H_

#include<iostream>
#include <gtest/gtest.h>
#include "mmapStudy.h"



class MmapStudy_test: public testing::Test {
protected:
	static void SetUpTestCase();

	static void TearDownTestCase();

	// Some expensive resource shared by all tests.

public:
	mmapStudy _mmaphandler;

};




#endif /* UT_MMAPSTUDY_TEST_H_ */
