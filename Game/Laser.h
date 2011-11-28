#pragma once
#include "gameobject.h"
#include "MoveableGameObject.h"

#define LASER_LIFETIME_MS 2000.0f
#define LASER_SPEED 150.0f
#define LASER_MAX_SPEED 5000.0f

class Laser :
    public MoveableGameObject
{
public:
    Laser(D3DXQUATERNION rotation, D3DXVECTOR3 position, D3DXVECTOR3 direction);
    ~Laser(void);

    virtual void update(float time);
    virtual bool isExpired();
    D3DXVECTOR3 getLastPosition();

private:
    D3DXVECTOR3 lastPosition;
    float lifetimeLeft;

};

