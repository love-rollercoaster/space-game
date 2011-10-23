#include "TeapotGraphicsComponent.h"
#include "Obstacle.h"

TeapotGraphicsComponent::TeapotGraphicsComponent(void)
    : teapot(NULL)
{
}


TeapotGraphicsComponent::~TeapotGraphicsComponent(void)
{
    if (teapot != NULL) {
        teapot->Release();
    }
}

void TeapotGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    D3DXCreateTeapot(graphicsEngine.getDirect3DDevice(), &teapot, NULL);
}

void TeapotGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    Obstacle *obstacle = dynamic_cast<Obstacle*>(&gameObject);
    
    if (obstacle == NULL) {
        throw "This component only works with obstacles!";
    }

    D3DXVECTOR3 position = obstacle->getPosition();
    D3DXVECTOR3 scale = obstacle->getScale();
    
    D3DXMATRIX worldMatrix, matScale, matTranslate, matRotate;

    D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
    worldMatrix = matScale;

    D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
    worldMatrix *= matTranslate;

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);

    teapot->DrawSubset(0);
}
