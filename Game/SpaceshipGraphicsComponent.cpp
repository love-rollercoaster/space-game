#include "SpaceshipGraphicsComponent.h"



SpaceshipGraphicsComponent::SpaceshipGraphicsComponent(void)
{
}


SpaceshipGraphicsComponent::~SpaceshipGraphicsComponent(void)
{
}

void SpaceshipGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    graphicsEngine.loadMesh("resources/meshes/spaceship.x", &spaceshipMesh, &materials, &textures, &numMaterials);
    D3DXCreateTextureFromFile(graphicsEngine.getDirect3DDevice(), "resources/textures/spaceship_fullspeed.jpg", &fullSpeedTexture); 
    initEffect(graphicsEngine);
}

void SpaceshipGraphicsComponent::initEffect( GraphicsEngine &graphicsEngine )
{
    ID3DXBuffer *errors = nullptr;
    D3DXCreateEffectFromFile(
        graphicsEngine.getDirect3DDevice(),
        "resources/effects/spaceshipShader.fx",
        0,0, D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, 0,
        &meshEffect,
        &errors);

    if (errors != NULL) {
        MessageBox(0, (char*) errors->GetBufferPointer(), 0, 0);
    }

    techniqueHandle        = meshEffect->GetTechniqueByName("spaceshipShaderTechnique"); 
    stoppedTextureHandle   = meshEffect->GetParameterByName(NULL, "stoppedTexture");
    fullSpeedTextureHandle = meshEffect->GetParameterByName(NULL, "fullSpeedTexture");
    hWorldMat   = meshEffect->GetParameterByName(NULL, "worldMatrix");
    hViewMat    = meshEffect->GetParameterByName(NULL, "viewMatrix");
    hProjMat    = meshEffect->GetParameterByName(NULL, "projectionMatrix");
    speedHandle = meshEffect->GetParameterByName(NULL, "speed");
}

void SpaceshipGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    MoveableGameObject *moveableGameObject = dynamic_cast<MoveableGameObject*>(&gameObject);

    if (moveableGameObject == NULL) {
        throw "This component only works with MoveableGameObjects!";
    }

    D3DXMATRIX worldMatrix, normalizedRotation;

    D3DXMatrixRotationYawPitchRoll(&normalizedRotation, D3DXToRadian(90.0f), 0.0f, 0.0f);
    moveableGameObject->generateTransformationMatrix(&worldMatrix);
    // graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &(normalizedRotation * worldMatrix));
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
    meshEffect->SetMatrix(hWorldMat, &(normalizedRotation * worldMatrix)); 
    meshEffect->SetMatrix(hViewMat,  &graphicsEngine.getViewMatrix());  
    meshEffect->SetMatrix(hProjMat,  &graphicsEngine.getProjectionMatrix());

    LPDIRECT3DTEXTURE9 stoppedTexture = textures[STOPPED_TEXTURE_INDEX];

    meshEffect->SetTexture(stoppedTextureHandle, stoppedTexture);
    meshEffect->SetTexture(fullSpeedTextureHandle, fullSpeedTexture);
    meshEffect->SetTechnique(techniqueHandle);

    float speedPercentage = moveableGameObject->getSpeed() / moveableGameObject->getMaxSpeed();
    
    static bool bacon = false;
    if (!bacon) {
        ERR("BACON: " << speedPercentage);
        bacon = true;
    }
    
    meshEffect->SetFloat(speedHandle, speedPercentage);

    unsigned int passCount = 0;
    meshEffect->Begin(&passCount, 0);

    for (unsigned int i = 0; i < passCount; i++) {
        meshEffect->BeginPass(i);
        for (DWORD i = 0; i < numMaterials; i++) {
            graphicsEngine.getDirect3DDevice()->SetMaterial(&materials[i]);
            // if (textures[i] != NULL) {
            //     graphicsEngine.getDirect3DDevice()->SetTexture(i, textures[i]);
            // }
            if (FAILED(spaceshipMesh->DrawSubset(i))) {
                ERR("Failed to draw spaceship");
            }
        }
        meshEffect->EndPass();
    }
     meshEffect->End();

    graphicsEngine.getDirect3DDevice()->SetTexture(0, NULL);
}
