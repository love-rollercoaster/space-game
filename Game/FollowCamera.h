#pragma once
#include "camera.h"
#include "MoveableGameObject.h"
class FollowCamera :
    public Camera
{
public:
    FollowCamera(MoveableGameObject *object);
    ~FollowCamera(void);

    virtual D3DXMATRIX getViewMatrix() const;
    virtual void yaw( float radians );
    virtual void pitch( float radians );
    virtual void roll( float radians );
    virtual void update(float time);
    virtual float getPitchAngle() const;
    virtual float getYawAngle() const;
    virtual D3DXVECTOR3 getPosition() const;
    void setOffset(D3DXVECTOR3 offset);

    void setGameObject(MoveableGameObject *object);

private:
    D3DXVECTOR3 offset; // needs better name, what kind of offset?
    MoveableGameObject *object;
};

