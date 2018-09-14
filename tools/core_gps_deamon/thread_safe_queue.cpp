/*
    QueuePtr - Self returning buffer pool
    Copyright (C) 2014  Chris Desjardins
    http://blog.chrisd.info cjd@chrisd.info
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
** This provides a thread safe queue
*/

#ifndef CB_THREAD_SAFE_QUEUE_Hxx
#define CB_THREAD_SAFE_QUEUE_Hxx

#include <list>
#include <mutex>
#include <condition_variable>

/*
** On the wait functions in this class if timeout == -1, then wait forever...
** When dequeing a batch of messages, the return code is the total number of bytes
** in all messages in the batch.
*/

template <class T> class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
        : _queue(),
        _queueMutex(),
        _msgNotification(),
        _numEnqueued(0)
    {
    }

    virtual ~ThreadSafeQueue()
    {
    }

    virtual void enqueue(const T& data)
    {
        { // create a new scope for the mutex
            std::unique_lock<std::mutex> lock(_queueMutex);
            pushData(data);
            _msgNotification.notify_all();
        }
    }

    virtual bool dequeue(T& data, const int msTimeout = 0)
    {
        bool ret = false;
        { // create a new scope for the mutex
            std::unique_lock<std::mutex> lock(_queueMutex);
            waitForData(lock, msTimeout);
            ret = popData(data);
        }
        return ret;
    }

    // Dequeue everything
    virtual size_t dequeue(std::vector<T>& dataVec, const int msTimeout = 0)
    {
        size_t size = 0;
        { // create a new scope for the mutex
            std::unique_lock<std::mutex> lock(_queueMutex);
            waitForData(lock, msTimeout);
            size = popData(dataVec);
        }
        return size;
    }

    size_t size() const
    {
        return _numEnqueued;
    }

    /*
    ** This function allows you to perform operations on the
    ** vector in a thread safe way. The functor is a function
    ** with the following signature:
    ** int func(std::list<T> &);
    ** The return value is the number of elements added or removed
    ** from the list, for example if 5 elements were removed
    ** and 3 new elements were added then the return value should
    ** be -2.
    */
    template <typename Functor> void iterate(Functor functor)
    {
        { // create a new scope for the mutex
            std::unique_lock<std::mutex> lock(_queueMutex);
            // the return value of this functor is added to the _numEnqueued
            // so if you add buffers then return the number of buffers added
            // or if you remove buffers then return -number of buffers removed
            int numChanged = functor(_queue);
            _numEnqueued += numChanged;
        }
    }

protected:

    void waitForData(std::unique_lock<std::mutex>& lock, const int msTimeout)
    {
        if (msTimeout != 0)
        {
            // This function assumes that _queueMutex is locked already!
            std::chrono::system_clock::time_point timeLimit = std::chrono::system_clock::now() +
                                                              std::chrono::milliseconds(msTimeout);
            while (_queue.empty() == true)
            {
                // if timeout is specified, then wait until the time is up
                // otherwise wait forever (forever is msTimeout = -1)
                if (msTimeout > 0)
                {
                    _msgNotification.wait_until(lock, timeLimit);
                    if (std::chrono::system_clock::now() >= timeLimit)
                    {
                        break;
                    }
                }
                else
                {
                    _msgNotification.wait(lock);
                }
            }
        }
    }

    void pushData(const T& data)
    {
        // This function assumes that _queueMutex is locked already!
        _queue.push_back(data);
        _numEnqueued++;
    }

    bool popData(T& data)
    {
        // This function assumes that _queueMutex is locked already!
        bool ret = false;
        if (_queue.empty() == false)
        {
            data = _queue.front();
            _queue.pop_front();
            _numEnqueued--;
            ret = true;
        }
        return ret;
    }

    size_t popData(std::vector<T>& dataVec)
    {
        // This function assumes that _queueMutex is locked already!
        size_t size = 0;
        T data;
        while (popData(data) == true)
        {
            size += sizeOfData(data);
            dataVec.push_back(data);
        }
        return size;
    }

    virtual size_t sizeOfData(const T&) const
    {
        return sizeof(T);
    }

    std::list<T> _queue;
    std::mutex _queueMutex;
    std::condition_variable _msgNotification;
    size_t _numEnqueued;
};

#endif
