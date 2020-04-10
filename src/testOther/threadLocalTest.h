/*
 * threadLocalTest.h
 *
 *  Created on: 2017年10月11日
 *      Author: chic
 */

#ifndef SRC_TESTOTHER_THREADLOCALTEST_H_
#define SRC_TESTOTHER_THREADLOCALTEST_H_

#include <gtest/gtest.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>

pthread_key_t p_key;
class threadLocalTest: public testing::Test {
protected:
    static void SetUpTestCase();

    static void TearDownTestCase();

};

#endif /* SRC_TESTOTHER_THREADLOCALTEST_H_ */
