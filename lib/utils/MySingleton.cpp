/*
 * MySingleton.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: echgchi
 */
#include <stddef.h>
#include "MySingleton.h"

MySingleton* MySingleton::_instance = NULL;
pthread_mutex_t MySingleton::_instMutex = PTHREAD_MUTEX_INITIALIZER;

MySingleton* MySingleton::getInstance() {
	if (_instance == NULL) {
		pthread_mutex_lock(&_instMutex);
		if (_instance == NULL) {
			_instance = new MySingleton();
		}
		pthread_mutex_unlock(&_instMutex);
	}

	return _instance;
}


void MySingleton::destroy()
{
	delete _instance;
}
