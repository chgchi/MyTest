/*
 * threadLocalTest.cpp
 *
 *  Created on: 2017年10月11日
 *      Author: chic
 */

#include "threadLocalTest.h"

// ./testOther --gtest_filter=threadLocalTest.*
void threadLocalTest::SetUpTestCase() {


}

void threadLocalTest::TearDownTestCase() {

}


void func1()
{
        int *tmp = (int*)pthread_getspecific(p_key);//同一线程内的各个函数间共享数据。
        printf("%d is runing in %s\n",*tmp,__func__);

}
void *thread_func(void *args)
{

        pthread_setspecific(p_key,args);

        int *tmp = (int*)pthread_getspecific(p_key);//获得线程的私有空间
        printf("%d is runing in %s\n",*tmp,__func__);

        *tmp = (*tmp)*100;//修改私有变量的值

        func1();

        return (void*)0;
}

TEST_F (threadLocalTest, test1) {
    pthread_t pa, pb;
    int a=1;
    int b=2;
    pthread_key_create(&p_key,NULL);
    pthread_create(&pa, NULL,thread_func,&a);
    pthread_create(&pb, NULL,thread_func,&b);
    pthread_join(pa, NULL);
    pthread_join(pb, NULL);
}
