#include "QuatCamera.h"
#include <stdio.h>

const D3DXVECTOR3 QuatCamera::basisDirectionVector(0.0f, 0.0f, 1.0f);
const D3DXVECTOR3 QuatCamera::basisUpVector(0.0f, 1.0f, 0.0f);

QuatCamera::QuatCamera(void)
{
    D3DXQuaternionIdentity(&rotQuat);
    D3DXQuaternionNormalize(&rotQuat, &rotQuat);
    updateDirectionVectors();
    updateViewMatrix();
}


QuatCamera::~QuatCamera(void)
{
}

void QuatCamera::yaw( float radians )
{
	updateOrientation(up, radians);
}

void QuatCamera::pitch( float radians )
{
    radians = yInverted? -radians : radians;
	updateOrientation(right, radians);
}

void QuatCamera::roll( float radians )
{
    updateOrientation(lookDirection, radians);
}

void QuatCamera::update(float time)
{
    position += lookDirection * speed /* * static_cast<float>(time) */;

    updateViewMatrix();
}

void QuatCamera::updateOrientation(D3DXVECTOR3 rotVector, float angleRad)
{
    D3DXQUATERNION rot;

	// create rotation matrix
	D3DXQuaternionRotationAxis(&rot, &rotVector, angleRad);
    rotQuat *= rot;
    D3DXQuaternionNormalize(&rotQuat, &rotQuat);
    updateDirectionVectors();
    updateViewMatrix();
}

void QuatCamera::updateDirectionVectors()
{
    D3DXMATRIX matRotation;
    D3DXMatrixRotationQuaternion(&matRotation, &rotQuat);
    D3DXVec3TransformCoord(&up, &basisUpVector, &matRotation);
    D3DXVec3TransformCoord(&lookDirection, &basisDirectionVector, &matRotation);
    D3DXVec3Cross(&right, &up, &lookDirection);

    D3DXVec3Normalize(&lookDirection, &lookDirection);
    D3DXVec3Normalize(&up, &up);
    D3DXVec3Normalize(&right, &right);
}

void QuatCamera::updateViewMatrix()
{
    D3DXMatrixLookAtLH(&view, &position, &getLookAtPoint(), &up);
}

float QuatCamera::getPitchAngle() const
{
    float angle = computeAngleBetweenNormal(&up, &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
    return angle;
}

float QuatCamera::getYawAngle() const
{
    float angle = computeAngleBetweenNormal(&lookDirection , &D3DXVECTOR3(1.0f, 0.0f, 0.0f));
    return angle;
    if (lookDirection.z < 0) {
        return 360.0f - angle;
    } else {
        return angle;
    }
}

float QuatCamera::computeAngleBetweenNormal(const D3DXVECTOR3 *vec1, const D3DXVECTOR3 *vec2) const
{
    float dot = D3DXVec3Dot(vec1, vec2);
    return D3DXToDegree(asin(dot));
}