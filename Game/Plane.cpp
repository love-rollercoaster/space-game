#include "Plane.h"
#include "PlaneInputComponent.h"
#include "Cube.h"
#include "CubeGraphicsComponent.h"

Plane::Plane(void)
    : camera(NULL)
{
}

Plane::~Plane(void)
{
}

Camera* Plane::getCamera()
{
    return this->camera;
}

void Plane::setCamera( Camera &camera )
{
    this->camera = &camera;
}