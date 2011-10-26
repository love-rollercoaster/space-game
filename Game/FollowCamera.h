#pragma once
#include "camera.h"
#include "MoveableGameObject.h"
#include <queue>
using std::queue;

#define CAMERA_CACHE_SIZE 10
#define DEFAULT_FOV_DEGREES 45.0f
#define MAX_FOV_DEGREES 70.0f

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
    void calculateNewFov();
    
    template<class T>
    class Cache {
    public:
        Cache(unsigned int capacity);
        void push(T item);
        T poll() const;
        void clear();
    private:
        queue<T> history;
        unsigned int capacity;
    };

    D3DXVECTOR3 offset;
    MoveableGameObject *obj;
    bool firstPersonCamera;
    float oldObjSpeed;
    Cache<D3DXQUATERNION> pastRotations;
};

