/*
 * RWLock.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: echgchi
 */

#include "RWLock.h"

RWLock::RWLock() :
        rd_cnt(0), wr_cnt(0)
{
    pthread_mutex_init(&cnt_mutex, NULL);
    pthread_cond_init(&rw_cond, NULL);
}

RWLock::~RWLock()
{
    pthread_mutex_destroy(&cnt_mutex);
    pthread_cond_destroy(&rw_cond);
}

void RWLock::get_shared_lock()
{
    pthread_mutex_lock(&cnt_mutex);
    while (wr_cnt > 0)
    {
        pthread_cond_wait(&rw_cond, &cnt_mutex);
    }
    rd_cnt++;
    pthread_mutex_unlock(&cnt_mutex);
}

void RWLock::release_shared_lock()
{
    pthread_mutex_lock(&cnt_mutex);
    rd_cnt--;
    if (0 == rd_cnt)
    {
        pthread_cond_signal(&rw_cond);
    }
    pthread_mutex_unlock(&cnt_mutex);
}

void RWLock::get_exclusive_lock()
{
    pthread_mutex_lock(&cnt_mutex);
    while (rd_cnt + wr_cnt > 0)
    {
        pthread_cond_wait(&rw_cond, &cnt_mutex);
    }
    wr_cnt++;
    pthread_mutex_unlock(&cnt_mutex);
}

void RWLock::release_exclusive_lock()
{
    pthread_mutex_lock(&cnt_mutex);
    wr_cnt--;
    pthread_cond_broadcast(&rw_cond);
    pthread_mutex_unlock(&cnt_mutex);
}
