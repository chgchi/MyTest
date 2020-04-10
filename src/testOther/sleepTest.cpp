/*
 * sleepTest.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: echgchi
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "sleepTest.h"

// ./MyTest --gtest_filter=sleepTest.*

void sleepTest::SetUpTestCase() {


}

void sleepTest::TearDownTestCase() {


}

TEST_F (sleepTest, sleep) {

	unsigned int nTimeTestSec = 0; /* sec */

	unsigned int nTimeTest = 0; /* usec */
	struct timeval tvBegin;
	struct timeval tvNow;
	int ret = 0;
	unsigned int nDelay = 0; /* usec */
	fd_set rfds;
	struct timeval tv;
	int fd = 1;
	int i = 0;
	struct timespec req;
	unsigned int delay[20] = { 500000, 100000, 50000, 10000, 1000, 900, 500,
			200, 10, 1, 0 };
	int nReduce = 0;

	pthread_mutex_t _sleepMutex;
	pthread_cond_t _sleepCond;

	pthread_cond_init(&_sleepCond, 0);
	pthread_mutex_init(&_sleepMutex, 0);


	fprintf(stderr, "%18s%12s%12s%12s\n", "function", "time(usec)", "realTime",
			"reduce");
	fprintf(stderr,
			"-------------------------------------------------------------------\n");

	for (i = 0; i < 20; i++) {
		if (delay[i] <= 0)
			break;

		nDelay = delay[i];

		/*      test usleep */
		gettimeofday(&tvBegin, NULL);
		ret = usleep(nDelay);

		if (-1 == ret) {
			fprintf(stderr, " usleep error . errno=%d [%s]\n", errno,
					strerror(errno));
		}

		gettimeofday(&tvNow, NULL);
		nTimeTest = (tvNow.tv_sec - tvBegin.tv_sec) * 1000000 + tvNow.tv_usec
				- tvBegin.tv_usec;
		nReduce = nTimeTest - nDelay;
		fprintf(stderr, "\t usleep       %8u   %8u   %8d\n", nDelay, nTimeTest,
				nReduce);


		/*      test nanosleep */
		gettimeofday(&tvBegin, NULL);
		req.tv_sec = nDelay / 1000000;
		req.tv_nsec = (nDelay % 1000000) * 1000;
		ret = nanosleep(&req, NULL);

		if (-1 == ret) {
			fprintf(stderr, "\t nanosleep    %8u   not support\n", nDelay);
		} else {
			gettimeofday(&tvNow, NULL);
			nTimeTest = (tvNow.tv_sec - tvBegin.tv_sec) * 1000000
					+ tvNow.tv_usec - tvBegin.tv_usec;
			nReduce = nTimeTest - nDelay;
			fprintf(stderr, "\t nanosleep    %8u   %8u   %8d\n", nDelay,
					nTimeTest, nReduce);
		}

		/*      test select */
		gettimeofday(&tvBegin, NULL);
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		tv.tv_sec = 0;
		tv.tv_usec = nDelay;
		ret = select(0, NULL, NULL, NULL, &tv);

		if (-1 == ret) {
			fprintf(stderr, " select error . errno=%d [%s]\n", errno,
					strerror(errno));
		}

		gettimeofday(&tvNow, NULL);
		nTimeTest = (tvNow.tv_sec - tvBegin.tv_sec) * 1000000 + tvNow.tv_usec
				- tvBegin.tv_usec;
		nReduce = nTimeTest - nDelay;
		fprintf(stderr, "\t select       %8u   %8u   %8d\n", nDelay, nTimeTest,
				nReduce);

		{
			CriticalSection cs(&_sleepMutex);

			gettimeofday(&tvBegin, NULL);

			//int mSec = 250;
			struct timespec timer_wait;
			struct timeval now;
			gettimeofday(&now, 0); //wait 250ms
			timer_wait.tv_sec = now.tv_sec + (now.tv_usec + nDelay) / 1000000;
			timer_wait.tv_nsec = (now.tv_usec + nDelay) % 1000000 * 1000;
			pthread_cond_timedwait(&_sleepCond, &_sleepMutex, &timer_wait);

			gettimeofday(&tvNow, NULL);
			nTimeTest = (tvNow.tv_sec - tvBegin.tv_sec) * 1000000 + tvNow.tv_usec
					- tvBegin.tv_usec;
			nReduce = nTimeTest - nDelay;
			fprintf(stderr, "\t timedwait    %8u   %8u   %8d\n", nDelay, nTimeTest,
					nReduce);

		}

	}

	pthread_cond_destroy(&_sleepCond);
	pthread_mutex_destroy(&_sleepMutex);

}
