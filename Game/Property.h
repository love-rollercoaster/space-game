#pragma once

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
