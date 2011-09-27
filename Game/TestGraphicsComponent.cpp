#include "TestGraphicsComponent.h"

TestGraphicsComponent::TestGraphicsComponent(void)
    : GraphicsComponent("TestGraphicsComponent")
{
}

void TestGraphicsComponent::init(GraphicsEngine &graphicsEngine)
{
    CustomVertex triangle[] = {
        { 2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { -2.5f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    vertexBuffer = graphicsEngine.createVertexBuffer(triangle, sizeof(triangle));
}

void TestGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    D3DXMATRIX matRotateZ;
    static float index = 0.0f;
    index += 0.05f;

    D3DXMatrixRotationZ(&matRotateZ, index);

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &matRotateZ);

    D3DXMATRIX matView; // the view transform matrix

    D3DXMatrixLookAtLH(&matView,
                       &D3DXVECTOR3 (0.0f, 0.0f, 50.0f),  // the camera position
                       &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),   // the look-at position
                       &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));  // the up direction

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    D3DXMATRIX matProjection;     // the projection transform matrix

    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),
        800 / 600.0, // TODO: Get this from graphics engine?
        1.0f,
        50.0f);

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

    graphicsEngine.drawVertexBuffer(vertexBuffer);
}
