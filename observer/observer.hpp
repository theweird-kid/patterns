#pragma once
#include <string>

// T : the type of object to be observed
template<typename T>
struct Observer
{
    virtual void field_changed(
        T& source, const std::string &field_name
    ) = 0;
};
