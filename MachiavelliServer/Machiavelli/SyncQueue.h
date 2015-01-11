//
//  SyncQueue.h
//  Machiavelli
//
//  Created by Alex Nagelkerke on 17-12-14.
//  Copyright (c) 2014 Alex Nagelkerke. All rights reserved.
//

#ifndef Machiavelli_SyncQueue_h
#define Machiavelli_SyncQueue_h

#include <mutex>
#include <condition_variable>
#include <list>
#include <future>
#include <thread>

template<typename T>
class Sync_queue {
public:
    void put(const T& val);
    void get(T& val);
    
private:
    std::mutex mtx;
    std::condition_variable cond;
    std::list<T> q;
};

template<typename T>
void Sync_queue<T>::put(const T& val)
{
    std::lock_guard<std::mutex> lck{ mtx };
    q.push_back(val);
    cond.notify_one();
}

template<typename T>
void Sync_queue<T>::get(T& val)
{
    std::unique_lock<std::mutex> lck{ mtx };
    cond.wait(lck, [this]{ return !q.empty(); });
    val = q.front();
    q.pop_front();
}

#endif
