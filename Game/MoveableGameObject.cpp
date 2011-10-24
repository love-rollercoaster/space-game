#include "MoveableGameObject.h"

const D3DXVECTOR3 MoveableGameObject::basisDirectionVector(0.0f, 0.0f, 1.0f);
const D3DXVECTOR3 MoveableGameObject::basisUpVector(0.0f, 1.0f, 0.0f);

MoveableGameObject::MoveableGameObject(D3DXVECTOR3 position, D3DXVECTOR3 scale) :
    position(position), scale(scale), GameObject(), speed(0.0f), 
    rollRotateSpeed(0.0f), yawRotateSpeed(0.0f), pitchRotateSpeed(0.0f)
{
    D3DXQuaternionIdentity(&rotation);
    D3DXQuaternionNormalize(&rotation, &rotation);
    updateDirectionVectors();
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

D3DXMATRIX *MoveableGameObject::generateTransformationMatrix(D3DXMATRIX *matrix)
{
    D3DXMATRIX matScale, matTranslate, matRotate;
    D3DXMatrixIdentity(matrix);

    D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

    D3DXMatrixRotationQuaternion(&matRotate, &rotation);

    D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
    D3DXMatrixMultiply(matrix, &(matScale * matRotate), &matTranslate);
    return matrix;
}

void MoveableGameObject::yaw( float radians )
{
    if (radians == 0)
        return;
    updateOrientation(up, radians);
}

void MoveableGameObject::pitch( float radians )
{
    if (radians == 0)
        return;
    updateOrientation(right, radians);
}

void MoveableGameObject::roll( float radians )
{
    if (radians == 0)
        return;
    updateOrientation(direction, radians);
}

void MoveableGameObject::setYawRotationSpeed(float radsPerSec) 
{
    yawRotateSpeed = radsPerSec;
}

void MoveableGameObject::setRollRotationSpeed(float radsPerSec) 
{
    rollRotateSpeed = radsPerSec;
}

void MoveableGameObject::setPitchRotationSpeed(float radsPerSec) 
{
    pitchRotateSpeed = radsPerSec;
}

void MoveableGameObject::setSpeed(float speed) 
{
    this->speed = speed;
}

D3DXQUATERNION MoveableGameObject::getRotationQuat()
{
    return rotation;
}

void MoveableGameObject::updateOrientation(D3DXVECTOR3 rotVector, float angleRad)
{
    D3DXQUATERNION rot;

	// create rotation matrix
	D3DXQuaternionRotationAxis(&rot, &rotVector, angleRad);
    rotation *= rot;
    D3DXQuaternionNormalize(&rotation, &rotation);
    updateDirectionVectors();
}

void MoveableGameObject::updateDirectionVectors()
{
    D3DXMATRIX matRotation;
    D3DXMatrixRotationQuaternion(&matRotation, &rotation);
    D3DXVec3TransformCoord(&up, &basisUpVector, &matRotation);
    D3DXVec3TransformCoord(&direction, &basisDirectionVector, &matRotation);
    D3DXVec3Cross(&right, &up, &direction);

    D3DXVec3Normalize(&direction, &direction);
    D3DXVec3Normalize(&up, &up);
    D3DXVec3Normalize(&right, &right);
}

void MoveableGameObject::update(float time) {
    position += direction * speed * time / 1000.0f;
    roll(rollRotateSpeed * time / 1000.0f);
    pitch(pitchRotateSpeed * time / 1000.0f);
    yaw(yawRotateSpeed * time / 1000.0f);
}

void MoveableGameObject::changeSpeedBy(float dSpeed)
{
    this->speed += dSpeed;
}