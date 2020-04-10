/*
 * stdBindTest.cpp
 *
 *  Created on: Feb 28, 2017
 *      Author: echgchi
 */
#include <functional>
#include <iostream>
#include "stdBindTest.h"
using namespace std;

void stdBindTest::SetUpTestCase() {


}

void stdBindTest::TearDownTestCase() {

}

TEST_F (stdBindTest, test1) {

//    //bind a normal
//	function<int(int)> fr1 = func;
//    fr1();
//
//
//    //绑定一个类的静态成员函数
//    function<int(int)> fr2 = Foo::foo_func;
//    cout << fr2(123) << endl;

    //绑定一个仿函数
    Bar bar;
//    fr2 = bar;
    cout << bar(123) <<endl;

}
