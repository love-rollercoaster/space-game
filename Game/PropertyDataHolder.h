#pragma once

// Reference:
// http://learningcppisfun.blogspot.com/2007/09/boostany.html

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