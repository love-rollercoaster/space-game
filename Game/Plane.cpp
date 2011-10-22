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

void Plane::shoot()
{
    /*
    Cube cube;
    D3DXVECTOR3 position = *camera->getPosition();

    cube.setPosition(position);
    cube.setScale(2.0f,2.0f,2.0f);
    cube.init(NULL, NULL, &bulletGraphicsComponent);

    bullets.push_back(cube);
    */
}

void Plane::setBulletGraphicsComponent( CubeGraphicsComponent &bulletGraphicsComponent )
{
    this->bulletGraphicsComponent = bulletGraphicsComponent;
}

void Plane::draw( GraphicsEngine &graphicsEngine )
{
    for each (Cube cube in bullets) {
        cube.draw(graphicsEngine);
    }
}
