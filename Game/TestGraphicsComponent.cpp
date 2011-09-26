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

    vertexBuffer = graphicsEngine.createVertexBuffer(triangle, 3);
}

void TestGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    graphicsEngine.drawVertexBuffer(vertexBuffer);
}
