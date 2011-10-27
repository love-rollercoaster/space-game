#include "TestGameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "AsteroidGraphicsComponent.h"
#include "BuildingGraphicsComponent.h"
#include "SpaceshipGraphicsComponent.h"
#include "LaserGraphicsComponent.h"
#include "VolumetricLines.h"
#include "EarthSceneryElement.h"

#define MESH_COLUMNS   100
#define MESH_ROWS      100
#define MESH_CELL_SIZE 100

#define EARTH_POSITION D3DXVECTOR3(-0.3f, 0, -1) // fixme
// temporary
#define RANDOM(lowerBound, upperBound) (float)((double)rand() / (RAND_MAX+1) * (upperBound - lowerBound) + lowerBound)

TestGameWorld::TestGameWorld( void )
    : spaceshipGraphicsComponent(new SpaceshipGraphicsComponent())
    , laserGraphicsComponent(new LaserGraphicsComponent())
    , planeInputComponent(new PlaneInputComponent())
    , laserShootDelay(0.0f)
    , asteroidBeingFollowed(0)
    , cameraFollowingShip(true)
    , cameraChangeDelay(0.0f)
{
}

TestGameWorld::~TestGameWorld( void )
{
}

void TestGameWorld::init( GameEngine &gameEngine )
{
    initSpaceship(gameEngine);
    initAsteroids(gameEngine);

    shared_ptr<Laser> laser(new Laser(plane.getRotationQuat(), plane.getPosition() + plane.getDirection() * 5.0f, plane.getDirection()));
    laser->init(NULL, NULL, laserGraphicsComponent);
    lasers.push_back(laser);

    GraphicsEngine &graphicsEngine = gameEngine.getGraphicsEngine();

    shared_ptr<EarthSceneryElement> earthSceneryElement(new EarthSceneryElement);
    earthSceneryElement->init(graphicsEngine);
    graphicsEngine.addSceneryElement(earthSceneryElement);

    camera = new FollowCamera(&plane);
    camera->setFarPlane(20000.0f);
    graphicsEngine.setCamera(*camera);

    initLighting(graphicsEngine);
    laserGraphicsComponent->init(graphicsEngine);
    spaceshipGraphicsComponent->init(graphicsEngine);
    graphicsEngine.setBackgroundColor(D3DCOLOR_XRGB(0, 6, 8));
    graphicsEngine.enableFog(camera->getFarPlane() - 1000.0f, camera->getFarPlane());   
}

void TestGameWorld::update( float time )
{
    laserShootDelay -= time;
    cameraChangeDelay -= time;
    plane.update(time);
    camera->update(time);

    for each (shared_ptr<Asteroid> asteroid in asteroids) {
        asteroid->update(time);
    }

    vector<shared_ptr<Laser> >::iterator it;
    for (it = lasers.begin(); it != lasers.end();) {
        (*it)->update(time);

        // TODO collision detection here

        if ((*it)->isExpired()) {
            it = lasers.erase(it);
        } else {
            it++;
        }
    }
}

void TestGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    plane.draw(graphicsEngine);

    for each (shared_ptr<Asteroid> asteroid in asteroids) {
        asteroid->draw(graphicsEngine);
    }

    for each(shared_ptr<Laser> laser in lasers) {
        laser->draw(graphicsEngine);
    }
}

void TestGameWorld::shootLaser()
{
    if (laserShootDelay <= 0.0f) {
        shared_ptr<Laser> laser = shared_ptr<Laser>(new Laser(plane.getRotationQuat(), plane.getPosition() + plane.getDirection() *0.5f, plane.getDirection()));
        laser->changeSpeedBy(plane.getSpeed());
        laser->init(NULL, NULL, laserGraphicsComponent);
        lasers.push_back(laser);
        laserShootDelay = LASER_SHOOT_DELAY_MS;
    }
}

void TestGameWorld::initSpaceship( GameEngine &gameEngine )
{
    planeInputComponent->init(&plane);
    plane.setMinSpeed(0.0f);
    plane.init(planeInputComponent, NULL, spaceshipGraphicsComponent);
}

void TestGameWorld::initAsteroids( GameEngine &gameEngine )
{
    float yMin = -1000.0f;
    float yMax = 1000.0f;
    float minAsteroidScale = 10.0f;
    float maxAsteroidScale = 150.0f;
    float asteroidCreationProbablility = 0.994f;

    for (int i = 0; i < MESH_ROWS; i++) {
        for (int j = 0; j < MESH_COLUMNS; j++) {

            float asteroidCreationDice = RANDOM(0,1);

            if (asteroidCreationDice < asteroidCreationProbablility) {
                continue;
            }
            
            float yAsteroidPosition = RANDOM(yMax, yMin);
            float asteroidScale = RANDOM(minAsteroidScale, maxAsteroidScale);

            float xAsteroidPosition = (float) i * MESH_CELL_SIZE;
            float zAsteroidPosition = (float) j * MESH_CELL_SIZE;

            shared_ptr<Asteroid> asteroid(new Asteroid());

            asteroid->init(gameEngine);
                
            shared_ptr<MoveableGameObject> asteroidRepresentation = asteroid->getGameObjectRepresentation();
                
            asteroidRepresentation->setScale(asteroidScale, asteroidScale, asteroidScale);
                
            D3DXVECTOR3 asteroidPosition = D3DXVECTOR3(xAsteroidPosition, yAsteroidPosition, zAsteroidPosition);

            asteroidRepresentation->yaw(D3DXToRadian(RANDOM(0, 360)));
            asteroidRepresentation->pitch(D3DXToRadian(RANDOM(0, 360)));
            asteroidRepresentation->roll(D3DXToRadian(RANDOM(0, 360)));
            asteroidRepresentation->setPitchRotationSpeed(RANDOM(0, 0.5f));
            asteroidRepresentation->setRollRotationSpeed(RANDOM(0, 0.5f));
            asteroidRepresentation->setYawRotationSpeed(RANDOM(0, 0.5f));
            asteroidRepresentation->setPosition(asteroidPosition);
            asteroidRepresentation->setFixedDirection(true);
            asteroidRepresentation->setDirection(EARTH_POSITION);
            asteroidRepresentation->setSpeed(RANDOM(75, 400));

            asteroids.push_back(asteroid);
        }
    }

}

void TestGameWorld::initLighting(GraphicsEngine &graphicsEngine)
{
    int i = 0;
    initAmbientLighting(graphicsEngine);
    i += initDirectionalLighting(i, graphicsEngine);
    i += initPointLighting(i, graphicsEngine);
}

void TestGameWorld::initAmbientLighting(GraphicsEngine &graphicsEngine)
{
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
}

int TestGameWorld::initDirectionalLighting(int lightIndex, GraphicsEngine &graphicsEngine)
{
    D3DLIGHT9 light;
    ZeroMemory(&light, sizeof(light));
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    light.Direction = D3DXVECTOR3(0.0f, -1.0f, -1.0f);

    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &light);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    return lightIndex +1;
}

int TestGameWorld::initPointLighting(int lightIndex, GraphicsEngine &graphicsEngine)
{
    D3DLIGHT9 earthLight, sunlight;
    ZeroMemory(&sunlight, sizeof(sunlight));
    sunlight.Type = D3DLIGHT_POINT;
    sunlight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    sunlight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    sunlight.Position = D3DXVECTOR3(0.0f, 500000.0f, 500000.0f); //sun position
    sunlight.Range = 1000000.0f;
    sunlight.Attenuation0 = 1.0f;
    sunlight.Attenuation1 = 0.0f;
    sunlight.Attenuation2 = 0.0f;

    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &sunlight);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    lightIndex++;

    ZeroMemory(&earthLight, sizeof(earthLight));
    earthLight.Type = D3DLIGHT_POINT;
    earthLight.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
    earthLight.Position = D3DXVECTOR3(0.0f, 0.0f, -250000.0f); //earth position
    earthLight.Range = 500000.0f;
    earthLight.Attenuation0 = 0.7f;
    earthLight.Attenuation1 = 0.05f;
    earthLight.Attenuation2 = 0.0f;
    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &earthLight);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    return lightIndex +1;
}

void TestGameWorld::followNextAsteroid()
{
    if (cameraChangeDelay > 0 || asteroids.size() == 0) {
        return;
    }
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    if (cameraFollowingShip) {
        asteroidBeingFollowed = 0;
    } else {
        asteroidBeingFollowed++;
        if (asteroidBeingFollowed >= asteroids.size()) {
            asteroidBeingFollowed = 0;
        }
    }
    cameraFollowingShip = false;
    followCamera->setGameObject(asteroids[asteroidBeingFollowed]->getGameObjectRepresentation().get());
    cameraChangeDelay = CAMERA_CHANGE_DELAY_MS;
}

void TestGameWorld::followPreviousAsteroid()
{
    if (cameraChangeDelay > 0 || asteroids.size() == 0) {
        return;
    }
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    if (cameraFollowingShip) {
        asteroidBeingFollowed = 0;
    } else {
        if (asteroidBeingFollowed == 0) {
            asteroidBeingFollowed = asteroids.size() - 1;
        } else {
            asteroidBeingFollowed--;
        }
    }
    cameraFollowingShip = false;
    followCamera->setGameObject(asteroids[asteroidBeingFollowed]->getGameObjectRepresentation().get());
    cameraChangeDelay = CAMERA_CHANGE_DELAY_MS;
}

void TestGameWorld::followShip()
{
    if (cameraChangeDelay > 0) {
        return;
    }
    if (!cameraFollowingShip) {
        FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
        if (followCamera == NULL) {
            return;
        }
        cameraFollowingShip = true;
        followCamera->setGameObject(&plane);
        cameraChangeDelay = CAMERA_CHANGE_DELAY_MS;
    }
}

void TestGameWorld::setFirstPersonCamera()
{
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    followCamera->setFirstPersonCamera();
}

void TestGameWorld::setThirdPersonCamera()
{
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    followCamera->setThirdPersonCamera();
}
