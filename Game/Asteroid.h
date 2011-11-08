#pragma once

#include "AsteroidGraphicsComponent.h"

class MoveableGameObject;
class GraphicsComponent;
class GraphicsEngine;
class GameEngine;

#define ASTEROID_BASE_X 0.959375f
#define ASTEROID_BASE_Y 1.49479f
#define ASTEROID_BASE_Z 0.693766f

class Asteroid : public MoveableGameObject
{
public:
    Asteroid(D3DXVECTOR3 position, D3DXVECTOR3 scale);
    ~Asteroid(void);

private:
};

