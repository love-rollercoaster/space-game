#pragma once
#include <d3dx9.h>

class Camera
{
public:
    Camera();

    virtual void createProjectionMatrix( float fov, float aspect, float nearPlane, float farPlane );

    virtual void yaw( float radians ) = 0;
    virtual void pitch( float radians ) = 0;
    virtual void roll( float radians ) = 0;
    virtual void update(int time) = 0;

    virtual void setPosition( D3DXVECTOR3 &position ) {this->position = D3DXVECTOR3(position);}
    virtual void setFOV( float fov )            { createProjectionMatrix( fov, aspect, nearPlane, farPlane ); }
    virtual void setAspectRatio( float aspect ) { createProjectionMatrix( fov, aspect, nearPlane, farPlane ); }
    virtual void setNearPlane( float plane )    { createProjectionMatrix( fov, aspect, plane, farPlane ); }
    virtual void setFarPlane( float plane )     { createProjectionMatrix( fov, aspect, nearPlane, plane ); }
    virtual void setMaxSpeed( float maxSpeed )  { this->maxSpeed = maxSpeed; }
    virtual void setInvertY( bool invert )      { this->yInverted = invert; }
    virtual void setMaxPitch( float maxPitch )  { this->maxPitchAngle = maxPitch; }
    virtual void setIgnoreMaxPitchAngle( bool ignore ) { this->ignoreMaxPitchAngle = ignore;}
    virtual void setSpeed(float speed);
    virtual void changeSpeedBy(float dSpeed);

    virtual D3DXMATRIX getViewMatrix() const        { return view; }
    virtual D3DXMATRIX getProjectionMatrix() const  { return projection; }
    virtual D3DXVECTOR3 getUpVector() const         { return up; }
    virtual D3DXVECTOR3 getPosition() const         { return position; }
    virtual D3DXVECTOR3 getLookAtPoint() const      { return position + lookDirection; }
    virtual D3DXVECTOR3 getLookDirection() const    { return lookDirection; }
    virtual float getFOV() const              { return fov; }
    virtual float getAspectRatio() const      { return aspect; }
    virtual float getNearPlane() const        { return nearPlane; }
    virtual float getFarPlane() const         { return farPlane; }
    virtual float getSpeed() const            { return speed; }
    virtual float getMaxSpeed() const         { return maxSpeed; }
    virtual bool  getInvertY() const          { return yInverted; }
    virtual float getMaxPitchAngle() const    { return maxPitchAngle; }
    virtual float getPitchAngle() const = 0;
    virtual float getYawAngle() const = 0;

protected:
    D3DXMATRIX  view;
    D3DXMATRIX  projection;
    D3DXVECTOR3 right;
    D3DXVECTOR3 up;
    D3DXVECTOR3 lookDirection;
    D3DXVECTOR3 position;
    float       speed;
    float       maxPitchAngle;
    float       maxSpeed;
    float       fov;
    float       aspect;
    float       nearPlane;
    float       farPlane;
    bool        yInverted;
    bool        yMovementEnabled;
    bool        ignoreMaxPitchAngle;

private:
    void keepSpeedBounds();
};