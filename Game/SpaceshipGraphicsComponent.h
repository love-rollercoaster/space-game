#pragma once
#include "graphicscomponent.h"
#include "MoveableGameObject.h"
#include "Log.h"

#define STOPPED_TEXTURE_INDEX    0
#define FULL_SPEED_TEXTURE_INDEX 1

class SpaceshipGraphicsComponent :
    public GraphicsComponent
{
public:
    SpaceshipGraphicsComponent(void);
    ~SpaceshipGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    LPDIRECT3DTEXTURE9 *textures;
    D3DMATERIAL9* materials;
    ID3DXEffect* meshEffect;
    LPD3DXMESH spaceshipMesh;
    LPDIRECT3DTEXTURE9 fullSpeedTexture;
    D3DXHANDLE stoppedTextureHandle;
    D3DXHANDLE fullSpeedTextureHandle;
    D3DXHANDLE techniqueHandle;
    D3DXHANDLE hWorldMat;
    D3DXHANDLE hViewMat;
    D3DXHANDLE hProjMat;
    D3DXHANDLE speedHandle;
    DWORD numMaterials;

    void initEffect(GraphicsEngine &graphicsEngine);
};