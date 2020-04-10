#include <gtest/gtest.h>
#include "epollClient.h"
#include "epollServer.h"

class PollTest: public testing::Test {
protected:
	static void SetUpTestCase();

	static void TearDownTestCase();

	// Some expensive resource shared by all tests.

};
