#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

// Forward Declaration
template<typename> struct Observer;

// CRTP -> Curiously recurring template pattern
template<typename T>
struct ThreadSafeObservable
{
    // vector of observer pointers
    std::vector<Observer<T>*> observers;

    typedef std::mutex mutex_t;
    mutex_t mtx;
public:

    void notify(T& source, const std::string &field_name)
    {
        std::scoped_lock<mutex_t> lock{mtx};
        for(auto observer : observers) {
            if(observer)
                observer->field_changed(source, field_name);
            else {
                observers.erase(
                    std::remove(observers.begin(), observers.end(), &observer),
                    observers.end()
                );
            }
        }
    }

    void subscribe(Observer<T> &observer)
    {
        std::scoped_lock<mutex_t> lock{mtx};
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T> &observer)
    {
        /*
            to prevent recursive locking, if in notify we try to access unsubscribe it would have resulted
            in a deadlock
        */
        auto it = std::find(std::begin(observers), std::end(observers), &observer);
        if(it != std::end(observers)) *it = nullptr;
        // std::scoped_lock<mutex_t> lock{mtx};
        // observers.erase(
        //     std::remove(observers.begin(), observers.end(), &observer),
        //     observers.end()
        // );

        // std::cout << "observer " << &observer << " unsubscribed\n";
    }
};
