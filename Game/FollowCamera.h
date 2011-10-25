#pragma once
#include "camera.h"
#include "MoveableGameObject.h"
#include <queue>
using std::queue;

#define CAMERA_CACHE_SIZE 10

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
    void setFirstPersonCamera();
    void setThirdPersonCamera();
    void toggleCameraMode();

    void setGameObject(MoveableGameObject *object);

private:
    class RotationCache {
    public:
        RotationCache(unsigned int capacity);
        void push(D3DXQUATERNION quat);
        D3DXQUATERNION poll() const;
    private:
        queue<D3DXQUATERNION> history;
        unsigned int capacity;
    };

    D3DXVECTOR3 offset;
    MoveableGameObject *obj;
    bool firstPersonCamera;
    RotationCache pastRotations;
};

