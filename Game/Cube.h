#pragma once

#include "GameObject.h"

class Cube
    : public GameObject
{
public:
    Cube(void);

    D3DXVECTOR3 getPosition();
    D3DXVECTOR3 getScale();
    D3DXVECTOR3 getVelocity();

    void setPosition(D3DXVECTOR3 position);
    void setScale(D3DXVECTOR3 scale);
    void setScale(float x, float y, float z);


private:
    D3DXVECTOR3 position;
    D3DXVECTOR3 scale;
    
};

