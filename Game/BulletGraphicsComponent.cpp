#include "BulletGraphicsComponent.h"


BulletGraphicsComponent::BulletGraphicsComponent(void)
{
}


BulletGraphicsComponent::~BulletGraphicsComponent(void)
{
}


void BulletGraphicsComponent::init(GraphicsEngine &graphicsEngine)
{
    if (FAILED(D3DXCreateSphere(graphicsEngine.getDirect3DDevice(),
        2.0f, 20, 20, &bulletMesh, NULL))) {
            ERR("Could not load bullet graphics mesh");
    }

}

void BulletGraphicsComponent::draw(GameObject &gameObject, GraphicsEngine &graphicsEngine)
{
    Bullet *bullet = dynamic_cast<Bullet*>(&gameObject);
    
    if (bullet == NULL) {
        throw "This component only works with bullets!";
    }

    D3DXMATRIX worldMatrix;

    bullet->generateTransformationMatrix(&worldMatrix);

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);

    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

    bulletMesh->DrawSubset(0);
}