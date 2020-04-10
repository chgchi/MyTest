/*
 * stdBindTest.h
 *
 *  Created on: Feb 28, 2017
 *      Author: echgchi
 */

#ifndef UT_STDBINDTEST_H_
#define UT_STDBINDTEST_H_

#include <iostream>
#include <gtest/gtest.h>

 int func(int a){
     std::cout << __FUNCTION__ << "(" << a << ") ->: ";
     return a;
 }

 class Foo
 {
 public:
     static int foo_func(int a){
         std::cout << __FUNCTION__ << "(" << a << ") ->: ";
         return a;
     }
 };

 class Bar
 {
 public:
     int operator()(int a){
         std::cout << __FUNCTION__ << "(" << a << ") ->: ";
         return a;
     }
 };


class stdBindTest:public testing::Test {
public:
	static void SetUpTestCase();

	static void TearDownTestCase();
};

#endif /* UT_STDBINDTEST_H_ */
