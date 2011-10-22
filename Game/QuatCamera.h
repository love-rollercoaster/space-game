#pragma once

#include "Camera.h"

#include <d3dx9.h>

class QuatCamera : public Camera
{
public:
    QuatCamera(void);
    virtual ~QuatCamera(void);

    virtual void yaw( float radians );
    virtual void pitch( float radians );
    virtual void roll( float radians );
    virtual void update(time_t time);

    virtual float getPitchAngle() const;
    virtual float getYawAngle() const;

private:
    void updateOrientation(D3DXVECTOR3 rotVector, float angleRad);
    void updateDirectionVectors();
    void updateViewMatrix();
    float computeAngleBetweenNormal(const D3DXVECTOR3 *vec1, const D3DXVECTOR3 *vec2) const;

    static const D3DXVECTOR3 basisDirectionVector;
    static const D3DXVECTOR3 basisUpVector;

    D3DXQUATERNION rotQuat;

};

