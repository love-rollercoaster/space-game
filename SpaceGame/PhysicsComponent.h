#pragma once
class PhysicsComponent
{
public:
    PhysicsComponent(void);
    ~PhysicsComponent(void);

    virtual void update(GameObject &gameObject, time_t time) = 0;
};