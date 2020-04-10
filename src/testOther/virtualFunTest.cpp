/*
 * virtualFunTest.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: echgchi
 */

#include "virtualFunTest.h"
#include "virtualFun.h"

void virtualFunTest::SetUpTestCase() {


}

void virtualFunTest::TearDownTestCase() {

}

// ./MyTest --gtest_filter=virtualFunTest.test1
TEST_F (virtualFunTest, test1) {

	virtualFunSub obj;
    virtualFunBase *pBase = &obj;

    virtualFunSub *pSub = &obj;

    pBase->parNonVirtualcldNonvirtual();
    pSub->parNonVirtualcldNonvirtual();

    pBase->parVirtualcldNonvirtual();
    pSub->parVirtualcldNonvirtual();


    pBase->parNonVirtualcldvirtual();
    pSub->parNonVirtualcldvirtual();

}
