//
// Created by Platholl on 14/07/2020.
//

#include <iostream>

#include "Raytracer/Core/ThreadPool.hpp"

namespace rt
{
    ThreadPool::ThreadPool(const uint32_t threadNumber)
    {
        m_workers.reserve(threadNumber);
        for(uint32_t i = 0; i < threadNumber; i++)
        {
            m_workers.push_back(std::thread([this]()
            {
                size_t taskNumber = 0;
                while(m_shouldRun || taskNumber > 0)
                {
                    m_tasksLocker.lock();
                    if(!m_tasks.empty())
                    {
                        auto task = m_tasks.top();
                        m_tasks.pop();
                        m_tasksLocker.unlock();
                        try
                        {
                            task();
                        }
                        catch (const std::exception& e)
                        {
                            std::cerr << e.what() << std::endl;
                        }
                    }
                    else
                    {
                        m_tasksLocker.unlock();
                    }
                    std::lock_guard tasksGuard{m_tasksLocker};
                    taskNumber = m_tasks.size();
                }
            }));
        }
    }

    void ThreadPool::Join()
    {
        for(auto& t : m_workers)
        {
            if(t.joinable())
                t.join();
            else
                t.detach();
        }
    }

    ThreadPool::~ThreadPool()
    {
        m_shouldRun = false;
        Join();
    }
}