/*
 * virtualFun.h
 *
 *  Created on: Nov 30, 2016
 *      Author: echgchi
 */

#ifndef INCLUDE_VIRTUALFUN_H_
#define INCLUDE_VIRTUALFUN_H_



class virtualFunBase {
public:
	virtualFunBase(){};
	virtual ~virtualFunBase(){};

	void parNonVirtualcldNonvirtual();
	virtual void parVirtualcldNonvirtual();
	void parNonVirtualcldvirtual();
};



class virtualFunSub : public virtualFunBase{
public:
	virtualFunSub(){};
	virtual ~virtualFunSub(){};

	void parNonVirtualcldNonvirtual();
	void parVirtualcldNonvirtual();
	virtual void parNonVirtualcldvirtual();

};


#endif /* INCLUDE_VIRTUALFUN_H_ */
