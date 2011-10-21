#pragma once

// Reference:
// http://learningcppisfun.blogspot.com/2007/09/boostany.html

#include "BasePropertyHolder.h"
#include "PropertyDataHolder.h"

class Property
{
public:
    template<typename T>
    Property( const T& t )
        : data( new PropertyDataHolder<T>(t) )
    {
    }

    ~Property()
    {
        delete data;
    }

private:
    BasePropertyHolder* data;
};
