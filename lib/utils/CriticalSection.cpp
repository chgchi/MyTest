#include "CriticalSection.h"

void CriticalSection::clean(void* arg)
{
    pthread_mutex_unlock((pthread_mutex_t *)arg);
}


CriticalSection::CriticalSection(pthread_mutex_t * mutex)
    :_mutex(mutex)
{
    pthread_mutex_lock(_mutex);
    __clframe = new __pthread_cleanup_class(clean, (void*)_mutex);
}

CriticalSection::~CriticalSection()
{
    // run the thread cleanup code.
    __clframe->__setdoit(1);
    delete __clframe;
    __clframe = NULL;
}

//static

int CriticalSection::mutex_init(pthread_mutex_t *mutex)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(& attr);

    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    int ret = pthread_mutex_init(mutex, &attr);

    pthread_mutexattr_destroy(&attr);

    return ret;
}
