#include "LaserPhysicsComponent.h"
#include "AsteroidGraphicsComponent.h"
#include <algorithm>
using std::max;

LaserPhysicsComponent::LaserPhysicsComponent(void)
{
}


LaserPhysicsComponent::~LaserPhysicsComponent(void)
{
}

bool LaserPhysicsComponent::testIntersectionWithAsteroid(Laser &laser, Asteroid &asteroid)
{
    D3DXVECTOR3 currLaserPos = laser.getPosition(), lastLaserPos = laser.getLastPosition(), 
        laserDir = laser.getDirection(), asteroidPosition = asteroid.getPosition();
    float asteroidRadius = getAsteroidBoundingSphereRadius(asteroid);
    float asteroidPosToLaserEnd;

    //check if the laser ray intersects a rough bounding sphere of the asteroid
    if (!D3DXSphereBoundProbe(&asteroidPosition, asteroidRadius, &lastLaserPos, &laserDir)) {
        return false;
    }

    asteroidPosToLaserEnd = D3DXVec3LengthSq(&(currLaserPos - asteroidPosition));

    //if this is true then the laser's current position does not fall within the sphere, and a ray starting at the laser's
    //current point crosses the circle. A ray starting at the last point already crosses the sphere, so this means both
    //points are "before" the sphere, along the ray in the direction the laser is travelling.
    if (asteroidRadius * asteroidRadius < asteroidPosToLaserEnd && 
        D3DXSphereBoundProbe(&asteroidPosition, asteroidRadius, &currLaserPos, &laserDir)) {
        return false;
    }

    //it may have collided. Now check ray against mesh
    shared_ptr<GraphicsComponent> gfx = asteroid.getGraphicsComponent();
    AsteroidGraphicsComponent *asteroidGraphicsComponent = dynamic_cast<AsteroidGraphicsComponent*>(gfx.get());
    
    if (asteroidGraphicsComponent == NULL) {
        throw "Asteroid didn't have a valid asteroid graphics component!";
    }

    BOOL hit;
    float dist;
    D3DXVECTOR3 laserPosRelativeToAsteroid = lastLaserPos - asteroidPosition;
    D3DXVECTOR3 asteroidScale = asteroid.getScale();
    D3DXQUATERNION rotationQuat = asteroid.getRotationQuat();
    D3DXMATRIX rot, scale;
    D3DXMatrixScaling(&scale, 0.8f/asteroidScale.x, 0.8f/asteroidScale.y, 0.8f/asteroidScale.z);
    D3DXMatrixRotationQuaternion(&rot, &rotationQuat);
    D3DXVec3TransformCoord(&laserPosRelativeToAsteroid, &laserPosRelativeToAsteroid, &(scale * rot));

    D3DXIntersect(asteroidGraphicsComponent->getMesh(),
        &laserPosRelativeToAsteroid,
        &laserDir,
        &hit,
        NULL,
        NULL,
        NULL,
        &dist,
        NULL,
        NULL);

    float distTravelledSq = D3DXVec3LengthSq(&(currLaserPos - lastLaserPos));
    if (!hit || dist * dist > D3DXVec3LengthSq(&(currLaserPos - lastLaserPos))) {
        return false;
    }

    return true;
}

float LaserPhysicsComponent::getAsteroidBoundingSphereRadius(Asteroid &asteroid)
{
    D3DXVECTOR3 asteroidScale = asteroid.getScale();
    float maxRadius = max<float>(ASTEROID_BASE_X * asteroidScale.x, ASTEROID_BASE_Y * asteroidScale.y);
    maxRadius = max<float>(maxRadius, ASTEROID_BASE_Z * asteroidScale.z);
    return maxRadius;
}