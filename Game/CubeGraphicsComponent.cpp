// Reference:
// http://www.directxtutorial.com/tutorial9/b-direct3dbasics/dx9B7.aspx

#include "CubeGraphicsComponent.h"

void CubeGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    initVertexBuffer(graphicsEngine);
    initIndexBuffer(graphicsEngine);
}

void CubeGraphicsComponent::initVertexBuffer( GraphicsEngine &graphicsEngine )
{
    CustomVertex vertices[] = {
        { D3DXVECTOR3(-1.0f,  1.0f, -1.0f), D3DCOLOR_XRGB(255,255,255), },
        { D3DXVECTOR3( 1.0f,  1.0f, -1.0f), D3DCOLOR_XRGB(255,255,255), },
        { D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DCOLOR_XRGB(255,255,255), },
        { D3DXVECTOR3( 1.0f, -1.0f, -1.0f), D3DCOLOR_XRGB(255,255,255), },
        { D3DXVECTOR3(-1.0f,  1.0f,  1.0f), D3DCOLOR_XRGB(255,255,255), },
        { D3DXVECTOR3( 1.0f,  1.0f,  1.0f), D3DCOLOR_XRGB(255,255,255), },
        { D3DXVECTOR3(-1.0f, -1.0f,  1.0f), D3DCOLOR_XRGB(255,255,255), },
        { D3DXVECTOR3( 1.0f, -1.0f,  1.0f), D3DCOLOR_XRGB(255,255,255), },
    };

    // create a vertex buffer interface called v_buffer
    graphicsEngine.getDirect3DDevice()->CreateVertexBuffer(
        8 * sizeof(CustomVertex),
        0,
        CUSTOM_FLEXIBLE_VECTOR_FORMAT,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    vertexBuffer->Lock(0, 0, static_cast<void**>(&pVoid), 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    vertexBuffer->Unlock();
}

void CubeGraphicsComponent::initIndexBuffer( GraphicsEngine &graphicsEngine )
{
    short indices[] = {
        0, 1, 2,    // side 1
        2, 1, 3,
        4, 0, 6,    // side 2
        6, 0, 2,
        7, 5, 6,    // side 3
        6, 5, 4,
        3, 1, 7,    // side 4
        7, 1, 5,
        4, 5, 0,    // side 5
        0, 5, 1,
        3, 7, 2,    // side 6
        2, 7, 6,
    };

    graphicsEngine.getDirect3DDevice()->CreateIndexBuffer(36*sizeof(short),
        0,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &indexBuffer,
        NULL);

    VOID *pVoid;
    indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    indexBuffer->Unlock();
}

void CubeGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    performWorldTransformations(gameObject, graphicsEngine);

    graphicsEngine.getDirect3DDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
    graphicsEngine.getDirect3DDevice()->SetIndices(indexBuffer);
    graphicsEngine.getDirect3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12); 
}

void CubeGraphicsComponent::performWorldTransformations( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    Cube *cube = dynamic_cast<Cube*>(&gameObject);

    if (cube == NULL) {
        throw "Can't draw game object with this component.";
    }

    D3DXVECTOR3 position = cube->getPosition();
    D3DXVECTOR3 scale = cube->getScale();

    D3DXMATRIX worldMatrix, matScale, matTranslate, matRotate;

    D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
    worldMatrix = matScale;

    D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
    worldMatrix *= matTranslate;

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);
}


