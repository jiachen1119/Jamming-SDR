/*!
 * \file concurrent_queue.h
 * \brief Interface of a thread-safe std::queue
 * \author Javier Arribas, 2011. jarribas(at)cttc.es
 */

#ifndef GNSS_SDR_CONCURRENT_QUEUE_H
#define GNSS_SDR_CONCURRENT_QUEUE_H

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

/** \addtogroup Core
 * \{ */
/** \addtogroup Core_Receiver
 * \{ */


template <typename Data>

/*!
 * \brief This class implements a thread-safe std::queue
 *
 * Thread-safe object queue which uses the library
 * boost_thread to perform MUTEX based on the code available at
 * https://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
 */
class Concurrent_Queue
{
public:
    void push(Data const& data)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        the_queue.push(data);
        lock.unlock();
        the_condition_variable.notify_one();
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        return the_queue.empty();
    }

    size_t size() const
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        return the_queue.size();
    }

    void clear()
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        the_queue = std::queue<Data>();
    }

    bool try_pop(Data& popped_value)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        if (the_queue.empty())
            {
                return false;
            }
        popped_value = the_queue.front();
        the_queue.pop();
        return true;
    }

    void wait_and_pop(Data& popped_value)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        while (the_queue.empty())
            {
                the_condition_variable.wait(lock);
            }
        popped_value = the_queue.front();
        the_queue.pop();
    }

    bool timed_wait_and_pop(Data& popped_value, int wait_ms)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        if (the_queue.empty())
            {
                the_condition_variable.wait_for(lock, std::chrono::milliseconds(wait_ms));
                if (the_queue.empty())
                    {
                        return false;
                    }
            }
        popped_value = the_queue.front();
        the_queue.pop();
        return true;
    }

private:
    std::queue<Data> the_queue;
    mutable std::mutex the_mutex;
    std::condition_variable the_condition_variable;
};


/** \} */
/** \} */
#endif  // GNSS_SDR_CONCURRENT_QUEUE_H
