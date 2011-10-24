#include "SpaceshipGraphicsComponent.h"


SpaceshipGraphicsComponent::SpaceshipGraphicsComponent(void)
{
}


SpaceshipGraphicsComponent::~SpaceshipGraphicsComponent(void)
{
}

void SpaceshipGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    graphicsEngine.loadMesh("resources/meshes/spaceship.x", &spaceshipMesh, &materials, &texture, &numMaterials);
}

void SpaceshipGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    MoveableGameObject *moveableGameObject = dynamic_cast<MoveableGameObject*>(&gameObject);

    if (moveableGameObject == NULL) {
        throw "This component only works with MoveableGameObjects!";
    }

    D3DXMATRIX worldMatrix;

    moveableGameObject->generateTransformationMatrix(&worldMatrix);

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);

    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

    for (DWORD i = 0; i < numMaterials; i++) {
        graphicsEngine.getDirect3DDevice()->SetMaterial(&materials[i]);
        if (texture[i] != NULL) {
            graphicsEngine.getDirect3DDevice()->SetTexture(i, texture[i]);
        }
        if (FAILED(spaceshipMesh->DrawSubset(i))) {
            ERR("Failed to draw spaceship");
        }
    }

    graphicsEngine.getDirect3DDevice()->SetTexture(0, NULL);
}