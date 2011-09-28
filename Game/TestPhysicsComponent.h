#pragma once

#include "PhysicsComponent.h"
#include "GameObject.h"

class TestPhysicsComponent :
    public PhysicsComponent
{
public:
    TestPhysicsComponent(void);
    ~TestPhysicsComponent(void);

    void update(GameObject &gameObject, time_t time);
};
