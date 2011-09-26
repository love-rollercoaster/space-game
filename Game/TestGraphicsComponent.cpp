#include "TestGraphicsComponent.h"


TestGraphicsComponent::TestGraphicsComponent(void)
{
}

TestGraphicsComponent::~TestGraphicsComponent(void)
{
}

void TestGraphicsComponent::init(GraphicsEngine &graphicsEngine)
{
    CustomVertex triangle[] = {
        { 400.0f, 62.5f,  0.5f, 1.0f, D3DCOLOR_XRGB(0,   0,   255) },
        { 650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0,   255, 0  ) },
        { 150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0,   0  ) },
    };

    graphicsEngine.getDirect3DDevice()->CreateVertexBuffer(3 * sizeof(CustomVertex),
        0,
        CUSTOM_FLEXIBLE_VECTOR_FORMAT,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL);

    VOID* pVoid;
    vertexBuffer->Lock(0, 0, static_cast<void**>(&pVoid), 0);
    memcpy(pVoid, triangle, sizeof(triangle));
    vertexBuffer->Unlock();

}

void TestGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    graphicsEngine.getDirect3DDevice()->SetFVF(CUSTOM_FLEXIBLE_VECTOR_FORMAT);
    graphicsEngine.getDirect3DDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
    graphicsEngine.getDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
