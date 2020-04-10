/*
 * TestEnviroment.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: echgchi
 */
# include <gtest/gtest.h>

//Write global test event

class TestEnvironment : public testing::Environment
 {
 public:
     virtual void SetUp()
     {
         std::cout << "TestEnvironment SetUP" << std::endl;
     }
     virtual void TearDown()
     {
         std::cout << "TestEnvironment TearDown" << std::endl;
     }
 };

