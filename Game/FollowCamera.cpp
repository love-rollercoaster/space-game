#include "FollowCamera.h"

FollowCamera::FollowCamera(MoveableGameObject *object) 
    : object(object)
    , offset(0.0f, 0.3f,-3.0f)
{
}

FollowCamera::~FollowCamera(void)
{
}

void FollowCamera::setGameObject(MoveableGameObject *object)
{
    this->object = object;
}

D3DXMATRIX FollowCamera::getViewMatrix() const
{
    D3DXMATRIX view;
    D3DXVECTOR3 up, direction, position;
    position = getPosition();
    direction = object->getDirection();
    up = object->getUpVector();

    D3DXMatrixLookAtLH(&view, &position, &(direction+position), &up);
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
    D3DXQUATERNION rotationQuat = object->getRotationQuat();
    D3DXMATRIX rotationMatrix;
    D3DXVECTOR3 offsetTransformed;
    D3DXVECTOR3 position = object->getPosition();
    D3DXMatrixRotationQuaternion(&rotationMatrix, &rotationQuat);
    D3DXVec3TransformCoord(&offsetTransformed, &offset, &rotationMatrix);
    
    return object->getPosition() + offsetTransformed; // TODO update with offset
}

void FollowCamera::setOffset(D3DXVECTOR3 offset)
{
    this->offset = offset;
}