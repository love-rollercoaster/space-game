#include "Laser.h"


Laser::Laser(D3DXQUATERNION rotation, D3DXVECTOR3 position, D3DXVECTOR3 direction) 
    : MoveableGameObject(position)
    , lifetimeLeft(LASER_LIFETIME_MS)
    , lastPosition(position)
{
    setDirection(direction);
    setRotation(rotation);
    setMaxSpeed(LASER_MAX_SPEED);
    setSpeed(LASER_SPEED);
}


Laser::~Laser(void)
{
}

void Laser::update(float time)
{
    lifetimeLeft -= time;
    lastPosition = getPosition();
    if (physicsComponent != NULL) {
        physicsComponent->update(*this, time);
    }
}

bool Laser::isExpired()
{
    return lifetimeLeft <= 0.0f;
}

D3DXVECTOR3 Laser::getLastPosition() {
    return lastPosition;
}
