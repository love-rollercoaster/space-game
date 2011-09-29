#pragma once

#include <atlbase.h>
#include <d3dx9.h>

#include "GraphicsComponent.h"
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "Block.h"

class BlockGraphicsComponent :
    public GraphicsComponent
{
public:
    BlockGraphicsComponent(void);

    void init(GraphicsEngine &graphicsEngine);
    void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

private:
    static LPCSTR textureLocation;
    static CComPtr<IDirect3DTexture9> texture;
    static CComPtr<ID3DXSprite> sprite;

    static void InitTexture(GraphicsEngine &graphicsEngine);
    static void InitSprite(GraphicsEngine &graphicsEngine);

    static const int NUMBER_OF_VERTICES = 3;
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    CustomVertex vertices[BlockGraphicsComponent::NUMBER_OF_VERTICES];

    D3DXVECTOR3 transformBlockPosition(Block::Position &position);
    D3DCOLOR transformBlockColor(BlockColors::Color color);
};
