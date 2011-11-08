#pragma once
#include "moveableobjectphysicscomponent.h"
#include "Asteroid.h"
#include "Laser.h"

class LaserPhysicsComponent :
    public MoveableObjectPhysicsComponent
{
public:
    LaserPhysicsComponent(void);
    ~LaserPhysicsComponent(void);

    bool testIntersectionWithAsteroid(Laser &laser, Asteroid &asteroid);

protected:
    float getAsteroidBoundingSphereRadius(Asteroid &asteroid);
};

