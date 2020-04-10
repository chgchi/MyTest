/*
 * autoPtrTest.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: echgchi
 */

#include "autoPtrTest.h"
#include <vector>
#include <tr1/memory>

// ./MyTest --gtest_filter=autoPtrTest.*

void autoPtrTest::SetUpTestCase() {

}

void autoPtrTest::TearDownTestCase() {

}

TEST_F (autoPtrTest, test1) {
	B* ptrB0 = new B();
	std::cout << "orig pointer: " << ptrB0 << std::endl;
	//std::tr1::shared_ptr<B> ptrB1(new B);

	std::tr1::shared_ptr<B> ptrB1;
	std::tr1::shared_ptr<B> ptrB2;
	std::tr1::shared_ptr<B> ptrB3;

	ptrB1 = std::tr1::shared_ptr<B>(ptrB0);
	std::cout << "sp1 pointer count: " << ptrB1.use_count() << std::endl;
	std::cout << "sp1 pointer: " << ptrB1.get() << std::endl;

	//    ptrB2 = std::tr1::shared_ptr<B>(ptrB0);
	ptrB2 = ptrB1;
	B* tmp = ptrB2.get();
	std::cout << "sp2 pointer count: " << ptrB2.use_count() << std::endl;
	std::cout << "sp2 pointer: " << ptrB2.get() << std::endl;
//
//	    //ptrB1.reset(ptrB0);
//
//	    //ptrB2.reset(ptrB0);
//	    //ptrB3.reset(ptrB0);
	std::vector<std::tr1::shared_ptr<B> > myvector;
	myvector.push_back(ptrB2);
	std::cout << "sp3 pointer count: " << ptrB2.use_count() << std::endl;
	std::cout << "sp3 pointer: " << ptrB2.get() << std::endl;

	myvector.clear();
	std::cout << "sp4 pointer count: " << ptrB1.use_count() << std::endl;
	std::cout << "sp4 pointer: " << ptrB1.get() << std::endl;

}

TEST_F (autoPtrTest, empty) {

	std::tr1::shared_ptr<B> ptrB;
	std::cout << "get for empty shared_ptr: " << ptrB.get() << std::endl;

	std::cout << "empty shared_ptr count: " << ptrB.use_count() << std::endl;

}
