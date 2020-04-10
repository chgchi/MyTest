/*
 * uniqueptrTest.h
 *
 *  Created on: 2017年9月30日
 *      Author: chic
 */

#ifndef SRC_TESTSTL_UNIQUEPTRTEST_H_
#define SRC_TESTSTL_UNIQUEPTRTEST_H_
#include <gtest/gtest.h>

#define CHECKPOINT(p0,p1) \
do\
{\
    printf("\t%s is %p;\n",#p0,p0.get());\
    printf("\t%s is %p;\n",#p1,p1.get());\
}while(0)

class myData {
public:
	myData(int data) :
			_data(data) {
		printf("-- in constructor :%p!\n", this);
	}
	myData(const myData&) {
		printf("-- in copy constructor:%p!\n", this);
	}
	const myData& operator=(const myData&) {
		printf("-- in assign operator :%p!\n", this);
		return *this;
	}
	~myData() {
		printf("-- in destructor :%p!\n", this);
	}
private:
	int _data;
};

class uniqueptrTest: public testing::Test {

protected:
	static void SetUpTestCase();

	static void TearDownTestCase();

};

#endif /* SRC_TESTSTL_UNIQUEPTRTEST_H_ */

