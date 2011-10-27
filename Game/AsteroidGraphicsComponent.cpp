#include "AsteroidGraphicsComponent.h"


AsteroidGraphicsComponent::AsteroidGraphicsComponent(void)
{
}


AsteroidGraphicsComponent::~AsteroidGraphicsComponent(void)
{
}

void AsteroidGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    graphicsEngine.loadMesh("resources/meshes/asteroid.x", &asteroidMesh, &materials, &texture, &numMaterials);
}

void AsteroidGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
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
            graphicsEngine.getDirect3DDevice()->SetTexture(0, texture[i]);
        }
        if (FAILED(asteroidMesh->DrawSubset(i))) {
            ERR("Failed to draw asteroid");
        }
    }

    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

    graphicsEngine.getDirect3DDevice()->SetTexture(0, NULL);
}