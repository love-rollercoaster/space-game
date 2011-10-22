#pragma once

#include <vector>
#include "GameWorld.h"
#include "GameObject.h"
#include "QuatCamera.h"
#include "MeshSurfaceGraphicsComponent.h"
#include "Plane.h"
#include "PlaneInputComponent.h"
#include "Cube.h"
#include "BuildingGraphicsComponent.h"

using std::vector;

class TestGameWorld :
    public GameWorld
{
public:
    TestGameWorld(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    QuatCamera camera;
    Plane plane;
    MeshSurfaceGraphicsComponent meshSurfaceGraphicsComponent;
    PlaneInputComponent planeInputComponent;

    void initCamera(GameEngine &gameEngine);
    void initPlane(GameEngine &gameEngine);
    void initMesh(GameEngine &gameEngine);
    void initObstacles(GameEngine &gameEngine);

    BuildingGraphicsComponent buildingGraphicsComponent;
    vector<Cube*> obstacles;
};
