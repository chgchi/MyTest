/*
 * boostOptionalTest.cpp
 *
 *  Created on: 2017年10月10日
 *      Author: chic
 */
#include <boost/optional.hpp>
#include <boost/typeof/typeof.hpp>
#include <math.h>
#include "boostOptionalTest.h"

// ./testBoost --gtest_filter=boostOptionalTest.*
using namespace boost;
using namespace std;

void boostOptionalTest::SetUpTestCase() {

}

void boostOptionalTest::TearDownTestCase() {

}

TEST_F (boostOptionalTest, test1) {
    boost::optional<int> op0;  //一个未初始化的optional对象
    boost::optional<int> op1(none);  //同上，使用none赋予未初始化值
    EXPECT_TRUE(!op0);
    EXPECT_TRUE(op0 == op1);
    EXPECT_TRUE(op1.get_value_or(253) == 253); //获取可选值
    boost::optional<string> ops("test");  //初始化为字符串test
    string str = *ops;     //用解引用操作符获取值
    cout << str.c_str() << endl;
    vector<int> v(10);
    boost::optional<vector<int>&> opv(v);  //容纳一个容器的引用
    EXPECT_TRUE(opv != none);
    opv->push_back(5);     //使用箭头操作符操纵容器
    EXPECT_TRUE(opv->size() == 11);
    opv = none;
    EXPECT_TRUE(!opv);
}

//计算倒数
boost::optional<double> calc(int x) {
    return boost::optional<double>(x != 0, 1.0 / x);     //条件构造函数
}
//计算实数的平方根
boost::optional<double> sqrt_op(double x) {
    return boost::optional<double>(x > 0, sqrt(x));   //条件构造函数
}

TEST_F (boostOptionalTest, test2) {
    boost::optional<double> d = calc(10);
    if (d)
        cout << *d << endl;
    d = sqrt_op(-10);
    if (!d)
        cout << "no result" << endl;
}

TEST_F (boostOptionalTest, test3) {
    auto x = boost::make_optional(5);
    EXPECT_TRUE(*x == 5);
    auto y = make_optional<double>((*x > 10), 1.0);
    EXPECT_TRUE(!y);
}


