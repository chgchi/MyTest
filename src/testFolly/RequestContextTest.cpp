/*
 * Copyright 2004-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <thread>

#include <folly/Memory.h>
#include <folly/io/async/EventBase.h>
#include <folly/io/async/Request.h>
#include <folly/portability/GTest.h>

using namespace folly;

class TestData: public RequestData {
public:
    explicit TestData(int data) :
            data_(data) {
    }
    ~TestData() override {
    }
    void onSet() override {
        set_++;
    }
    void onUnset() override {
        unset_++;
    }
    int set_ = 0, unset_ = 0;
    int data_;
};

//./testFolly --gtest_filter=RequestContext.MutilThreadTest
TEST(RequestContext, MutilThreadTest) {

    constexpr uint32_t numThreads = 20;

    std::deque<std::thread> threads;
    SCOPE_EXIT {   //execute the code block before finish the local scope(Wait on all of the threads.)
                for (auto& thread : threads) {
                    thread.join();
                }
            };

//    RequestContext::create();
    auto requestCtx0 = RequestContext::get();
    std::cout << "in main thread 1" << pthread_self() << " ctx: " << requestCtx0 << std::endl;


    for (uint32_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([i] {
            if(i == 1){
            RequestContext::create();
            }
            auto requestCtx= RequestContext::get();
            std::cout << "in thread " << (int)i << " ctx: " << requestCtx << std::endl;
            usleep(10000);
            requestCtx= RequestContext::get();
            std::cout << "in thread " << (int)i << " ctx: " << requestCtx << std::endl;
        });

    }


    sleep(2);

}

//./testFolly --gtest_filter=RequestContext.SimpleTest
TEST(RequestContext, SimpleTest) {


    // There should always be a default context with get()
    //try to get a SingletonThreadLocal RequestContext(getStaticContext()),
    //if there is not one, create a local static RequestContext and return it.
    auto requestCtx0 = RequestContext::get();
    EXPECT_TRUE(requestCtx0 != nullptr);
    std::cout << "in thread " << pthread_self() << " ctx: " << requestCtx0 << std::endl;

    RequestContext::get()->setContextData("test", std::make_unique < TestData > (20));

    // but not with saveContext()
    //saveContext is called to get a shared_ptr to the context, and
    // setContext is used to reset it on the other side of the queue.
    EXPECT_EQ(RequestContext::saveContext(), nullptr);   //equal to getStaticContext()
    RequestContext::create();    //create a new RequestContext and set as Threadlocal RequestContext
    auto requestCtx1 = RequestContext::saveContext();
    EXPECT_NE(requestCtx1, nullptr);
    std::cout << "in main thread " << pthread_self() << " ctx: " << requestCtx1 << std::endl;

    RequestContext::create();
    auto requestCtx2 = RequestContext::saveContext();
    EXPECT_NE(requestCtx2, nullptr);
    std::cout << "in main thread " << pthread_self() << " ctx: " << requestCtx2 << std::endl;

    EXPECT_NE(requestCtx1, requestCtx2);

    EXPECT_EQ(nullptr, RequestContext::get()->getContextData("test"));

    //insert data in the RequestContext of main thread local
    RequestContext::get()->setContextData("test", std::make_unique < TestData > (10));

    //in a new normal thread, will try to get its own threadlocal RequestContext or default local static RequestContext
    std::thread thread1([]{
            auto requestCtxInthread = RequestContext::get();
            EXPECT_TRUE(requestCtxInthread != nullptr);
            std::cout << "in my thread " << pthread_self()<< " ctx: " << requestCtxInthread <<std::endl;

            auto data = dynamic_cast<TestData*>(
                    requestCtxInthread->getContextData("test"))->data_;
            EXPECT_EQ(20, data);

    });
    thread1.join();

    EventBase base;

    //Why we will get the same thread local RequestContext in main thread in the Eventbase loop thread
    base.runInEventBaseThread([&base]() {

        auto requestCtxInthread = RequestContext::get();
        EXPECT_TRUE(requestCtxInthread != nullptr);
        std::cout << "in eventbase thread " << pthread_self()<< " ctx: " << requestCtxInthread <<std::endl;

        auto data = dynamic_cast<TestData*>(
                requestCtxInthread->getContextData("test"))->data_;
        EXPECT_EQ(10, data);
//        base.terminateLoopSoon();
    });


    std::thread thread2([&base]{
            base.runInEventBaseThread([&base]() {

                auto requestCtxInthread = RequestContext::get();
                EXPECT_TRUE(requestCtxInthread != nullptr);
                std::cout << "in eventbase thread 2 " << pthread_self()<< " ctx: " << requestCtxInthread <<std::endl;

                auto data = dynamic_cast<TestData*>(
                        requestCtxInthread->getContextData("test"))->data_;
                EXPECT_EQ(20, data);
                base.terminateLoopSoon();
            });
    });
    thread2.join();


    std::cout << "before start EventBase loop " <<std::endl;
    auto th = std::thread([&]() {
        base.loopForever();
    });
    th.join();




    EXPECT_TRUE(RequestContext::get() != nullptr);
    auto a = dynamic_cast<TestData*>(RequestContext::get()->getContextData("test"));
    auto data = a->data_;
    EXPECT_EQ(10, data);

    RequestContext::setContext(std::shared_ptr<RequestContext>());
    // There should always be a default context
    EXPECT_TRUE(nullptr != RequestContext::get());

}

TEST(RequestContext, setIfAbsentTest) {
    EXPECT_TRUE(RequestContext::get() != nullptr);

    RequestContext::get()->setContextData("test", std::make_unique < TestData > (10));
    EXPECT_FALSE(RequestContext::get()->setContextDataIfAbsent("test", std::make_unique < TestData > (20)));
    EXPECT_EQ(10, dynamic_cast<TestData*>(RequestContext::get()->getContextData("test"))->data_);

    EXPECT_TRUE(RequestContext::get()->setContextDataIfAbsent("test2", std::make_unique < TestData > (20)));
    EXPECT_EQ(20, dynamic_cast<TestData*>(RequestContext::get()->getContextData("test2"))->data_);

    RequestContext::setContext(std::shared_ptr<RequestContext>());
    EXPECT_TRUE(nullptr != RequestContext::get());
}

TEST(RequestContext, testSetUnset) {
    RequestContext::create();
    auto ctx1 = RequestContext::saveContext();
    ctx1->setContextData("test", std::make_unique < TestData > (10));
    auto testData1 = dynamic_cast<TestData*>(ctx1->getContextData("test"));

    // Override RequestContext
    RequestContext::create();
    auto ctx2 = RequestContext::saveContext();
    ctx2->setContextData("test", std::make_unique < TestData > (20));
    auto testData2 = dynamic_cast<TestData*>(ctx2->getContextData("test"));

    // Check ctx1->onUnset was called
    EXPECT_EQ(0, testData1->set_);
    EXPECT_EQ(1, testData1->unset_);

    RequestContext::setContext(ctx1);
    EXPECT_EQ(1, testData1->set_);
    EXPECT_EQ(1, testData1->unset_);
    EXPECT_EQ(0, testData2->set_);
    EXPECT_EQ(1, testData2->unset_);

    RequestContext::setContext(ctx2);
    EXPECT_EQ(1, testData1->set_);
    EXPECT_EQ(2, testData1->unset_);
    EXPECT_EQ(1, testData2->set_);
    EXPECT_EQ(1, testData2->unset_);
}

TEST(RequestContext, deadlockTest) {
    class DeadlockTestData: public RequestData {
    public:
        explicit DeadlockTestData(const std::string& val) :
                val_(val) {
        }

        ~DeadlockTestData() override {
            RequestContext::get()->setContextData(val_, std::make_unique < TestData > (1));
        }

        void onSet() override {
        }

        void onUnset() override {
        }

        std::string val_;
    };

    RequestContext::get()->setContextData("test", std::make_unique < DeadlockTestData > ("test2"));
    RequestContext::get()->clearContextData("test");
}
