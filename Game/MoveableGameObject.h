#pragma once

#include "GameObject.h"

class MoveableGameObject
    : public GameObject
{
public:
    MoveableGameObject(D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));

    D3DXVECTOR3 getPosition();
    D3DXVECTOR3 getDirection();
    D3DXVECTOR3 getUpVector();
    D3DXVECTOR3 getScale();
    float getSpeed();
    void yaw( float radians );
    void pitch( float radians );
    void roll( float radians );
    void setSpeed(float speed);
    void setYawRotationSpeed(float radiansPerSecond);
    void setRollRotationSpeed(float radiansPerSecond);
    void setPitchRotationSpeed(float radiansPerSecond);
    D3DXQUATERNION getRotationQuat();
    virtual void update(float time);
    virtual void changeSpeedBy(float speedDelta);

    D3DXMATRIX* generateTransformationMatrix(D3DXMATRIX *matrix);

    void setPosition(D3DXVECTOR3 position);
    void setScale(D3DXVECTOR3 scale);
    void setScale(float x, float y, float z);
    void setDirection(D3DXVECTOR3 direction);
    void setFixedDirection(bool fixedDirection);

private:
    void changeOrientation(D3DXVECTOR3 rotationVector, float radians);
    void computeDirectionVectors();
    void updateRotationSpeeds(float time);
    void updatePosition(float time);

    static const D3DXVECTOR3 basisDirectionVector;
    static const D3DXVECTOR3 basisUpVector;

    D3DXVECTOR3 right;
    D3DXVECTOR3 up;
    D3DXVECTOR3 direction;
    D3DXVECTOR3 position;
    D3DXVECTOR3 scale;
    D3DXQUATERNION rotation;
    float yawRotationSpeed;
    float rollRotationSpeed;
    float pitchRotationSpeed;
    float speed;
    bool fixedDirection;
};

