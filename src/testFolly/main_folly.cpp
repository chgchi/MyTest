//============================================================================
// Name        : myTest.cpp
// Author      : echgchi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <gtest/gtest.h>
#include <glog/logging.h>
#include "TestEnviroment.h"


int main(int argc, char *argv[]) {

    FLAGS_log_dir = "/chicheng/MyTest/build/bin/testFolly/logs";
    google::InitGoogleLogging(argv[0]);
	testing::AddGlobalTestEnvironment(new TestEnvironment);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
