#include "AsteroidsGameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "AsteroidGraphicsComponent.h"
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

AsteroidsGameWorld::AsteroidsGameWorld( void )
    : laserShootDelay(0.0f)
    , asteroidBeingFollowed(0)
    , cameraFollowingShip(true)
    , cameraChangeDelay(0.0f)
    , objectBeingFollowed(NULL)
    , usingThirdPersonCamera(true)
    , usingAsteroidGraphic(true)
    , spaceshipGraphicsComponent(new SpaceshipGraphicsComponent())
    , asteroidGraphicsComponent(new AsteroidGraphicsComponent())
    , laserGraphicsComponent(new LaserGraphicsComponent())
    , spaceshipInputComponent(new PlaneInputComponent())
{
}

AsteroidsGameWorld::~AsteroidsGameWorld( void )
{
}

void AsteroidsGameWorld::init( GameEngine &gameEngine )
{
    GraphicsEngine &graphicsEngine = gameEngine.getGraphicsEngine();
    initGraphicsComponents(graphicsEngine);
    initPhysicsComponents();
    initSpaceship(gameEngine);
    initAsteroids(gameEngine);
    initCamera(graphicsEngine);
    initSceneryElements(graphicsEngine);
    initLighting(graphicsEngine);

    graphicsEngine.setBackgroundColor(D3DCOLOR_XRGB(0, 6, 8));
    graphicsEngine.enableFog(camera->getFarPlane() - 1000.0f, camera->getFarPlane());   
}

void AsteroidsGameWorld::update( float time )
{
    laserShootDelay -= time;
    cameraChangeDelay -= time;
    spaceship.update(time);
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

bool AsteroidsGameWorld::testCollisionOfLaserWithAllAsteroids(shared_ptr<Laser> laser) {
    vector<shared_ptr<Asteroid> >::iterator it;
    for (it = asteroids.begin(); it != asteroids.end();) {
        if (laserPhysicsComponent->testIntersectionWithAsteroid(*laser.get(), *(*it).get())) {
            POUT("Laser collided with an asteroid");
            shared_ptr<Asteroid> a = *it;
            it = asteroids.erase(it);
            it = fragmentAsteroid(it, a);
            return true;
        } else {
            it++;
        }
    }
    return false;
}

vector<shared_ptr<Asteroid> >::iterator &AsteroidsGameWorld::fragmentAsteroid(vector<shared_ptr<Asteroid> >::iterator &it, shared_ptr<Asteroid> asteroid)
{
    D3DXVECTOR3 scale = asteroid->getScale() / 2.0f;
    if (scale.x < 0.5f || scale.y < 0.5f || scale.z < 0.5f) {
        return it;
    }
    D3DXVECTOR3 dir = D3DXVECTOR3(RANDOM(0.0f, 1.0f), RANDOM(0.0f, 1.0f), RANDOM(0.0f, 1.0f));
    D3DXVec3Normalize(&dir, &dir);

    for (int i = 0; i < 2; i++) {
        shared_ptr<Asteroid> newAst = makeOneAsteroid();
        newAst->setScale(scale * RANDOM(0.8f, 1.2f));
        newAst->setDirection(dir);
        newAst->setPosition(asteroid->getPosition() + 2.0f * dir);
        newAst->setSpeed(asteroid->getSpeed() * RANDOM(0.8f, 1.2f));
        newAst->setRollRotationSpeed(asteroid->getRollRotationSpeed() * RANDOM(1.6f, 2.4f));
        newAst->setPitchRotationSpeed(asteroid->getPitchRotationSpeed() * RANDOM(1.6f, 2.4f));
        newAst->setYawRotationSpeed(asteroid->getYawRotationSpeed() * RANDOM(1.6f, 2.4f));
        it = asteroids.insert(it, newAst);
        dir *= -1.0f;
    }
    return it;
}

void AsteroidsGameWorld::draw( GraphicsEngine &graphicsEngine )
{
    spaceship.draw(graphicsEngine);

    for each (shared_ptr<Asteroid> asteroid in asteroids) {
        asteroid->draw(graphicsEngine);
    }

    for each(shared_ptr<Laser> laser in lasers) {
        laser->draw(graphicsEngine);
    }
    
    drawShipPositionText();
}

void AsteroidsGameWorld::shootLaser()
{
    if (laserShootDelay <= 0.0f) {
        shared_ptr<Laser> laser = shared_ptr<Laser>(new Laser(spaceship.getRotationQuat(), spaceship.getPosition() + spaceship.getDirection() *0.5f, spaceship.getDirection()));
        laser->changeSpeedBy(spaceship.getSpeed());
        laser->init(NULL, laserPhysicsComponent, laserGraphicsComponent);
        lasers.push_back(laser);
        laserShootDelay = LASER_SHOOT_DELAY_MS;
    }
}

void AsteroidsGameWorld::initGraphicsComponents(GraphicsEngine &graphicsEngine) {
    asteroidGraphicsComponent->init(graphicsEngine);
    spaceshipGraphicsComponent->init(graphicsEngine);
    laserGraphicsComponent->init(graphicsEngine);
}

void AsteroidsGameWorld::initPhysicsComponents() {
    spaceshipPhysicsComponent = shared_ptr<PhysicsComponent>(new MoveableObjectPhysicsComponent());
    asteroidPhysicsComponent = spaceshipPhysicsComponent;
    laserPhysicsComponent = shared_ptr<LaserPhysicsComponent>(new LaserPhysicsComponent());
}

void AsteroidsGameWorld::initCamera( GraphicsEngine &graphicsEngine )
{
    FollowCamera *fc = new FollowCamera(&spaceship);
    objectBeingFollowed = &spaceship;
    fc->setThirdPersonCamera();
    usingThirdPersonCamera = true;
    camera = fc;
    camera->setFarPlane(20000.0f);
    graphicsEngine.setCamera(*camera);
}

void AsteroidsGameWorld::initSpaceship( GameEngine &gameEngine )
{
    spaceshipInputComponent->init(&spaceship);
    spaceship.setMinSpeed(0.0f);
    spaceship.init(spaceshipInputComponent, spaceshipPhysicsComponent, spaceshipGraphicsComponent);
}

shared_ptr<Asteroid> AsteroidsGameWorld::makeOneAsteroid() 
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
    return asteroid;
}

void AsteroidsGameWorld::initAsteroids( GameEngine &gameEngine )
{
    float yMin = -100.0f;
    float yMax = 100.0f;
    float minAsteroidScale = 1.0f;
    float maxAsteroidScale = 6.0f;
    float asteroidCreationProbablility = 0.002f;

    for (int i = 0; i < MESH_ROWS; i++) {
        for (int j = 0; j < MESH_COLUMNS; j++) {

            float asteroidCreationDice = RANDOM(0,1);

            if (asteroidCreationProbablility < asteroidCreationDice) {
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

void AsteroidsGameWorld::initLighting(GraphicsEngine &graphicsEngine)
{
    int i = 0;
    initAmbientLighting(graphicsEngine);
    i += initDirectionalLighting(i, graphicsEngine);
    i += initPointLighting(i, graphicsEngine);
}

void AsteroidsGameWorld::initAmbientLighting(GraphicsEngine &graphicsEngine)
{
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
}

int AsteroidsGameWorld::initDirectionalLighting(int lightIndex, GraphicsEngine &graphicsEngine)
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

int AsteroidsGameWorld::initPointLighting(int lightIndex, GraphicsEngine &graphicsEngine)
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

void AsteroidsGameWorld::initSceneryElements( GraphicsEngine &graphicsEngine )
{
    shared_ptr<SceneryElement> earthSceneryElement(new EarthSceneryElement());
    shared_ptr<SceneryElement> sunSceneryElement(new SunSceneryElement());

    earthSceneryElement->init(graphicsEngine);
    sunSceneryElement->init(graphicsEngine);
    graphicsEngine.addSceneryElement(earthSceneryElement);
    graphicsEngine.addSceneryElement(sunSceneryElement);
}

void AsteroidsGameWorld::followNextAsteroid()
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

void AsteroidsGameWorld::followPreviousAsteroid()
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

void AsteroidsGameWorld::followShip()
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
        objectBeingFollowed = &spaceship;
        objectBeingFollowed->setDrawn(usingThirdPersonCamera);
        followCamera->setGameObject(objectBeingFollowed);
        cameraChangeDelay = CAMERA_CHANGE_DELAY_MS;
    }
}

void AsteroidsGameWorld::setFirstPersonCamera()
{
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    usingThirdPersonCamera = false;
    objectBeingFollowed->setDrawn(false);
    followCamera->setFirstPersonCamera();
}

void AsteroidsGameWorld::setThirdPersonCamera()
{
    FollowCamera *followCamera = dynamic_cast<FollowCamera*>(camera);
    if (followCamera == NULL) {
        return;
    }
    usingThirdPersonCamera = true;
    objectBeingFollowed->setDrawn(true);
    followCamera->setThirdPersonCamera();
}

void AsteroidsGameWorld::drawShipPositionText()
{
    static char buffer[256];
    D3DXVECTOR3 position = spaceship.getPosition();
    sprintf_s(buffer, "Position:\n%f\n%f\n%f)", position.x, position.y, position.z);
    FontSystem::DrawText(buffer, 10, 10, D3DCOLOR_XRGB(255,255,255));
}
