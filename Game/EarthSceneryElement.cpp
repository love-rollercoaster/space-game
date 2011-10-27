#include "EarthSceneryElement.h"
#include "GraphicsEngine.h"
#include "Camera.h"
#include "Log.h"

float EarthSceneryElement::Z_CAMERA_POSITION_MULTIPLIER = 0.95f;

EarthSceneryElement::EarthSceneryElement(void)
    : texture(nullptr)
    , vertexBuffer(nullptr)
{
}

EarthSceneryElement::~EarthSceneryElement(void)
{
    if (texture != nullptr) {
        texture->Release();
    }

    if (vertexBuffer != nullptr) {
        vertexBuffer->Release();
    }
}

void EarthSceneryElement::init( GraphicsEngine &graphicsEngine )
{
    initVertexBuffer(graphicsEngine);
    initTexture(graphicsEngine);
}

void EarthSceneryElement::draw( Camera &camera, GraphicsEngine &graphicsEngine )
{
    performWorldTransformations(camera, graphicsEngine);

    graphicsEngine.getDirect3DDevice()->SetFVF(TEXTURE_FVF);
    graphicsEngine.getDirect3DDevice()->SetStreamSource( 0, vertexBuffer, 0, sizeof(TexturedVertex));

    graphicsEngine.getDirect3DDevice()->SetTexture( 0, texture );
    graphicsEngine.getDirect3DDevice()->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

    graphicsEngine.getDirect3DDevice()->SetTexture( 0, NULL );
}

void EarthSceneryElement::initVertexBuffer(GraphicsEngine &graphicsEngine)
{
    TexturedVertex vertices[] = {
        {D3DXVECTOR3( 10000.0f, -10000.0f, -15000.0f),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3( 10000.0f,  10000.0f, -15000.0f),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3(-10000.0f, -10000.0f, -15000.0f),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3(-10000.0f,  10000.0f, -15000.0f),  D3DXVECTOR2(1.0f, 0.0f) },
    };

    // create a vertex buffer interface called v_buffer
    graphicsEngine.getDirect3DDevice()->CreateVertexBuffer(
        sizeof(vertices),
        0,
        TEXTURE_FVF,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL);

    void* verticesLock;
    vertexBuffer->Lock(0, sizeof(vertices), static_cast<void**>(&verticesLock), 0);
    memcpy(verticesLock, vertices, sizeof(vertices));
    vertexBuffer->Unlock();
}

void EarthSceneryElement::initTexture( GraphicsEngine &graphicsEngine )
{
    if ( FAILED(D3DXCreateTextureFromFile(graphicsEngine.getDirect3DDevice(), ("resources/textures/earth.png"),  &texture)) )
    {
        ERR("Failed to create the earth texture!");
    }
}

void EarthSceneryElement::performWorldTransformations( Camera &camera, GraphicsEngine &graphicsEngine )
{
    D3DXMATRIX worldMatrix, translationMatrix;
    D3DXMatrixIdentity(&worldMatrix);

    D3DXVECTOR3 cameraPosition = camera.getPosition();
    
    
    D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z*Z_CAMERA_POSITION_MULTIPLIER);


    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);
}



