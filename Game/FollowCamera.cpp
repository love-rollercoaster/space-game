#include "FollowCamera.h"

FollowCamera::FollowCamera(MoveableGameObject *object) 
    : obj(object), offset(0.0f, 1.0f,-3.0f), firstPersonCamera(false),
    pastRotations(CAMERA_CACHE_SIZE)
{
}

FollowCamera::~FollowCamera(void)
{
}

void FollowCamera::setGameObject(MoveableGameObject *object)
{
    this->obj = object;
}

D3DXMATRIX FollowCamera::getViewMatrix() const
{
    D3DXMATRIX view;
    D3DXVECTOR3 up, dir, cameraPos, objPos;
    cameraPos = getPosition();
    objPos = obj->getPosition();
    dir = obj->getDirection();
    up = obj->getUpVector();

    D3DXMatrixLookAtLH(&view, &cameraPos, &(dir+objPos), &up);
    return view;
}

void FollowCamera::yaw( float radians )
{
}

void FollowCamera::pitch( float radians )
{
}

void FollowCamera::roll( float radians )
{
}

void FollowCamera::update(float time)
{
    pastRotations.push(obj->getRotationQuat());
}

float FollowCamera::getPitchAngle() const
{
    return 0.0f;
}

float FollowCamera::getYawAngle() const
{
    return 0.0f;
}

D3DXVECTOR3 FollowCamera::getPosition() const {
    if (firstPersonCamera) {
        return obj->getPosition();
    }
    D3DXQUATERNION quat = pastRotations.poll();
    D3DXMATRIX rotMat;
    D3DXVECTOR3 offsetTransformed;
    D3DXVECTOR3 pos = obj->getPosition();
    D3DXMatrixRotationQuaternion(&rotMat, &quat);
    D3DXVec3TransformCoord(&offsetTransformed, &offset, &rotMat);
    return obj->getPosition() + offsetTransformed;
}

void FollowCamera::setOffset(D3DXVECTOR3 offset)
{
    this->offset = offset;
}

void FollowCamera::setFirstPersonCamera()
{
    this->firstPersonCamera = true;
}

void FollowCamera::setThirdPersonCamera()
{
    this->firstPersonCamera = false;
}

void FollowCamera::toggleCameraMode()
{
    this->firstPersonCamera = !this->firstPersonCamera;
}

/*
 * Rotation cache stuff starts here
 */
FollowCamera::RotationCache::RotationCache(unsigned int capacity) 
    : capacity(capacity)
{}

void FollowCamera::RotationCache::push(D3DXQUATERNION quat)
{
    history.push(quat);
    while (history.size() > capacity) {
        history.pop();
    }
}

D3DXQUATERNION FollowCamera::RotationCache::poll() const
{
    if (history.empty()) {
        return D3DXQUATERNION();
    }
    return history.front();
}