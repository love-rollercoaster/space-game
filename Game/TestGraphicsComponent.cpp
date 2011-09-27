#include "TestGraphicsComponent.h"

TestGraphicsComponent::TestGraphicsComponent(void)
    : GraphicsComponent("TestGraphicsComponent")
{
}

void TestGraphicsComponent::init(GraphicsEngine &graphicsEngine)
{
    vertices[0].position.x = 0.0f;
    vertices[0].position.y = -0.5f;
    vertices[0].color = D3DCOLOR_XRGB(0, 0, 255);

    vertices[1].position.x = 0.5;
    vertices[1].position.y = 0.5;
    vertices[1].color = D3DCOLOR_XRGB(0, 255, 0);

    vertices[2].position.x = -0.5;
    vertices[2].position.y = 0.5f;
    vertices[2].color = D3DCOLOR_XRGB(255, 0, 0);

    vertices[0].position.z = vertices[1].position.z = vertices[2].position.z = 0.0f;
    vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = 1.0f;

    vertexBuffer = graphicsEngine.createVertexBuffer(vertices, TestGraphicsComponent::NUMBER_OF_VERTICES);
}

void TestGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    D3DXMATRIX matScale;
    D3DXMATRIX matTranslate;
    D3DXMATRIX matTransform;
    D3DXMatrixTranslation(&matTranslate, gameObject.getPosition().x, gameObject.getPosition().y, 0.0f);
    D3DXMatrixScaling(&matScale, 100.0f, 100.0f, 0.0f);
    matTransform = matScale * matTranslate;

    CustomVertex *newVertices;
    vertexBuffer->Lock(0,
                       sizeof(CustomVertex) * TestGraphicsComponent::NUMBER_OF_VERTICES,
                       ((void**)&newVertices),
                       0);
    memcpy(newVertices, this->vertices, sizeof(CustomVertex) * TestGraphicsComponent::NUMBER_OF_VERTICES);

    for (int i = 0; i < TestGraphicsComponent::NUMBER_OF_VERTICES; i++) {
        D3DXVec3TransformCoord(&newVertices[i].position, &this->vertices[i].position, &matTransform);
    }

    vertexBuffer->Unlock();

    graphicsEngine.getDirect3DDevice()->SetFVF(CUSTOM_FLEXIBLE_VECTOR_FORMAT);
    graphicsEngine.getDirect3DDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
    graphicsEngine.getDirect3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
