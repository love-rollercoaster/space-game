#include "LaserGraphicsComponent.h"

const float LaserGraphicsComponent::LASER_RADIUS = 0.08f;
const float LaserGraphicsComponent::LASER_LENGTH = 1.0f;

LaserGraphicsComponent::LaserGraphicsComponent(void)
{
    outerLaserMaterial.Ambient  = D3DXCOLOR(255, 0.0f, 0.0f, 0.4f);
    outerLaserMaterial.Diffuse  = D3DXCOLOR(69, 0.0f, 0.0f, 0.4f);
    outerLaserMaterial.Emissive = D3DXCOLOR(69, 0.0f, 0.0f, 0.5f);
    outerLaserMaterial.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
    outerLaserMaterial.Power    = 0.0f;

    innerLaserMaterial.Ambient  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
    innerLaserMaterial.Diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
    innerLaserMaterial.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
    innerLaserMaterial.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
    innerLaserMaterial.Power    = 0.0f;
}


LaserGraphicsComponent::~LaserGraphicsComponent(void)
{
}


void LaserGraphicsComponent::init(GraphicsEngine &graphicsEngine)
{   
    HRESULT result = D3DXCreateCylinder(
        graphicsEngine.getDirect3DDevice(),
        LASER_RADIUS,
        LASER_RADIUS,
        LASER_LENGTH,
        20,
        20,
        &outerLaserMesh,
        nullptr);

    result |= D3DXCreateCylinder(
        graphicsEngine.getDirect3DDevice(),
        LASER_RADIUS * 0.75f,
        LASER_RADIUS,
        LASER_LENGTH * 1.01f,
        20,
        20,
        &innerLaserMesh,
        nullptr);

    if (FAILED(result)) {
            ERR("Could not load laser graphics mesh");
    }
}

void LaserGraphicsComponent::draw(GameObject &gameObject, GraphicsEngine &graphicsEngine)
{
    Laser *laser = dynamic_cast<Laser*>(&gameObject);

    if (laser == nullptr) {
        throw "This component only works with lasers!";
    }

    D3DXMATRIX worldMatrix;
    laser->generateTransformationMatrix(&worldMatrix);
    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    graphicsEngine.getDirect3DDevice()->SetMaterial(&outerLaserMaterial);
    outerLaserMesh->DrawSubset(0);

    graphicsEngine.getDirect3DDevice()->SetMaterial(&innerLaserMaterial);
    innerLaserMesh->DrawSubset(0);
}