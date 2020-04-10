///*
// * RWLockTest.cpp
// *
// *  Created on: Feb 2, 2015
// *      Author: echgchi
// */
//
//#include "RWLockTest.h"
//#include <time.h>
//#include <sys/time.h>
//#include <pthread.h>
//#include <iostream>
//
//static int readCnt1 = 0;
//static int readCnt2 = 0;
//
//void RWLockTest::SetUpTestCase()
//{
//
//}
//
//void RWLockTest::TearDownTestCase()
//{
//
//}
//
//static void* shared_task_handler(void* arg)
//{
//    RWLock* testptr = static_cast<RWLock*>(arg);
//
//    testptr->get_shared_lock();
//    //do the shared task here
//    printf("read readCnt %d     %d\n", readCnt1, readCnt2);
//
//    testptr->release_shared_lock();
//
//    return NULL;
//}
//
//static void * exclusive_task_handler(void * arg)
//{
//    RWLock* testptr = static_cast<RWLock*>(arg);
//    testptr->get_exclusive_lock();
//    //do the exclusive task here
//    readCnt1++;
//    readCnt2++;
//    printf("write readCnt %d    %d\n", readCnt1, readCnt2);
//    testptr->release_exclusive_lock();
//    return NULL;
//}
///*
//TEST_F (RWLockTest, test1)
//{
//    RWLock testptr;
//    readCnt1 = 0;
//    readCnt2 = 0;
//
//    const int THREADS_NO = 100;
//    pthread_t* threads = new pthread_t[THREADS_NO];
//
//    for (int i = 0; i < THREADS_NO; i++)
//    {
//        ThreadFunc tmpfunc = i % 3 ? shared_task_handler : exclusive_task_handler;
//        if (pthread_create(threads + i, NULL, tmpfunc, &testptr))
//        {
//            //cerr << "pthread_create fails" << endl;
//            exit(1);
//        }
//    }
//
//    for (int i = 0; i < THREADS_NO; i++)
//    {
//        pthread_join(threads[i], NULL);
//    }
//
//    delete[] threads;
//
//}
//
//static void * reader(void* arg)
//{
//    pthread_rwlock_t* testptr = static_cast<pthread_rwlock_t*>(arg);
//    pthread_rwlock_rdlock(testptr);
//    printf("read readCnt %d     %d\n", readCnt1, readCnt2);
//    pthread_rwlock_unlock(testptr);
//
//    return NULL;
//}
//
//static void * writer(void* arg)
//{
//    pthread_rwlock_t* testptr = static_cast<pthread_rwlock_t*>(arg);
//    pthread_rwlock_wrlock(testptr);
//    readCnt1++;
//    readCnt2++;
//    printf("write readCnt %d    %d\n", readCnt1, readCnt2);
//    pthread_rwlock_unlock(testptr);
//
//    return NULL;
//}
//
//
//TEST_F (RWLockTest, test2)
//{
//    pthread_rwlock_t rwlock;
//    pthread_rwlock_init(&rwlock, NULL);
//    readCnt1=0;
//    readCnt2=0;
//
//    const int THREADS_NO = 100;
//    pthread_t* threads = new pthread_t[THREADS_NO];
//
//    for (int i = 0; i < THREADS_NO; i++)
//    {
//        ThreadFunc tmpfunc = i % 3 ? reader : writer;
//        if (pthread_create(threads + i, NULL, tmpfunc, &rwlock))
//        {
//            //cerr << "pthread_create fails" << endl;
//            exit(1);
//        }
//    }
//
//    for (int i = 0; i < THREADS_NO; i++)
//    {
//        pthread_join(threads[i], NULL);
//    }
//
//    delete[] threads;
//
//    pthread_rwlock_destroy(&rwlock);
//
//}
//*/
