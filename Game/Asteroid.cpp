#include "Asteroid.h"
#include "MoveableGameObject.h"

Asteroid::Asteroid(D3DXVECTOR3 position, D3DXVECTOR3 scale) 
    : MoveableGameObject(position, scale)
{
}

Asteroid::~Asteroid(void)
{
}
