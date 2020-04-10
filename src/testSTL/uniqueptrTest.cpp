/*
 * uniqueptrTest.cpp
 *
 *  Created on: 2017年9月30日
 *      Author: chic
 */

// ./testSTL --gtest_filter=uniqueptrTest.*
#include "uniqueptrTest.h"
#include <memory>
using namespace std;
void uniqueptrTest::SetUpTestCase() {

}

void uniqueptrTest::TearDownTestCase() {

}

TEST_F (uniqueptrTest, create) {

    // 创建一个unique_ptr实例
    {
        unique_ptr<myData> pInt(new myData(5));
    }

    //普通的new[]对象.
    {
        std::unique_ptr<int[]> p2(new int[4]{1,2,3,4});
    }

    //unique不支持拷贝构造函数
    //unique_ptr<int> pInt2(pInt);    // 报错
    //unique_ptr<int> pInt3 = pInt;   // 报错

}

unique_ptr<int> clone(int p)
{
    unique_ptr<int> pInt(new int(p));
    return pInt;    // 返回unique_ptr
}

TEST_F (uniqueptrTest, move) {
    unique_ptr<int> pInt(new int(5));
    unique_ptr<int> pInt2 = std::move(pInt);    // 转移所有权
    //cout << *pInt << endl; // 出错，pInt为空
    cout << *pInt2 << endl;

    //unique_ptr不支持拷贝操作, 但是支持移动拷贝构造。因此可以从函数中返回一个unique_ptr
    int p = 5;
    unique_ptr<int> ret = clone(p);
    cout << *ret << endl;
}

TEST_F (uniqueptrTest, InContainer) {
    //支持放入容器
    vector<unique_ptr<myData>> vec;
    unique_ptr<myData> p(new myData(5));
}

// ./testSTL --gtest_filter=uniqueptrTest.reset
TEST_F (uniqueptrTest, reset) {
    //支持放入容器
    unique_ptr<myData> p(new myData(5));  //资源的引用计数减一
    p.reset();
}

