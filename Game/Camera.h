// Reference:
// http://www.chadvernon.com/blog/resources/directx9/moving-around-a-3d-world/

#pragma once

#include <d3dx9.h>
#include "GameObject.h"

class Camera
{
public:
    Camera();

    void createProjectionMatrix( float fov, float aspect, float nearPlane, float farPlane );
    void moveForward( float units );
    void strafe( float units );
    void moveUp( float units );    

    void yaw( float radians );
    void pitch( float radians );
    void roll( float radians );
    void update();

    void setPosition( D3DXVECTOR3 &position );
    void setLookAtPoint( D3DXVECTOR3 &lookAtPoint );
    void setFOV( float fov )            { createProjectionMatrix( fov, aspect, nearPlane, farPlane ); }
    void setAspectRatio( float aspect ) { createProjectionMatrix( fov, aspect, nearPlane, farPlane ); }
    void setNearPlane( float plane )    { createProjectionMatrix( fov, aspect, plane, farPlane ); }
    void setFarPlane( float plane )     { createProjectionMatrix( fov, aspect, nearPlane, plane ); }
    void setMaxVelocity( float maxVelocity ) { maxVelocity = maxVelocity; }
    void setInvertY( bool invert )           { yInverted = invert; }
    void setMaxPitch( float maxPitch )       { maxPitch = maxPitch; }
    void setIgnoreMaxPitchAngle( bool ignore ) { ignoreMaxPitchAngle = ignore;}

    D3DXMATRIX* getViewMatrix()        { return &view; }
    D3DXMATRIX* getProjectionMatrix()  { return &projection; }
    D3DXVECTOR3* getPosition()         { return &position; }
    D3DXVECTOR3* getLookAtPoint()      { return &lookAtPoint; }
    D3DXVECTOR3* getLookDirection()    { return &lookDirection; }
    float getFOV()                     { return fov; }
    float getAspectRatio()             { return aspect; }
    float getNearPlane()               { return nearPlane; }
    float getFarPlane()                { return farPlane; }
    float getMaxVelocity()             { return maxVelocity; }
    bool  getInvertY()                 { return yInverted; }
    float getPitchAngle()              { return pitchAngle; }
    float getYawAngle()                { return yawAngle; }
    float getMaxPitchAngle()           { return maxPitchAngle; }

private:
    D3DXMATRIX  view;
    D3DXMATRIX  projection;
    D3DXVECTOR3 right;
    D3DXVECTOR3 up;
    D3DXVECTOR3 lookDirection;
    D3DXVECTOR3 position;
    D3DXVECTOR3 lookAtPoint;
    D3DXVECTOR3 velocity;
    float       yawAngle;
    float       pitchAngle;
    float       maxPitchAngle;
    float       maxVelocity;
    float       fov;
    float       aspect;
    float       nearPlane;
    float       farPlane;
    bool        yInverted;
    bool        yMovementEnabled;
    bool        ignoreMaxPitchAngle;
};