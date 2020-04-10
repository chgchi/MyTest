/*
 *  Created on: Dec 15, 2014
 *      Author: echgchi
 */
#include <pthread.h>
#include "pollTest.h"

void* ThreadFun1(void * arg) {
	epollServer * server = new epollServer();
	server->startEpollServer();
	return NULL;
}

void PollTest::SetUpTestCase() {
	//int pthread_create(pthread_t *tidp,const pthread_attr_t *attr, (void*)(*start_rtn)(void*),void *arg);
	int ret = 0;
	pthread_t pid;

	//ret = pthread_create(&pid, 0, ThreadFun1,NULL);

}

void PollTest::TearDownTestCase() {

}

TEST_F (PollTest, test1) {



}

