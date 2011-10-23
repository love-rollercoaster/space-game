#include "Obstacle.h"

Obstacle::Obstacle(void)
    : position(0.0f, 0.0f, 0.0f)
    , scale(1.0f, 1.0f, 1.0f)
    , GameObject()
{
}

D3DXVECTOR3 Obstacle::getPosition()
{
    return position;
}

D3DXVECTOR3 Obstacle::getScale()
{
    return scale;
}

void Obstacle::setPosition( D3DXVECTOR3 position )
{
    this->position = position;
}

void Obstacle::setScale( D3DXVECTOR3 scale )
{
    this->scale = scale;
}

void Obstacle::setScale( float x, float y, float z )
{
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;
}