/*
 * autoPtrTest.h
 *
 *  Created on: Oct 13, 2015
 *      Author: echgchi
 */

#ifndef AUTOPTRTEST_H_
#define AUTOPTRTEST_H_

#include <gtest/gtest.h>
#include<iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "construct A!!!" << endl;
    }
    ;
    ~A()
    {
        cout << "destruct A!!!" << endl;
    }
    ;
};
class B: public A
{
public:
    B()
    {
        cout << "construct B!!!" << endl;
    }
    ;
    ~B()
    {
        cout << "destruct B!!!" << endl;
    }
    ;
};


class autoPtrTest: public testing::Test {
protected:
	static void SetUpTestCase();

	static void TearDownTestCase();

	// Some expensive resource shared by all tests.

};


#endif /* AUTOPTRTEST_H_ */
