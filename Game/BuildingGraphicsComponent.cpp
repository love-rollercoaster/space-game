#include "BuildingGraphicsComponent.h"

void BuildingGraphicsComponent::initVertexBuffer( GraphicsEngine &graphicsEngine )
{
    DWORD darkGrey = D3DCOLOR_XRGB(5,5,5);
    DWORD grey     = D3DCOLOR_XRGB(40,40,40);
    DWORD light    = D3DCOLOR_XRGB(200,215,215);
    CustomVertex vertices[] = {
        { D3DXVECTOR3(-1.0f,  10.0f, -1.0f), darkGrey, },
        { D3DXVECTOR3( 1.0f,  10.0f, -1.0f), grey, },
        { D3DXVECTOR3(-1.0f, -10.0f, -1.0f), grey, },
        { D3DXVECTOR3( 1.0f, -10.0f, -1.0f), grey, },
        { D3DXVECTOR3(-1.0f,  10.0f,  1.0f), grey, },
        { D3DXVECTOR3( 1.0f,  10.0f,  1.0f), light, },
        { D3DXVECTOR3(-1.0f, -10.0f,  1.0f), grey, },
        { D3DXVECTOR3( 1.0f, -10.0f,  1.0f), grey, },
    };

    // create a vertex buffer interface called v_buffer
    graphicsEngine.getDirect3DDevice()->CreateVertexBuffer(8 * sizeof(CustomVertex),
        0,
        CUSTOM_FLEXIBLE_VECTOR_FORMAT,
        D3DPOOL_MANAGED,
        &this->vertexBuffer,
        NULL);

    void* pVoid;    // a void pointer
    // lock v_buffer and load the vertices into it
    vertexBuffer->Lock(0, 0, static_cast<void**>(&pVoid), 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    vertexBuffer->Unlock();
}
