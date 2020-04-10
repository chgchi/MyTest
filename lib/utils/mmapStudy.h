/*
 * mmapStudy.h
 *
 *  Created on: Nov 8, 2016
 *      Author: echgchi
 */

#ifndef MMAPSTUDY_H_
#define MMAPSTUDY_H_

#include <string>

#define BUF_SIZE 100

using std::string;

class mmapStudy {
public:
	mmapStudy();
	virtual ~mmapStudy();

public:
	void modifyfile(string filename);


};

#endif /* MMAPSTUDY_H_ */
