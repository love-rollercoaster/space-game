#include "TestGraphicsComponent.h"

TestGraphicsComponent::TestGraphicsComponent(void)
{
}

void TestGraphicsComponent::init(GraphicsEngine &graphicsEngine)
{
    CustomVertex vertices[] =
    {
        { 320.0f, 50.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 520.0f, 400.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 120.0f, 400.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    vertexBuffer = graphicsEngine.createVertexBuffer(vertices, TestGraphicsComponent::NUMBER_OF_VERTICES);
}

void TestGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    graphicsEngine.getDirect3DDevice()->SetFVF(CUSTOM_FLEXIBLE_VECTOR_FORMAT);
    graphicsEngine.getDirect3DDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
    graphicsEngine.getDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
