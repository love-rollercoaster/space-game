#pragma once

#include <memory>
#include <vector>
#include "GameWorld.h"
#include "GameObject.h"
#include "QuatCamera.h"
#include "MeshSurfaceGraphicsComponent.h"
#include "Plane.h"
#include "PlaneInputComponent.h"
#include "MoveableGameObject.h"
#include "FollowCamera.h"
#include "Asteroid.h"
#include "Laser.h"
#include "MoveableObjectPhysicsComponent.h"
#include "LaserPhysicsComponent.h"

#define LASER_SHOOT_DELAY_MS 300.0f
#define CAMERA_CHANGE_DELAY_MS 100.0f

using std::vector;
using std::tr1::shared_ptr;

class TestGameWorld :
    public GameWorld
{
public:
    TestGameWorld(void);
    ~TestGameWorld(void);

    void init(GameEngine &gameEngine);
    void update(float time);
    void draw(GraphicsEngine &graphicsEngine);
    void shootLaser();
    void followNextAsteroid();
    void followPreviousAsteroid();
    void followShip();
    void setFirstPersonCamera();
    void setThirdPersonCamera();

private:
    Plane plane;
    Camera* camera;
    MoveableGameObject *objectBeingFollowed;
    float laserShootDelay;
    float cameraChangeDelay;
    unsigned int asteroidBeingFollowed;
    bool cameraFollowingShip;
    bool usingThirdPersonCamera;

    shared_ptr<InputComponent> planeInputComponent;
    shared_ptr<GraphicsComponent> spaceshipGraphicsComponent;
    shared_ptr<GraphicsComponent> laserGraphicsComponent;
    shared_ptr<GraphicsComponent> asteroidGraphicsComponent;
    shared_ptr<PhysicsComponent> spaceshipPhysicsComponent;
    shared_ptr<LaserPhysicsComponent> laserPhysicsComponent;
    shared_ptr<PhysicsComponent> asteroidPhysicsComponent;

    vector<shared_ptr<Asteroid> > asteroids;
    vector<shared_ptr<Laser> > lasers;

    void initGraphicsComponents(GraphicsEngine &graphicsEngine);
    void initPhysicsComponents();
    void initSpaceship(GameEngine &gameEngine);
    void initAsteroids(GameEngine &gameEngine);
    shared_ptr<Asteroid> makeOneAsteroid();
    void initLighting(GraphicsEngine &graphicsEngine);
    void initAmbientLighting(GraphicsEngine &graphicsEngine);
    void initCamera(GraphicsEngine &graphicsEngine);
    vector<shared_ptr<Asteroid> >::iterator &fragmentAsteroid(vector<shared_ptr<Asteroid> >::iterator &it, shared_ptr<Asteroid> asteroid);
    int initDirectionalLighting(int lightIndex, GraphicsEngine &graphicsEngine);
    int initPointLighting(int lightIndex, GraphicsEngine &graphicsEngine);
    void initSceneryElements(GraphicsEngine &graphicsEngine);
    bool testCollisionOfLaserWithAllAsteroids(shared_ptr<Laser> laser);

    void drawShipPositionText();
};
