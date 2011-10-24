#include "MoveableGameObject.h"

MoveableGameObject::MoveableGameObject(D3DXVECTOR3 position, D3DXVECTOR3 scale) :
    position(position), scale(scale), GameObject()
{
    D3DXQuaternionIdentity(&rotation);
    D3DXQuaternionNormalize(&rotation, &rotation);
}

D3DXVECTOR3 MoveableGameObject::getPosition()
{
    return position;
}

D3DXVECTOR3 MoveableGameObject::getScale()
{
    return scale;
}

void MoveableGameObject::setPosition( D3DXVECTOR3 position )
{
    this->position = position;
}

void MoveableGameObject::setScale( D3DXVECTOR3 scale )
{
    this->scale = scale;
}

void MoveableGameObject::setScale( float x, float y, float z )
{
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;
}

D3DXMATRIX *MoveableGameObject::generateTransformationMatrix(D3DXMATRIX *matrix)
{
    D3DXMATRIX matScale, matTranslate, matRotate;
    D3DXMatrixIdentity(matrix);

    D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

    //TODO add rotation

    D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
    D3DXMatrixMultiply(matrix, &matScale, &matTranslate);
    return matrix;
}