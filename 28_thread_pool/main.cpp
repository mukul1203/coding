#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>

// thread pool
//  n threads
//  a thread safe task queue - dispatcher to dispatch
//  threads wait on a condition variable - queue is non empty, only after finding the queue is currently empty
//  dispatcher dispatches the task to queue and notifies one thread to wake up and pull the task
//  if all threads are busy, and queue piles up, the thread which finishes a current task should
//  look at the queue, if not empty, should pull the next task.

// VERY ROUGH, QUICK AND DIRTY SOLUTION

struct task
{
    std::function<void()> f;
    task(std::function<void()> t) : f(std::move(t)) {}
    void run()
    {
        f();
    }
};

struct task_queue
{
    std::queue<task> q;
    std::mutex m;
    void enqueue(task t)
    {
        std::unique_lock<std::mutex> lk(m);
        q.push(std::move(t));
    }

    task dequeue()
    {
        std::unique_lock<std::mutex> lk(m);
        task t = q.front();
        q.pop();
        return t;
    }

    bool is_empty()
    {
        std::unique_lock<std::mutex> lk(m);
        return q.empty();
    }
};

struct my_thread_pool
{
    std::vector<std::thread> threads;
    std::vector<bool> done;
    task_queue q;
    std::condition_variable cv;
    std::mutex m;
    my_thread_pool(int n)
    {
        // n threads
        for (int i = 0; i < n; ++i)
        {
            done.push_back(false);
            threads.emplace_back(std::thread([&, i]()
                                             {
                while (true) {
                {
                    std::unique_lock<std::mutex> lk(m);
                    cv.wait(lk, [&]()
                            { return !q.is_empty() || done[i]; });
                    if (done[i] && q.is_empty())
                        break;
                }
                task t = q.dequeue();
                std::cout << " thread " << std::this_thread::get_id() << std::endl;
                t.run();
            } }));
        }
    }
    void dispatch(task t)
    {
        q.enqueue(std::move(t));
        cv.notify_one();
    }

    ~my_thread_pool()
    {
        for (int i = 0; i < threads.size(); ++i)
        {
            {
                std::unique_lock<std::mutex> lk(m);
                done[i] = true;
                cv.notify_all();
            }
            threads[i].join();
        }
    }
};

#include "test_framework/catch_amalgamated.hpp"
TEST_CASE("thread pool")
{
    my_thread_pool p(3);
    p.dispatch(task([]()
                    {
                        std::cout << "task 1" << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(3)); }));
    p.dispatch(task([]()
                    {
                        std::cout << "task 2" << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    p.dispatch(task([]()
                    {
                        std::cout << "task 3" << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(2)); }));
}