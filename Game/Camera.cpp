#include "Camera.h"

Camera::Camera()
    : maxPitchAngle(D3DXToRadian( 89.0f ))
    , maxSpeed(10.0f)
    , minSpeed(0.0f)
    , yInverted(false)
    , yMovementEnabled(true)
    , position(0.0f, 0.0f, 0.0f)
    , speed(0.0f)
    , lookDirection(0.0f, 0.0f, 1.0f)
    , ignoreMaxPitchAngle(false)
{
    createProjectionMatrix(D3DXToRadian(45), 1.333333333f, 0.1f, 5000.0f );
}

void Camera::createProjectionMatrix( float fov, float aspect, float nearPlane, float farPlane )
{
    this->fov       = fov;
    this->aspect    = aspect;
    this->nearPlane = nearPlane;
    this->farPlane  = farPlane;
    D3DXMatrixPerspectiveFovLH( &projection, fov, aspect, nearPlane, farPlane );
}

void Camera::setSpeed(float speed)
{
    this->speed = speed;
    keepSpeedBounds();
}

void Camera::changeSpeedBy(float dSpeed) 
{
    this->speed += dSpeed;
    keepSpeedBounds();
}

void Camera::setMaxSpeed( float maxSpeed )
{ 
    this->maxSpeed = maxSpeed;
    keepSpeedBounds();
}

void Camera::setMinSpeed( float minSpeed )
{
    this->minSpeed = minSpeed;
    keepSpeedBounds();
}

void Camera::keepSpeedBounds()
{
    if (this->speed > maxSpeed) {
        this->speed = maxSpeed;
    } else if (this->speed < minSpeed) {
        this->speed = minSpeed;
    }
}