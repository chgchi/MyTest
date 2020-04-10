/*
 * MySingleton.h
 *
 *  Created on: Mar 27, 2017
 *      Author: echgchi
 */

#ifndef MYSINGLETON_H_
#define MYSINGLETON_H_

#include <pthread.h>

class MySingleton {

public:
	static MySingleton* getInstance();
	static void destroy();

private:
	MySingleton(){};
	virtual ~MySingleton(){};
	//把复制构造函数和=操作符也设为私有,防止被复制
	MySingleton(const MySingleton&);
	MySingleton& operator=(const MySingleton&);

	static MySingleton* _instance;
    static pthread_mutex_t _instMutex;
};

#endif /* MYSINGLETON_H_ */
