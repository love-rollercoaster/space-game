#include "Obstacle.h"

Obstacle::Obstacle(D3DXVECTOR3 position, D3DXVECTOR3 scale) :
    position(position), scale(scale), GameObject()
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

D3DXMATRIX *Obstacle::generateTransformationMatrix(D3DXMATRIX *matrix)
{
    D3DXMATRIX matScale, matTranslate, matRotate;
    D3DXMatrixIdentity(matrix);

    D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

    //TODO add rotation

    D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
    D3DXMatrixMultiply(matrix, &matScale, &matTranslate);
    return matrix;
}