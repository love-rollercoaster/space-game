#pragma once

#include "GameObject.h"

class MoveableGameObject
    : public GameObject
{
public:
    MoveableGameObject(D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));

    D3DXVECTOR3 getPosition();
    D3DXVECTOR3 getScale();
    D3DXVECTOR3 getVelocity();
    void yaw( float radians );
    void pitch( float radians );
    void roll( float radians );
    void setSpeed(float speed);
    void setYawRotationSpeed(float radsPerSec);
    void setRollRotationSpeed(float radsPerSec);
    void setPitchRotationSpeed(float radsPerSec);
    D3DXQUATERNION getRotationQuat();
    virtual void update(float time);

    D3DXMATRIX *generateTransformationMatrix(D3DXMATRIX *matrix);

    void setPosition(D3DXVECTOR3 position);
    void setScale(D3DXVECTOR3 scale);
    void setScale(float x, float y, float z);

private:
    void updateOrientation(D3DXVECTOR3 rotVector, float angleRad);
    void updateDirectionVectors();

    static const D3DXVECTOR3 basisDirectionVector;
    static const D3DXVECTOR3 basisUpVector;

    D3DXVECTOR3 right;
    D3DXVECTOR3 up;
    D3DXVECTOR3 direction;
    D3DXVECTOR3 position;
    D3DXVECTOR3 scale;
    D3DXQUATERNION rotation;
    float yawRotateSpeed;
    float rollRotateSpeed;
    float pitchRotateSpeed;
    float speed;    
};

