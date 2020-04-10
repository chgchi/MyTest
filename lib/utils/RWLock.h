/*
 * RWLock.h
 *
 *  Created on: Jan 30, 2015
 *      Author: echgchi
 */
/*
 * Solaris 库（lib 线程）            Linux POSIX 库（libp 线程）                  操作
 * sema_destroy()              sem_destroy()                           销毁信号状态。
 * sema_init()                 sem_init()                              初始化信号。
 * sema_post()                 sem_post()                              增加信号。
 * sema_wait()                 sem_wait()                              阻止信号计数。
 * sema_trywait()              sem_trywait()                           减少信号计数。
 * mutex_destroy()             pthread_mutex_destroy()                 销毁或禁用与互斥对象相关的状态。
 * mutex_init()                pthread_mutex_init()                    初始化互斥变量。
 * mutex_lock()                pthread_mutex_lock()                    锁定互斥对象和块，直到互斥对象被释放。
 * mutex_unlock()              pthread_mutex_unlock()                  释放互斥对象。
 * cond_broadcast()            pthread_cond_broadcast()                解除对等待条件变量的所有线程的阻塞。
 * cond_destroy()              pthread_cond_destroy()                  销毁与条件变量相关的任何状态。
 * cond_init()                 pthread_cond_init()                     初始化条件变量。
 * cond_signal()               pthread_cond_signal()                   解除等待条件变量的下一个线程的阻塞。
 * cond_wait()                 pthread_cond_wait()                     阻止条件变量，并在最后释放它。
 * rwlock_init()               pthread_rwlock_init()                   初始化读／写锁。
 * rwlock_destroy()            pthread_rwlock_destroy()                锁定读／写锁。
 * rw_rdlock()                 pthread_rwlock_rdlock()                 读取读／写锁上的锁。
 * rw_wrlock()                 pthread_rwlock_wrlock()                 写读／写锁上的锁。
 * rw_unlock()                 pthread_rwlock_unlock()                 解除读／写锁。
 * rw_tryrdlock()              pthread_rwlock_tryrdlock()              读取非阻塞读／写锁上的锁。
 * rw_trywrlock()              pthread_rwlock_trywrlock()              写非阻塞读／写锁上的锁。
 */

#ifndef RWLOCK_H_
#define RWLOCK_H_


#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
class RWLock
{
public:
    RWLock();
    virtual ~RWLock();

    void get_shared_lock();
    void release_shared_lock();
    void get_exclusive_lock();
    void release_exclusive_lock();

private:
    pthread_mutex_t cnt_mutex;
    pthread_cond_t rw_cond;
    int rd_cnt, wr_cnt;

    RWLock(const RWLock&);
    RWLock& operator= (const RWLock&);
};

#endif /* RWLOCK_H_ */
