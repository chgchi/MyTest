/*
 * MmapStudy_test.cpp
 *
 *  Created on: Nov 9, 2016
 *      Author: echgchi
 */

#include "MmapStudy_test.h"

void MmapStudy_test::SetUpTestCase() {

}

void MmapStudy_test::TearDownTestCase() {

}

TEST_F (MmapStudy_test, modifyFile) {
	_mmaphandler.modifyfile("text.txt");

}

