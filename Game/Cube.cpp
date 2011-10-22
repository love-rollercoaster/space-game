#include "Cube.h"

Cube::Cube(void)
    : position(0.0f, 0.0f, 0.0f)
    , scale(1.0f, 1.0f, 1.0f)
    , GameObject()
{
}

D3DXVECTOR3 Cube::getPosition()
{
    return position;
}

D3DXVECTOR3 Cube::getScale()
{
    return scale;
}

void Cube::setPosition( D3DXVECTOR3 position )
{
    this->position = position;
}

void Cube::setScale( D3DXVECTOR3 scale )
{
    this->scale = scale;
}

void Cube::setScale( float x, float y, float z )
{
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;
}