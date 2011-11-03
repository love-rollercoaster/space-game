#include "MoveableGameObject.h"

const D3DXVECTOR3 MoveableGameObject::basisDirectionVector(0.0f, 0.0f, 1.0f);
const D3DXVECTOR3 MoveableGameObject::basisUpVector(0.0f, 1.0f, 0.0f);

MoveableGameObject::MoveableGameObject(D3DXVECTOR3 position, D3DXVECTOR3 scale)
    : position(position)
    , scale(scale)
    , speed(0.0f)
    , rollRotationSpeed(0.0f)
    , yawRotationSpeed(0.0f)
    , pitchRotationSpeed(0.0f)
    , fixedDirection(false)
    , minSpeed(DEFAULT_MIN_SPEED)
    , maxSpeed(DEFAULT_MAX_SPEED)
{
    D3DXQuaternionIdentity(&rotation);
    D3DXQuaternionNormalize(&rotation, &rotation);

    computeDirectionVectors();
}

D3DXVECTOR3 MoveableGameObject::getPosition()
{
    return position;
}

D3DXVECTOR3 MoveableGameObject::getDirection()
{
    return direction;
}
D3DXVECTOR3 MoveableGameObject::getUpVector()
{
    return up;
}

D3DXVECTOR3 MoveableGameObject::getScale()
{
    return scale;
}

void MoveableGameObject::setPosition( D3DXVECTOR3 position )
{
    this->position = position;
}

void MoveableGameObject::setScale( D3DXVECTOR3 scale )
{
    this->scale = scale;
}

void MoveableGameObject::setScale( float x, float y, float z )
{
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;
}

D3DXMATRIX* MoveableGameObject::generateTransformationMatrix(D3DXMATRIX *matrix)
{
    D3DXMATRIX scalingMatrix, translationMatrix, rotationMatrix;
    D3DXMatrixIdentity(matrix);

    D3DXMatrixScaling(&scalingMatrix, scale.x, scale.y, scale.z);

    D3DXMatrixRotationQuaternion(&rotationMatrix, &rotation);

    D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);
    D3DXMatrixMultiply(matrix, &(scalingMatrix * rotationMatrix), &translationMatrix);

    return matrix;
}

void MoveableGameObject::yaw( float radians )
{
    if (radians == 0.0f)
        return;
    changeOrientation(up, radians);
}

void MoveableGameObject::pitch( float radians )
{
    if (radians == 0.0f)
        return;
    changeOrientation(right, radians);
}

void MoveableGameObject::roll( float radians )
{
    if (radians == 0.0f)
        return;
    changeOrientation(direction, radians);
}

float MoveableGameObject::getYawRotationSpeed() 
{
    return yawRotationSpeed;
}

float MoveableGameObject::getRollRotationSpeed() 
{
    return rollRotationSpeed;
}

float MoveableGameObject::getPitchRotationSpeed() 
{
    return pitchRotationSpeed;
}

void MoveableGameObject::setYawRotationSpeed(float radiansPerSecond) 
{
    yawRotationSpeed = radiansPerSecond;
}

void MoveableGameObject::setRollRotationSpeed(float radiansPerSecond) 
{
    rollRotationSpeed = radiansPerSecond;
}

void MoveableGameObject::setPitchRotationSpeed(float radiansPerSecond) 
{
    pitchRotationSpeed = radiansPerSecond;
}

D3DXQUATERNION MoveableGameObject::getRotationQuat()
{
    return rotation;
}

void MoveableGameObject::changeOrientation(D3DXVECTOR3 rotationVector, float radians)
{
    D3DXQUATERNION newRotation;
	D3DXQuaternionRotationAxis(&newRotation, &rotationVector, radians);
    
    rotation *= newRotation;
    D3DXQuaternionNormalize(&rotation, &rotation);
    
    if (!fixedDirection) {
        computeDirectionVectors();
    }
}

void MoveableGameObject::computeDirectionVectors()
{
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationQuaternion(&rotationMatrix, &rotation);
    D3DXVec3TransformCoord(&up, &basisUpVector, &rotationMatrix);
    D3DXVec3TransformCoord(&direction, &basisDirectionVector, &rotationMatrix);
    D3DXVec3Cross(&right, &up, &direction);

    D3DXVec3Normalize(&direction, &direction);
    D3DXVec3Normalize(&up, &up);
    D3DXVec3Normalize(&right, &right);
}

void MoveableGameObject::update(float time)
{
    if (physicsComponent != NULL) {
        physicsComponent->update(*this, time);
    }
}

void MoveableGameObject::changeSpeedBy(float speedDelta)
{
    this->speed += speedDelta;
    keepSpeedBounds();
}

float MoveableGameObject::getSpeed()
{
    return this->speed;
}

void MoveableGameObject::setDirection( D3DXVECTOR3 direction )
{
    this->direction = direction;
}

void MoveableGameObject::setFixedDirection( bool fixedDirection )
{
    this->fixedDirection = fixedDirection;
}

void MoveableGameObject::setSpeed(float speed) 
{
    this->speed = speed;
    keepSpeedBounds();
}

float MoveableGameObject::getMinSpeed()
{
    return minSpeed;
}

float MoveableGameObject::getMaxSpeed()
{
    return maxSpeed;
}

void MoveableGameObject::setMaxSpeed( float maxSpeed )
{ 
    this->maxSpeed = maxSpeed;
    keepSpeedBounds();
}

void MoveableGameObject::setMinSpeed( float minSpeed )
{
    this->minSpeed = minSpeed;
    keepSpeedBounds();
}

void MoveableGameObject::keepSpeedBounds()
{
    if (this->speed > maxSpeed) {
        this->speed = maxSpeed;
    } else if (this->speed < minSpeed) {
        this->speed = minSpeed;
    }
}

void MoveableGameObject::setRotation(D3DXQUATERNION rot) {
    rotation = rot;
    computeDirectionVectors();
}