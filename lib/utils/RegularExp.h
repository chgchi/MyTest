/*
 * RegularExp.h
 *
 *  Created on: Jan 27, 2015
 *      Author: echgchi
 */

#ifndef REGULAREXP_H_
#define REGULAREXP_H_

#include <regex.h>


class RegularExp {
public:
	static RegularExp* instance();

	static void destroy();

	bool initRegexCmp(const char * pattern);

    void destroyRegex();

    bool isMatch(const char* str);

private:
	static RegularExp* _instance;

	regex_t _reg;

	RegularExp();
	virtual ~RegularExp();
};

#endif /* REGULAREXP_H_ */
