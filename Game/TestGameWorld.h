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

private:
    Camera* camera;
    Plane plane;
    shared_ptr<PlaneInputComponent> planeInputComponent;
    shared_ptr<GraphicsComponent> spaceshipGraphicsComponent;
    shared_ptr<GraphicsComponent> laserGraphicsComponent;
    //    vector<MoveableGameObject*> moveableGameObjects;

    vector<shared_ptr<Asteroid> > asteroids;
    vector<shared_ptr<Laser> > lasers;

    void initSpaceship(GameEngine &gameEngine);
    void initAsteroids(GameEngine &gameEngine);
    void initLighting(GraphicsEngine &graphicsEngine);
    void initAmbientLighting(GraphicsEngine &graphicsEngine);
    int initDirectionalLighting(int lightIndex, GraphicsEngine &graphicsEngine);
    int initPointLighting(int lightIndex, GraphicsEngine &graphicsEngine);
};
