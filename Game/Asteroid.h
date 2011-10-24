#pragma once
#include "MoveableGameObject.h"

#define MIN_SCALE 0.3f

class Asteroid :
    public MoveableGameObject
{
public:
    Asteroid(D3DXVECTOR3 position, D3DXVECTOR3 scale);
    ~Asteroid(void);
};

