#pragma once
#include "physicscomponent.h"
#include "MoveableGameObject.h"


class MoveableObjectPhysicsComponent :
    public PhysicsComponent
{
public:
    MoveableObjectPhysicsComponent(void);
    ~MoveableObjectPhysicsComponent(void);

    virtual void update(GameObject &gameObject, float time);

protected:
    virtual void updateRotationSpeeds(MoveableGameObject &obj, float time);
    virtual void updatePosition(MoveableGameObject &obj, float time);
};

