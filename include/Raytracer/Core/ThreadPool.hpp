//
// Created by Platholl on 14/07/2020.
//

#ifndef RAYTRACER_THREADPOOL_HPP
#define RAYTRACER_THREADPOOL_HPP

#include <atomic>
#include <functional>
#include <future>
#include <mutex>
#include <stack>
#include <thread>
#include <vector>

namespace rt
{
    // Based on https://vorbrodt.blog/2019/02/12/simple-thread-pool/
    using Task = std::function<void()>;

    class ThreadPool
    {
    public:
        ThreadPool(uint32_t threadNumber = std::thread::hardware_concurrency());

        template<class Function, class... Args>
        auto AddTask(Function&& task, Args&&... args) -> std::future<typename std::invoke_result<Function, Args...>::type>;

        void Join();

        ~ThreadPool();

    private:
        std::mutex m_tasksLocker;
        std::stack<Task> m_tasks;

        std::atomic<bool> m_shouldRun = true;

        std::vector<std::thread> m_workers;
    };

    template<class Function, class... Args>
    auto ThreadPool::AddTask(Function&& function, Args&&... args) -> std::future<typename std::invoke_result<Function, Args...>::type>
    {
        using ReturnType = typename std::invoke_result<Function, Args...>::type;
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<Function>(function), std::forward<Args>(args)...));
        std::future<ReturnType> res = task->get_future();

        m_tasksLocker.lock();
        m_tasks.push([task]()
        {
            (*task)();
        });
        m_tasksLocker.unlock();

        return res;
    }
}

#endif //RAYTRACER_THREADPOOL_HPP
