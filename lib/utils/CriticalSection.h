
#ifndef CRITICALSECTION_H
#define CRITICALSECTION_H

#include <pthread.h>

class CriticalSection
{
public:
    /**
     * Constructor accepting a pointer to the mutex which will be used
     * to control access to the section. The construction blocks until it
     * can exclusivly lock the mutex object.
     * It also registers a cancelation function to free the mutex if the
     * thread is terminated while in a critical section.
     */
    CriticalSection(pthread_mutex_t * mutex);

    /**
     * Distructor frees the locked mutex.
     */
    ~CriticalSection();

    /**
     * To support linux platform...
     */
    static void clean(void* arg);

    /**
     * Connivance function to initalise a re-entrant mutex.
     * \return upon success zero is returned; otherwise a pthread error code will be returned.
     */
    static int mutex_init(pthread_mutex_t *mutex);

private:

    pthread_mutex_t *_mutex; // pointer to the locking mutex

    /**
     * Control variable for the registered cancelation function.
     * \note This is for the solaris 10 implementation of assoicated
     * pthread_cancel_push & pthread_cancel_pop functions.  Future
     * versions of the operating system may require the implemetation
     * to change.
     */
    __pthread_cleanup_class* __clframe;

};

#endif
