/*
 * atomicTest.cpp
 *
 *  Created on: 2017年11月1日
 *      Author: chic
 */
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <sstream>
#include <gtest/gtest.h>

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT; //flag处于clear状态，没有被设置过
std::stringstream stream;

void append_number(int x) {
    while (lock_stream.test_and_set()) {
    } //检查并设置是个原子操作，如以前没有设置过则退出循环，每个线程都等待前面一个线程将lock_stream状态清除后跳出循环

    stream << "thread #" << x << '\n';
    lock_stream.clear();
}

//./testSTL --gtest_filter=atomicTest.atomicflag
TEST(atomicTest, atomicflag) {
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(append_number, i));
    for (auto& th : threads)
        th.join();
    std::cout << stream.str();
}

struct Node {
    int value;
    Node* next;
};

/*
    //以下函数可以指定内存序memory_order
    T exchange(T val, memory_order = memory_order_seq_cst) volatile;//将T的值置为val，并返回原来T的值
    T exchange(T val, memory_order = memory_order_seq_cst);
    void store(T val, memory_order = memory_order_seq_cst) volatile;//将T值设为val
    void store(T val, memory_order = memory_order_seq_cst);
    T load(memory_order = memory_order_seq_cst) const volatile;//访问T值
    T load(memory_order = memory_order_seq_cst) const;

bool compare_exchange_weak(T& expected, T val, memory_order = memory_order_seq_cst) volatile;
该函数直接比较原子对象所封装的值与参数 expected 的物理内容，所以某些情况下，
对象的比较操作在使用 operator==() 判断时相等，但 compare_exchange_weak 判断时却可能失败，
因为对象底层的物理内容中可能存在位对齐或其他逻辑表示相同但是物理表示不同的值(比如 true 和 2 或 3，
它们在逻辑上都表示"真"，但在物理上两者的表示并不相同)。可以虚假的返回false(和expected相同)。
若本atomic的T值和expected相同则用val值替换本atomic的T值，返回true;若不同则用本atomic的T值替换expected，返回false。
*/
std::atomic<Node*> list_head(nullptr);
void append(int val) {     // append an element to the list
    Node* newNode = new Node { val, list_head };
    // next is the same as: list_head = newNode, but in a thread-safe way:
    while (!list_head.compare_exchange_weak(newNode->next, newNode)) {
    }
    // (with newNode->next updated accordingly if some other thread just appended another node)
}

//./testSTL --gtest_filter=atomicTest.atomic
TEST(atomicTest, atomic) {
    // spawn 10 threads to fill the linked list:
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread(append, i));
    for (auto& th : threads)
        th.join();
    // print contents:
    for (Node* it = list_head; it != nullptr; it = it->next)
        std::cout << ' ' << it->value;
    std::cout << '\n';
    // cleanup:
    Node* it;

    it = list_head;
    while (it) {
        list_head = it->next;
        delete it;
        it=list_head;
    }
}
