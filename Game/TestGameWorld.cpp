#include "TestGameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "AsteroidGraphicsComponent.h"
#include "BuildingGraphicsComponent.h"
#include "SpaceshipGraphicsComponent.h"
#include "LaserGraphicsComponent.h"
#include "EarthSceneryElement.h"
#include "SunSceneryElement.h"
#include "FontSystem.h"
#include "Log.h"
#include <string>

#define MESH_COLUMNS   100
#define MESH_ROWS      100
#define MESH_CELL_SIZE 5

#define EARTH_POSITION D3DXVECTOR3(-0.3f, 0, -1) // fixme
// temporary
#define RANDOM(lowerBound, upperBound) (float)((double)rand() / (RAND_MAX+1) * (upperBound - lowerBound) + lowerBound)

using std::string;

TestGameWorld::TestGameWorld( void )
    : laserShootDelay(0.0f)
    , asteroidBeingFollowed(0)
    , cameraFollowingShip(true)
    , cameraChangeDelay(0.0f)
    , objectBeingFollowed(NULL)
    , usingThirdPersonCamera(true)
{
}

TestGameWorld::~TestGameWorld( void )
{
}

void TestGameWorld::init( GameEngine &gameEngine )
{
    GraphicsEngine &graphicsEngine = gameEngine.getGraphicsEngine();
    planeInputComponent = shared_ptr<InputComponent>(new PlaneInputComponent());
    initGraphicsComponents(graphicsEngine);
    initPhysicsComponents();
    initSpaceship(gameEngine);
    initAsteroids(gameEngine);
    //makeOneAsteroid(gameEngine);

    laserGraphicsComponent->init(graphicsEngine);
    spaceshipGraphicsComponent->init(graphicsEngine);

    initCamera(graphicsEngine);
    initSceneryElements(graphicsEngine);
    initLighting(graphicsEngine);

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

        if (testCollisionOfLaserWithAllAsteroids(*it)) {
            it = lasers.erase(it);
            continue;
        }

        if ((*it)->isExpired()) {
            it = lasers.erase(it);
        } else {
            it++;
        }
    }
}

bool TestGameWorld::testCollisionOfLaserWithAllAsteroids(shared_ptr<Laser> laser) {
    vector<shared_ptr<Asteroid> >::iterator it;
    for (it = asteroids.begin(); it != asteroids.end();) {
        if (laserPhysicsComponent->testIntersectionWithAsteroid(*laser.get(), *(*it).get())) {
            POUT("Laser collided with an asteroid");
            it = asteroids.erase(it);
            return true;
        } else {
            it++;
        }
    }
    return false;
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
    
    drawShipPositionText();
}

void TestGameWorld::shootLaser()
{
    if (laserShootDelay <= 0.0f) {
        shared_ptr<Laser> laser = shared_ptr<Laser>(new Laser(plane.getRotationQuat(), plane.getPosition() + plane.getDirection() *0.5f, plane.getDirection()));
        laser->changeSpeedBy(plane.getSpeed());
        laser->init(NULL, laserPhysicsComponent, laserGraphicsComponent);
        lasers.push_back(laser);
        laserShootDelay = LASER_SHOOT_DELAY_MS;
    }
}

void TestGameWorld::initGraphicsComponents(GraphicsEngine &graphicsEngine) {
    asteroidGraphicsComponent = shared_ptr<GraphicsComponent>(new AsteroidGraphicsComponent());
    asteroidGraphicsComponent->init(graphicsEngine);
    spaceshipGraphicsComponent = shared_ptr<GraphicsComponent>(new SpaceshipGraphicsComponent());
    spaceshipGraphicsComponent->init(graphicsEngine);
    laserGraphicsComponent = shared_ptr<GraphicsComponent>(new LaserGraphicsComponent());
    laserGraphicsComponent->init(graphicsEngine);
}

void TestGameWorld::initPhysicsComponents() {
    spaceshipPhysicsComponent = shared_ptr<PhysicsComponent>(new MoveableObjectPhysicsComponent());
    asteroidPhysicsComponent = spaceshipPhysicsComponent;
    laserPhysicsComponent = shared_ptr<LaserPhysicsComponent>(new LaserPhysicsComponent());
}

void TestGameWorld::initCamera( GraphicsEngine &graphicsEngine )
{
    FollowCamera *fc = new FollowCamera(&plane);
    objectBeingFollowed = &plane;
    fc->setThirdPersonCamera();
    usingThirdPersonCamera = true;
    camera = fc;
    camera->setFarPlane(20000.0f);
    graphicsEngine.setCamera(*camera);
}

void TestGameWorld::initSpaceship( GameEngine &gameEngine )
{
    planeInputComponent->init(&plane);
    plane.setMinSpeed(0.0f);
    plane.init(planeInputComponent, spaceshipPhysicsComponent, spaceshipGraphicsComponent);
}

void TestGameWorld::makeOneAsteroid(GameEngine &gameEngine) 
{
    D3DXVECTOR3 asteroidPosition = D3DXVECTOR3(0.0f, 3.0f, 10.0f);
    D3DXVECTOR3 asteroidScaleVec = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

    shared_ptr<Asteroid> asteroid(new Asteroid(asteroidPosition, asteroidScaleVec));

    asteroid->init(NULL, asteroidPhysicsComponent, asteroidGraphicsComponent);

    asteroid->yaw(D3DXToRadian(RANDOM(0, 360)));
    asteroid->pitch(D3DXToRadian(RANDOM(0, 360)));
    asteroid->roll(D3DXToRadian(RANDOM(0, 360)));
    asteroid->setPitchRotationSpeed(RANDOM(0, 0.5f));
    asteroid->setRollRotationSpeed(RANDOM(0, 0.5f));
    asteroid->setYawRotationSpeed(RANDOM(0, 0.5f));
    asteroid->setFixedDirection(true);
    asteroids.push_back(asteroid);
}

void TestGameWorld::initAsteroids( GameEngine &gameEngine )
{
    float yMin = -100.0f;
    float yMax = 100.0f;
    float minAsteroidScale = 1.0f;
    float maxAsteroidScale = 6.0f;
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
            D3DXVECTOR3 asteroidPosition = D3DXVECTOR3(xAsteroidPosition, yAsteroidPosition, zAsteroidPosition);
            D3DXVECTOR3 asteroidScaleVec = D3DXVECTOR3(asteroidScale, asteroidScale, asteroidScale);

            shared_ptr<Asteroid> asteroid(new Asteroid(asteroidPosition, asteroidScaleVec));

            asteroid->init(NULL, asteroidPhysicsComponent, asteroidGraphicsComponent);
                
            asteroid->yaw(D3DXToRadian(RANDOM(0, 360)));
            asteroid->pitch(D3DXToRadian(RANDOM(0, 360)));
            asteroid->roll(D3DXToRadian(RANDOM(0, 360)));
            asteroid->setPitchRotationSpeed(RANDOM(0, 0.5f));
            asteroid->setRollRotationSpeed(RANDOM(0, 0.5f));
            asteroid->setYawRotationSpeed(RANDOM(0, 0.5f));
            asteroid->setFixedDirection(true);
            asteroid->setDirection(EARTH_POSITION);
            asteroid->setSpeed(RANDOM(5, 20));

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
    //this light represents light coming from the general direction of the sun.
    D3DLIGHT9 light, light2, light3, light4;
    ZeroMemory(&light, sizeof(light));
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    D3DXVECTOR3 dir = SUN_POS;
    dir.x += 5.0f;
    dir.z += 5.0f;
    D3DXVec3Normalize(&dir, &dir);
    light.Direction = -dir;

    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &light);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    lightIndex += 1;

    ZeroMemory(&light2, sizeof(light2));
    light2.Type = D3DLIGHT_DIRECTIONAL;
    light2.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    dir = SUN_POS;
    dir.x -= 5.0f;
    dir.z += 5.0f;
    D3DXVec3Normalize(&dir, &dir);
    light2.Direction = -dir;

    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &light2);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    lightIndex += 1;

    ZeroMemory(&light3, sizeof(light3));
    light3.Type = D3DLIGHT_DIRECTIONAL;
    light3.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    dir = SUN_POS;
    dir.x -= 5.0f;
    dir.z -= 5.0f;
    D3DXVec3Normalize(&dir, &dir);
    light3.Direction = -dir;

    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &light3);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    lightIndex += 1;

    ZeroMemory(&light4, sizeof(light4));
    light4.Type = D3DLIGHT_DIRECTIONAL;
    light4.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    dir = SUN_POS;
    dir.x += 5.0f;
    dir.z -= 5.0f;
    D3DXVec3Normalize(&dir, &dir);
    light4.Direction = -dir;

    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &light4);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    return lightIndex +1;
}

int TestGameWorld::initPointLighting(int lightIndex, GraphicsEngine &graphicsEngine)
{
    //this creates a strong sun light from a distant point, and a weaker light emitted (reflected)
    //from the earth much closer.
    D3DLIGHT9 earthLight, sunlight;
    ZeroMemory(&sunlight, sizeof(sunlight));
    sunlight.Type = D3DLIGHT_POINT;
    sunlight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    sunlight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    sunlight.Position = SUN_POS * 50000.0f; //sun position
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
    earthLight.Position = EarthSceneryElement::GetPosition() * 10.0f; //earth position
    earthLight.Range = 500000.0f;
    earthLight.Attenuation0 = 0.7f;
    earthLight.Attenuation1 = 0.05f;
    earthLight.Attenuation2 = 0.0f;
    graphicsEngine.getDirect3DDevice()->SetLight(lightIndex, &earthLight);
    graphicsEngine.getDirect3DDevice()->LightEnable(lightIndex, true);
    return lightIndex +1;
}

void TestGameWorld::initSceneryElements( GraphicsEngine &graphicsEngine )
{
    shared_ptr<SceneryElement> earthSceneryElement(new EarthSceneryElement());
    shared_ptr<SceneryElement> sunSceneryElement(new SunSceneryElement());

    earthSceneryElement->init(graphicsEngine);
    sunSceneryElement->init(graphicsEngine);
    graphicsEngine.addSceneryElement(earthSceneryElement);
    graphicsEngine.addSceneryElement(sunSceneryElement);
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
    objectBeingFollowed->setDrawn(true);
    objectBeingFollowed = asteroids[asteroidBeingFollowed].get();
    objectBeingFollowed->setDrawn(usingThirdPersonCamera);
    followCamera->setGameObject(objectBeingFollowed);
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
    objectBeingFollowed->setDrawn(true);
    objectBeingFollowed = asteroids[asteroidBeingFollowed].get();
    objectBeingFollowed->setDrawn(usingThirdPersonCamera);
    followCamera->setGameObject(objectBeingFollowed);
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
        objectBeingFollowed->setDrawn(true);
        objectBeingFollowed = &plane;
        objectBeingFollowed->setDrawn(usingThirdPersonCamera);
        followCamera->setGameObject(objectBeingFollowed);
        cameraChangeDelay = CAMERA_CHANGE_DELAY_MS;
    }
}

void TestGameWorld::setFirstPersonCamera()
{
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    usingThirdPersonCamera = false;
    objectBeingFollowed->setDrawn(false);
    followCamera->setFirstPersonCamera();
}

void TestGameWorld::setThirdPersonCamera()
{
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    usingThirdPersonCamera = true;
    objectBeingFollowed->setDrawn(true);
    followCamera->setThirdPersonCamera();
}

void TestGameWorld::drawShipPositionText()
{
    static char buffer[256];
    D3DXVECTOR3 position = plane.getPosition();
    sprintf_s(buffer, "Position:\n%f\n%f\n%f)", position.x, position.y, position.z);
    FontSystem::DrawText(buffer, 10, 10, D3DCOLOR_XRGB(255,255,255));
}
