#include "AsteroidGraphicsComponent.h"


AsteroidGraphicsComponent::AsteroidGraphicsComponent(void)
{
}


AsteroidGraphicsComponent::~AsteroidGraphicsComponent(void)
{
}

void AsteroidGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    LPD3DXBUFFER asteroidMaterials;

    if (FAILED(D3DXLoadMeshFromX("resources/meshes/asteroid1.x",
                                 D3DXMESH_MANAGED,
                                 graphicsEngine.getDirect3DDevice(),
                                 NULL,
                                 &asteroidMaterials,
                                 NULL,
                                 &numMaterials,
                                 &asteroidMesh)))
    {
        ERR("Failed to load asteroid mesh");
        return;
    }

    if(FAILED(D3DXCreateTextureFromFileA(graphicsEngine.getDirect3DDevice(),
                                         "resources/textures/asteroid1.tga",
                                         &texture)))
    {
        texture = NULL;
    }

    D3DXMATERIAL* tempMaterials = (D3DXMATERIAL*)asteroidMaterials->GetBufferPointer();
    material = new D3DMATERIAL9[numMaterials];

    for(DWORD i = 0; i < numMaterials; i++)
    {
        material[i] = tempMaterials[i].MatD3D;
        material[i].Ambient = material[i].Diffuse;
    }
}

void AsteroidGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
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
    if (texture != NULL) {
        graphicsEngine.getDirect3DDevice()->SetTexture(0, texture);
    }

    for (DWORD i = 0; i < numMaterials; i++) {
        graphicsEngine.getDirect3DDevice()->SetMaterial(&material[i]);
        if (FAILED(asteroidMesh->DrawSubset(i))) {
            ERR("Failed to draw asteroid");
        }
    }
}