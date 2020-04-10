/*
 * Copyright 2017 Facebook, Inc.
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

#include <folly/executors/ThreadedExecutor.h>

#include <gtest/gtest.h>

#include <folly/Conv.h>
#include <folly/futures/Future.h>
#include <folly/gen/Base.h>

namespace {

class ThreadedExecutorTest : public testing::Test {};
}

//Future拥有一个via()函数，该函数需要一个Executor类型的参数。
// Executor是一个非常简单的接口，它只存在一个线程安全的add(std::function<void()> func) 方法，
//它会在某个时候执行这个func，尽管不是立即执行。而via()可以确保被设置的回调函数在指定的Executor上执行。例如：
//1 makeFutureWith(x)
//2   .via(exe1).then(y)
//3   .via(exe2).then(z);
//在上面的例子中，y将在exe1中执行，z将在exe2中执行，这是一个相当大的抽象，
//它不但解决了上文提到的竞态现象，还给我们提供了一个清晰、简洁可控的线程执行模型。
//比如可以使用不同类型的Executor来执行不同类型的工作（io密集型和cpu密集型）。

TEST_F(ThreadedExecutorTest, example) {
  folly::ThreadedExecutor x;
  auto ret = folly::via(&x)
                 .then([&] { return 42; })
                 .then([&](int n) { return folly::to<std::string>(n); })
                 .get();

  EXPECT_EQ("42", ret);
}

TEST_F(ThreadedExecutorTest, dtor_waits) {
  constexpr auto kDelay = std::chrono::milliseconds(100);
  auto x = std::make_unique<folly::ThreadedExecutor>();
  auto fut = folly::via(&*x, [&] { /* sleep override */
                                   std::this_thread::sleep_for(kDelay);
  });
  x = nullptr;

  EXPECT_TRUE(fut.isReady());
}

TEST_F(ThreadedExecutorTest, many) {
  constexpr auto kNumTasks = 1024;
  folly::ThreadedExecutor x;
  auto rets =
      folly::collect(
          folly::gen::range<size_t>(0, kNumTasks) |
          folly::gen::map([&](size_t i) {
            return folly::via(&x).then([=] { return i; }).then([](size_t k) {
              return folly::to<std::string>(k);
            });
          }) |
          folly::gen::as<std::vector>())
          .get();

  EXPECT_EQ("42", rets[42]);
}

TEST_F(ThreadedExecutorTest, many_sleeping_constant_time) {
  constexpr auto kNumTasks = 256;
  constexpr auto kDelay = std::chrono::milliseconds(100);
  folly::ThreadedExecutor x;
  auto rets =
      folly::collect(
          folly::gen::range<size_t>(0, kNumTasks) |
          folly::gen::map([&](size_t i) {
            return folly::via(&x)
                .then([=] {
                  /* sleep override */ std::this_thread::sleep_for(kDelay);
                })
                .then([=] { return i; })
                .then([](size_t k) { return folly::to<std::string>(k); });
          }) |
          folly::gen::as<std::vector>())
          .get();

  EXPECT_EQ("42", rets[42]);
}

TEST_F(ThreadedExecutorTest, many_sleeping_decreasing_time) {
  constexpr auto kNumTasks = 256;
  constexpr auto kDelay = std::chrono::milliseconds(100);
  folly::ThreadedExecutor x;
  auto rets =
      folly::collect(
          folly::gen::range<size_t>(0, kNumTasks) |
          folly::gen::map([&](size_t i) {
            return folly::via(&x)
                .then([=] {
                  auto delay = kDelay * (kNumTasks - i) / kNumTasks;
                  /* sleep override */ std::this_thread::sleep_for(delay);
                })
                .then([=] { return i; })
                .then([](size_t k) { return folly::to<std::string>(k); });
          }) |
          folly::gen::as<std::vector>())
          .get();

  EXPECT_EQ("42", rets[42]);
}
