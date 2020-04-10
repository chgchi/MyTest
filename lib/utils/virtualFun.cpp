/*
 * virtualFun.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: echgchi
 */
#include <iostream>
#include "virtualFun.h"

using namespace std;

void virtualFunBase::parNonVirtualcldNonvirtual() {
	cout<<"virtualFunBase::parNonVirtualcldNonvirtual"<<endl;
}

void virtualFunBase::parVirtualcldNonvirtual() {
	cout<<"virtualFunBase::parVirtualcldNonvirtual"<<endl;
}

void virtualFunBase::parNonVirtualcldvirtual() {
	cout<<"virtualFunBase::parNonVirtualcldvirtual"<<endl;
}

void virtualFunSub::parNonVirtualcldNonvirtual() {
	cout<<"virtualFunSub::parNonVirtualcldNonvirtual"<<endl;
}

void virtualFunSub::parVirtualcldNonvirtual() {
	cout<<"virtualFunSub::parVirtualcldNonvirtual"<<endl;
}

void virtualFunSub::parNonVirtualcldvirtual() {
	cout<<"virtualFunSub::parNonVirtualcldvirtual"<<endl;
}

