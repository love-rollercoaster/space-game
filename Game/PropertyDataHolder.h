#pragma once

#include "BasePropertyHolder.h"

template<typename T>
class PropertyDataHolder : public Property
{
public:
    PropertyDataHolder(const T& t)
        : t(t)
    {

    }
private:
    T t;
};