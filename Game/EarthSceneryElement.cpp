#include "EarthSceneryElement.h"
#include "GraphicsEngine.h"
#include "Camera.h"
#include "Log.h"

// TODO:
// Since the earth does have a position in the world space (unlike the sun or the skybox),
// it should be refactored to a game object. For now however, this is fine.

float EarthSceneryElement::Z_CAMERA_POSITION_MULTIPLIER = 0.2f;
float EarthSceneryElement::EARTH_RADIUS = 1000.0f;
D3DXVECTOR3 EarthSceneryElement::EARTH_POSITION = D3DXVECTOR3(0.0f, 0.0f, -1500.0f);

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
    D3DXVECTOR3 pos = EARTH_POSITION;

    TexturedVertex vertices[] = {
        {D3DXVECTOR3( pos.x + EARTH_RADIUS, pos.y - EARTH_RADIUS, pos.z),  D3DXVECTOR2(0.0f, 1.0f) },
        {D3DXVECTOR3( pos.x + EARTH_RADIUS, pos.y + EARTH_RADIUS, pos.z),  D3DXVECTOR2(0.0f, 0.0f) },
        {D3DXVECTOR3( pos.x - EARTH_RADIUS, pos.y - EARTH_RADIUS, pos.z),  D3DXVECTOR2(1.0f, 1.0f) },
        {D3DXVECTOR3( pos.x - EARTH_RADIUS,  pos.y + EARTH_RADIUS, pos.z),  D3DXVECTOR2(1.0f, 0.0f) },
    };

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

D3DXVECTOR3 EarthSceneryElement::GetPosition() {
    return EARTH_POSITION;
}
