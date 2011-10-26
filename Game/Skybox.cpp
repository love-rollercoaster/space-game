// Reference
// http://www.gameengineer.net/samples-graphics.html

#include "Skybox.h"
#include "GraphicsEngine.h"


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
        sizeof(vertices),
        0,
        D3DFVF_XYZ | D3DFVF_TEX1,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL);

    void* verticesLock;    // a void pointer
    vertexBuffer->Lock(0, sizeof(vertices), static_cast<void**>(&verticesLock), 0);
    memcpy(verticesLock, vertices, sizeof(vertices));
    vertexBuffer->Unlock();
}

void Skybox::initTexture( GraphicsEngine &graphicsEngine )
{
    HRESULT result;

    result  = D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("resources/textures/SkyBox_front5.png"),  &texture[0] );
    result |= D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("resources/textures/SkyBox_back6.png") ,  &texture[1] );
    result |= D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("resources/textures/SkyBox_left2.png") ,  &texture[2] );
    result |= D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("resources/textures/SkyBox_right1.png"),  &texture[3] );
    result |= D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("resources/textures/SkyBox_top3.png")  ,  &texture[4] );
    result |= D3DXCreateTextureFromFile( graphicsEngine.getDirect3DDevice(), ("resources/textures/SkyBox_bottom4.png"), &texture[5] );

    if ( FAILED( result ) )
    {
        ::MessageBox(NULL, "Failed to create the vertex buffer!", "Error in BuildSkybox()", MB_OK | MB_ICONSTOP);
    }
}

void Skybox::draw( Camera &camera, GraphicsEngine &graphicsEngine )
{
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_LIGHTING, false);
    DWORD antialiasedLineEnable;
    graphicsEngine.getDirect3DDevice()->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &antialiasedLineEnable);
    graphicsEngine.getDirect3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, false );

    performWorldTransformations(camera, graphicsEngine);
    
    graphicsEngine.getDirect3DDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
    graphicsEngine.getDirect3DDevice()->SetStreamSource( 0, vertexBuffer, 0, sizeof(TexturedVertex));

    for ( int i = 0; i < 6; ++i )
    {
        graphicsEngine.getDirect3DDevice()->SetTexture( 0, texture[i] );
        graphicsEngine.getDirect3DDevice()->DrawPrimitive( D3DPT_TRIANGLESTRIP, i * 4, 2 );
    }

    graphicsEngine.getDirect3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, true );
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, antialiasedLineEnable);
    graphicsEngine.getDirect3DDevice()->SetTexture( 0, NULL );
}

void Skybox::performWorldTransformations( Camera &camera, GraphicsEngine &graphicsEngine )
{
    D3DXMATRIX worldMatrix, translationMatrix;
    D3DXMatrixIdentity(&worldMatrix);

    D3DXVECTOR3 position = camera.getPosition();
    D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);
    worldMatrix *= translationMatrix;

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);
}
