/*
 * EventBaseManagerTest.cpp
 *
 *  Created on: 2017年11月2日
 *      Author: chic
 */

#include <chrono>

#include <folly/synchronization/Baton.h>
#include <folly/system/ThreadName.h>
#include <folly/io/async/EventBaseThread.h>
#include <folly/io/async/EventBaseManager.h>
#include <folly/portability/GTest.h>

using namespace std;
using namespace std::chrono;
using namespace folly;

//./testFolly --gtest_filter=EventBaseManagerTest.testLocal
//make sure each thread can get its own local eventbase from EventBaseManager
TEST(EventBaseManagerTest, testLocal) {

    constexpr uint32_t numThreads = 10;
    std::set<EventBase *> eventBaseSet;
    auto eventBaseManager = folly::EventBaseManager::get();
    auto eventBase = eventBaseManager->getEventBase();
    eventBaseSet.insert(eventBase);
    std::cout << "main thread id: " << pthread_self() << " eventbase: " << eventBase << std::endl;

    deque<std::thread> threads;
    SCOPE_EXIT {   //execute the code block before finish the local scope(Wait on all of the threads.)
                for (auto& thread : threads) {
                    thread.join();
                }
            };

    for (uint32_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([eventBaseManager, &eventBaseSet] {
            auto eventBaseinthread = eventBaseManager->getEventBase();
            std::cout << "thread id: " << pthread_self() << " eventbase: "<< eventBaseinthread<< std::endl;
            eventBaseSet.insert(eventBaseinthread);
            sleep(1);
        });
    }
    sleep(1);
    ASSERT_EQ(11, eventBaseSet.size());
}
