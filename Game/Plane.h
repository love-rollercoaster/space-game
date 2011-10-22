#pragma once

#include "GameObject.h"
#include "Camera.h"

class PlaneInputComponent;

class Plane
    : public GameObject
{
public:
    Plane(void);
    ~Plane(void);

    Camera* getCamera(); // Maybe make this friend of plane input component?
    void setCamera(Camera &camera);

private:
    Camera *camera;
};

