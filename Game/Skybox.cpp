#include "Skybox.h"

// Reference
// http://www.gameengineer.net/samples-graphics.html


Skybox::Skybox(void)
{
}


Skybox::~Skybox(void)
{
}

void Skybox::init(GraphicsEngine &graphicsEngine) {
    initVertexBuffer(graphicsEngine);
    initTexture(graphicsEngine);
}

void Skybox::initVertexBuffer( GraphicsEngine &graphicsEngine )
{
    TexturedVertex vertices[] =
    {
        // Front quad, NOTE: All quads face inward
        {D3DXVECTOR3(-10.0f, -10.0f,  10.0f),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3(-10.0f,  10.0f,  10.0f),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3( 10.0f, -10.0f,  10.0f),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3( 10.0f,  10.0f,  10.0f),  D3DXVECTOR2(1.0f, 0.0f) },

        // Back quad
        {D3DXVECTOR3( 10.0f, -10.0f, -10.0f),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3( 10.0f,  10.0f, -10.0f),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3(-10.0f, -10.0f, -10.0f),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3(-10.0f,  10.0f, -10.0f),  D3DXVECTOR2(1.0f, 0.0f) },

        // Left quad
        {D3DXVECTOR3(-10.0f, -10.0f, -10.0f),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3(-10.0f,  10.0f, -10.0f),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3(-10.0f, -10.0f,  10.0f),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3(-10.0f,  10.0f,  10.0f),  D3DXVECTOR2(1.0f, 0.0f) },

        // Right quad
        {D3DXVECTOR3( 10.0f, -10.0f,  10.0f),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3( 10.0f,  10.0f,  10.0f),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3( 10.0f, -10.0f, -10.0f),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3( 10.0f,  10.0f, -10.0f),  D3DXVECTOR2(1.0f, 0.0f) },

        // Top quad
        {D3DXVECTOR3(-10.0f,  10.0f,  10.0f),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3(-10.0f,  10.0f, -10.0f),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3( 10.0f,  10.0f,  10.0f),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3( 10.0f,  10.0f, -10.0f),  D3DXVECTOR2(1.0f, 0.0f) },

        // Bottom quad
        {D3DXVECTOR3(-10.0f, -10.0f, -10.0f),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3(-10.0f, -10.0f,  10.0f),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3( 10.0f, -10.0f, -10.0f),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3( 10.0f, -10.0f,  10.0f),  D3DXVECTOR2(1.0f, 0.0f) }
    };

    // create a vertex buffer interface called v_buffer
    graphicsEngine.getDirect3DDevice()->CreateVertexBuffer(
        24 * sizeof(TexturedVertex),
        0,
        D3DFVF_XYZ | D3DFVF_TEX1,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL);

    VOID* pVoid;    // a void pointer
    vertexBuffer->Lock(0, 0, static_cast<void**>(&pVoid), 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    vertexBuffer->Unlock();
}

void Skybox::initTexture( GraphicsEngine &graphicsEngine )
{
    D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("SkyBox_Front.jpg") , &texture[0] );
    D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("SkyBox_Back.jpg")  , &texture[1] );
    D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("SkyBox_Left.jpg")  , &texture[2] );
    D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("SkyBox_Right.jpg") , &texture[3] );
    D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("SkyBox_Top.jpg")   , &texture[4] );
    HRESULT res = D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("SkyBox_Bottom.jpg"), &texture[5] );

    if ( FAILED( res ) )
    {
        ::MessageBox(NULL, "Failed to create the vertex buffer!", "Error in BuildSkybox()", MB_OK | MB_ICONSTOP);
    }
}

void Skybox::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    graphicsEngine.getDirect3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, false );

    performWorldTransformations(gameObject, graphicsEngine);
    
    graphicsEngine.getDirect3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
    graphicsEngine.getDirect3DDevice()->SetStreamSource( 0, vertexBuffer, 0, sizeof(TexturedVertex));

    for ( ULONG i = 0; i < 6; ++i )
    {
        graphicsEngine.getDirect3DDevice()->SetTexture( 0, texture[i] );
        graphicsEngine.getDirect3DDevice()->DrawPrimitive( D3DPT_TRIANGLESTRIP, i * 4, 2 );

    } 

    graphicsEngine.getDirect3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, true );
    graphicsEngine.getDirect3DDevice()->SetFVF(CUSTOM_FLEXIBLE_VECTOR_FORMAT);
}

void Skybox::performWorldTransformations( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    D3DXMATRIX worldMatrix, matTranslate;
    D3DXMatrixIdentity(&worldMatrix);

    D3DXVECTOR3 position = camera->getPosition();
    D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
    worldMatrix *= matTranslate;

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);
}
