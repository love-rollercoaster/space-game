#pragma once

#include "GameObject.h"

class Obstacle
    : public GameObject
{
public:
    Obstacle(D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));

    D3DXVECTOR3 getPosition();
    D3DXVECTOR3 getScale();
    D3DXVECTOR3 getVelocity();

    D3DXMATRIX *generateTransformationMatrix(D3DXMATRIX *matrix);

    void setPosition(D3DXVECTOR3 position);
    void setScale(D3DXVECTOR3 scale);
    void setScale(float x, float y, float z);

private:
    D3DXVECTOR3 position;
    D3DXVECTOR3 scale;
    
};

