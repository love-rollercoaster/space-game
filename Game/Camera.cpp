// Reference:
// http://www.chadvernon.com/blog/resources/directx9/moving-around-a-3d-world/

#include "Camera.h"

Camera::Camera()
    : maxPitchAngle(D3DXToRadian( 89.0f ))
    , maxVelocity(1.0f)
    , yInverted(false)
    , yMovementEnabled(true)
    , position(0.0f, 0.0f, 0.0f)
    , velocity(0.0f, 0.0f, 0.0f)
    , lookDirection(0.0f, 0.0f, 1.0f)
    , ignoreMaxPitchAngle(false)
{
    createProjectionMatrix(1.3f, D3DXToRadian(45), 1.0f, 5000.0f );
    update();
}

void Camera::createProjectionMatrix( float fov, float aspect, float nearPlane, float farPlane )
{
    this->fov       = fov;
    this->aspect    = aspect;
    this->nearPlane = nearPlane;
    this->farPlane  = farPlane;
    D3DXMatrixPerspectiveFovLH( &projection, fov, aspect, nearPlane, farPlane );
}

void Camera::moveForward( float units )
{
    if ( yMovementEnabled ) {
        velocity += lookDirection * units;
    }
    else {
        D3DXVECTOR3 moveVector( lookDirection.x, 0.0f, lookDirection.z );
        D3DXVec3Normalize( &moveVector, &moveVector );
        velocity += moveVector * units;
    }
}

void Camera::strafe( float units )
{
    velocity += right * units;
}

void Camera::moveUp( float units )
{
    if ( yMovementEnabled )
    {
        velocity.y += units;
    }
}


void Camera::yaw( float radians )
{
    if ( radians == 0.0f ) {
        return;
    }
    D3DXMATRIX rotation;
    D3DXMatrixRotationAxis( &rotation, &up, radians );
    D3DXVec3TransformNormal( &right, &right, &rotation );
    D3DXVec3TransformNormal( &lookDirection, &lookDirection, &rotation );
}

void Camera::pitch( float radians )
{
    if ( radians == 0.0f ) {
        return;
    }

    radians = (yInverted) ? -radians : radians;
    pitchAngle -= radians;

    // Getting pitch angle difference if it the max pitch angle is not ignored
    // and if using the radians parameter would exceed the max pitch angle.
    if ( !ignoreMaxPitchAngle && pitchAngle > maxPitchAngle )
    {
        radians += pitchAngle - maxPitchAngle;
    }
    else if ( !ignoreMaxPitchAngle && pitchAngle < -maxPitchAngle )
    {
        radians += pitchAngle + maxPitchAngle;
    }

    D3DXMATRIX rotation;
    D3DXMatrixRotationAxis( &rotation, &right, radians );
    D3DXVec3TransformNormal( &up, &up, &rotation );
    D3DXVec3TransformNormal( &lookDirection, &lookDirection, &rotation );
}

void Camera::roll( float radians )
{
    if ( radians == 0.0f )
    {
        return;
    }
    D3DXMATRIX rotation;
    D3DXMatrixRotationAxis( &rotation, &lookDirection, radians );
    D3DXVec3TransformNormal( &right, &right, &rotation );
    D3DXVec3TransformNormal( &up, &up, &rotation );
}

void Camera::update()
{
    // Cap velocity to max velocity
    if ( D3DXVec3Length( &velocity ) > maxVelocity )
    {
        velocity = *(D3DXVec3Normalize( &velocity, &velocity )) * maxVelocity;
    }

    // Move the camera
    position += velocity;

    // Could decelerate here. I'll just stop completely.
    velocity = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    lookAtPoint = position + lookDirection;

    // Calculate the new view matrix
    D3DXVECTOR3 yNormal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &view, &position, &lookAtPoint, &yNormal );

    // Set the camera axes from the view matrix
    right.x = view._11;
    right.y = view._21;
    right.z = view._31;
    up.x = view._12;
    up.y = view._22;
    up.z = view._32;
    lookDirection.x = view._13;
    lookDirection.y = view._23;
    lookDirection.z = view._33;

    // Calculate yaw and pitch
    float lookLengthOnXZ = sqrtf( lookDirection.z * lookDirection.z + lookDirection.x * lookDirection.x );
    pitchAngle = atan2f( lookDirection.y, lookLengthOnXZ );
    yawAngle   = atan2f( lookDirection.x, lookDirection.z );
}

void Camera::setPosition( D3DXVECTOR3 &position )
{
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
}

void Camera::setLookAtPoint( D3DXVECTOR3 &lookAtPoint )
{
    this->lookAtPoint.x = lookAtPoint.x;
    this->lookAtPoint.y = lookAtPoint.y;
    this->lookAtPoint.z = lookAtPoint.z;
    D3DXVec3Normalize( &lookDirection, &(lookAtPoint - position) );
}