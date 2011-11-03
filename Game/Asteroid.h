#pragma once

#include "AsteroidGraphicsComponent.h"

class MoveableGameObject;
class GraphicsComponent;
class GraphicsEngine;
class GameEngine;

class Asteroid : public MoveableGameObject
{
public:
    Asteroid(D3DXVECTOR3 position, D3DXVECTOR3 scale);
    ~Asteroid(void);

private:
};

