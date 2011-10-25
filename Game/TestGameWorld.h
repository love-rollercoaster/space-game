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
    //    vector<MoveableGameObject*> moveableGameObjects;

    vector<shared_ptr<Asteroid> > asteroids;

    void initSpaceship(GameEngine &gameEngine);
    void initAsteroids(GameEngine &gameEngine);
};
