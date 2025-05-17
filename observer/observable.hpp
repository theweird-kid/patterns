#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Forward Declaration
template<typename> struct Observer;

// CRTP -> Curiously recurring template pattern
template<typename T>
struct Observable
{
    // vector of observer pointers
    std::vector<Observer<T>*> observers;
public:

    void notify(T& source, const std::string &field_name)
    {
        for(auto observer : observers) {
            observer->field_changed(source, field_name);
        }
    }

    void subscribe(Observer<T> &observer)
    {
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T> &observer)
    {
        observers.erase(
            std::remove(observers.begin(), observers.end(), &observer),
            observers.end()
        );

        std::cout << "observer " << &observer << " unsubscribed\n";
    }
};
