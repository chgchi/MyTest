/*
 * RegularExp_test.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: echgchi
 */

#include "RegularExp_test.h"
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

void RegularExp_test::SetUpTestCase() {

}

void RegularExp_test::TearDownTestCase() {

}

void* ThreadFun(void * arg) {

	for (int i = 0; i < 1000; i++)
		RegularExp::instance()->isMatch("FA:16:3E:78:F7:F8");

	return NULL;
}
void* ThreadFun2(void * arg) {

	for (int i = 0; i < 1000; i++)
		RegularExp::instance()->isMatch("FA:16:3E:78:F7:F81");

	return NULL;
}

TEST_F (RegularExp_test, test1) {

	unsigned int nTimeTest = 0; // usec

	struct timeval tvBegin;
	struct timeval tvNow;

	gettimeofday(&tvBegin, NULL);
	RegularExp::instance()->initRegexCmp(
			"^([A-Fa-f0-9]{2}:){5}[A-Fa-f0-9]{2}$");

	gettimeofday(&tvNow, NULL);
	nTimeTest = (tvNow.tv_sec - tvBegin.tv_sec) * 1000000 + tvNow.tv_usec
			- tvBegin.tv_usec;

	printf("init cost %d usec\n", nTimeTest);

	gettimeofday(&tvBegin, NULL);
	RegularExp::instance()->isMatch("FA:16:3E:78:F7:F8");
	gettimeofday(&tvNow, NULL);
	nTimeTest = (tvNow.tv_sec - tvBegin.tv_sec) * 1000000 + tvNow.tv_usec
			- tvBegin.tv_usec;

	printf("exec cost %d usec\n", nTimeTest);

	gettimeofday(&tvBegin, NULL);
	RegularExp::instance()->destroyRegex();
	gettimeofday(&tvNow, NULL);
	nTimeTest = (tvNow.tv_sec - tvBegin.tv_sec) * 1000000 + tvNow.tv_usec
			- tvBegin.tv_usec;

	printf("destroy cost %d usec\n", nTimeTest);
}

TEST_F (RegularExp_test, test2) {

	RegularExp::instance()->initRegexCmp(
			"^([A-Fa-f0-9]{2}:){5}[A-Fa-f0-9]{2}$");

	pthread_t pid;
	int ret;
	//RegularExp::instance()->isMatch("FA:16:3E:78:F7:F8");
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0)
			ret = pthread_create(&pid, 0, ThreadFun, NULL);
		else
			ret = pthread_create(&pid, 0, ThreadFun2, NULL);
	}

	sleep(10);
	RegularExp::instance()->destroyRegex();
}

