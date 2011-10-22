#pragma once

#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "CubeGraphicsComponent.h"

using std::vector;

class PlaneInputComponent;

class Plane
    : public GameObject
{
public:
    Plane(void);
    ~Plane(void);

    Camera* getCamera(); // Maybe make this friend of plane input component?
    void setCamera(Camera &camera);

    void draw(GraphicsEngine &graphicsEngine);

    void shoot();
    void setBulletGraphicsComponent(CubeGraphicsComponent &bulletGraphicsComponent);

private:
    Camera *camera;
    CubeGraphicsComponent bulletGraphicsComponent;

    vector<Cube> bullets;
};

