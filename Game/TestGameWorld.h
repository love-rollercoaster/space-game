#pragma once

#include "GameWorld.h"
#include "GameObject.h"
#include "QuatCamera.h"
#include "MeshSurfaceGraphicsComponent.h"
#include "Plane.h"
#include "PlaneInputComponent.h"

class TestGameWorld :
    public GameWorld
{
public:
    TestGameWorld(void);
    ~TestGameWorld(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    QuatCamera camera;
    GameObject mesh;
    Plane plane;
    MeshSurfaceGraphicsComponent meshSurfaceGraphicsComponent;
    PlaneInputComponent planeInputComponent;

    void initCamera(GameEngine &gameEngine);
    void initPlane(GameEngine &gameEngine);
    void initMesh(GameEngine &gameEngine);
};
