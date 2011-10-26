#include "LaserGraphicsComponent.h"


LaserGraphicsComponent::LaserGraphicsComponent(void)
{
    material.Ambient = LASER_AMBIENT_COLOR;
    material.Diffuse = LASER_DIFFUSE_COLOR;
    material.Emissive = LASER_EMISSIVE_COLOR;
    material.Specular = LASER_SPECULAR_COLOR;
    material.Power = LASER_SPECULAR_POWER;
}


LaserGraphicsComponent::~LaserGraphicsComponent(void)
{
}


void LaserGraphicsComponent::init(GraphicsEngine &graphicsEngine)
{
    if (FAILED(D3DXCreateCylinder(graphicsEngine.getDirect3DDevice(),
        LASER_RADIUS, LASER_RADIUS, LASER_LENGTH, 20, 20, &laserMesh, NULL))) {
            ERR("Could not load laser graphics mesh");
    }

}

void LaserGraphicsComponent::draw(GameObject &gameObject, GraphicsEngine &graphicsEngine)
{
    Laser *laser = dynamic_cast<Laser*>(&gameObject);
    
    if (laser == NULL) {
        throw "This component only works with lasers!";
    }

    D3DXMATRIX worldMatrix;

    laser->generateTransformationMatrix(&worldMatrix);

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);

    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

    graphicsEngine.getDirect3DDevice()->SetMaterial(&material);
    laserMesh->DrawSubset(0);
}