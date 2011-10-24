#include "FollowCamera.h"

FollowCamera::FollowCamera(MoveableGameObject *object) 
    : obj(object), offset(0.0f, 0.3f,-3.0f)
{
}


FollowCamera::~FollowCamera(void)
{
}

void FollowCamera::setGameObject(MoveableGameObject *obj)
{
    this->obj = obj;
}

D3DXMATRIX FollowCamera::getViewMatrix() const
{
    D3DXMATRIX view;
    D3DXVECTOR3 up, dir, pos;
    pos = getPosition();
    dir = obj->getDirection();
    up = obj->getUpVector();

    D3DXMatrixLookAtLH(&view, &pos, &(dir+pos), &up);
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
    D3DXQUATERNION quat = obj->getRotationQuat();
    D3DXMATRIX rotMat;
    D3DXVECTOR3 offsetTransformed;
    D3DXVECTOR3 pos = obj->getPosition();
    D3DXMatrixRotationQuaternion(&rotMat, &quat);
    D3DXVec3TransformCoord(&offsetTransformed, &offset, &rotMat);
    return obj->getPosition() + offsetTransformed; //TODO update with offset
}

void FollowCamera::setOffset(D3DXVECTOR3 offset)
{
    this->offset = offset;
}