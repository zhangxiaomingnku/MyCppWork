#include <folly/futures/Future.h>
#include <folly/futures/Promise.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "thread/ThreadPool.h"

#define LOG_LINE(msg) std::cout << msg << std::endl;

/*
bazel build //:test_aync_use_promoise
./bazel-bin/test_aync_use_promoise

*/

void func(folly::Promise<int> * p) {
    LOG(ERROR) << "func in thread " << std::this_thread::get_id();
    LOG_LINE("begin func");
    p->setValue(3);
    LOG_LINE("p set value");
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    LOG_LINE("end func");
}

int main(int argc, char *argv[]) {
    ThreadPool thread_pool(3);
    thread_pool.start();

    folly::Promise<int> p;

    auto task = std::bind(func, &p);

    thread_pool.add_task(task);

    p.getFuture()
            .within(std::chrono::milliseconds(1000), std::runtime_error("timeout"))  // 但这里p的回调设置的超时时间为1000
            .then([](folly::Try<int> &t) {
                if (t.hasException()) {
                    LOG(ERROR) << "has exception " << t.exception().what().toStdString();
                    return;
                }
                LOG(ERROR) << "in thread " << std::this_thread::get_id();
                LOG(ERROR) << "t.value() " << t.value();
            });

    thread_pool.stop();




    // // t线程等待5000ms后才会对p进行setValue
    // auto lambda_task = [&p]() {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(5000));  // done in thread
    //     p.setValue(3);
    //     LOG(ERROR) << "set value to pomise";
    // };
    // std::thread t(lambda_task);

    // p.getFuture()
    // .within(std::chrono::milliseconds(1000), std::runtime_error("timeout"))  // 但这里p的回调设置的超时时间为1000
    // .then([](folly::Try<int> &t) {
    //     if (t.hasException()) {
    //         LOG(ERROR) << "has exception " << t.exception().what().toStdString();
    //         return;
    //     }
    //     LOG(ERROR) << "t.value() " << t.value();
    // });

    // t.join();
    return 0;
}