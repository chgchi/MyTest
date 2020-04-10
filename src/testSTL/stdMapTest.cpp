/*
 * stdMapTest.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: echgchi
 */
#include <map>
#include <iostream>
#include "stdMapTest.h"

// ./MyTest --gtest_filter=stdMapTest.*

void stdMapTest::SetUpTestCase() {

}

void stdMapTest::TearDownTestCase() {

}

TEST_F (stdMapTest, earse) {

	std::map<char, int> myMap;

	myMap['1'] = 10;
	myMap['2'] = 30;
	myMap['3'] = 50;
	myMap['4'] = 70;
	myMap['5'] = 70;
	myMap['6'] = 60;
	myMap['7'] = 70;

	std::cout <<"incorrect earse usage for remove value 70: \n";
	for (std::map<char, int>::iterator it = myMap.begin(); it != myMap.end(); ++it) // 清晰，直截了当而漏洞百出的用于删除c中badValue返回真
	{
		if ((*it).second == 70)
			myMap.erase(it); // erase 动作执行后， it已经被破坏， 再去 ++it 会有问题
	}

	for (std::map<char, int>::iterator it = myMap.begin(); it != myMap.end();++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second << ") \n";
	}

	std::cout <<"incorrect earse usage for remove value 70: \n";
	myMap['1'] = 10;
	myMap['2'] = 30;
	myMap['3'] = 50;
	myMap['4'] = 70;
	myMap['5'] = 70;
	myMap['6'] = 60;
	myMap['7'] = 70;

	for (std::map<char, int>::iterator it = myMap.begin(); it != myMap.end(); /*nothing*/ ) // 清晰，直截了当而漏洞百出的用于删除c中badValue返回真
	{
		if ((*it).second == 70){
			myMap.erase(it++); // 对于坏的值，先把当前的 i传给erase，然后作为副作用增加i；最后在执行erase
		                       //因为参数处理优先于函数调用，所以接下来执行了it++操作，也就是it现在已经指向了下一个地址。
		}
		else
			it++;
	}
	for (std::map<char, int>::iterator it = myMap.begin(); it != myMap.end();++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second << ") \n";
	}
}

// ./MyTest --gtest_filter=stdMapTest.lowerbound
TEST_F (stdMapTest, lowerbound) {
    std::map<int,int> mymap;
    std::map<int,int>::iterator itlow,itup;

    mymap[20]=21;
    mymap[40]=41;
    mymap[60]=61;
    mymap[80]=81;
    mymap[100]=101;

    itlow=mymap.lower_bound(59);  // itlow points to b
    itup=mymap.upper_bound(59);   // itup points to e (not d!)

    std::cout << "lowbound ："<<itlow->first << " => " << itlow->second << '\n';
    std::cout << "upperbound ："<<itup->first << " => " << itup->second << '\n';
}
