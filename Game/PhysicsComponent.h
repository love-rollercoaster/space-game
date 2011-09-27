#pragma once

#include <time.h>
class GameObject;

class PhysicsComponent
{
public:
    virtual void update(GameObject &gameObject, time_t time) = 0;
};