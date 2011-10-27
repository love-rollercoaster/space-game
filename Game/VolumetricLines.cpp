#include "VolumetricLines.h"
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "Laser.h"
#include "Log.h"

#define THICKNESS 1.0f
#define LENGHT 1.0f

VolumetricLines::VolumetricLines(void)
    : texture(nullptr)
    , effect(nullptr)
{
}


VolumetricLines::~VolumetricLines(void)
{
}

void VolumetricLines::initVertices()
{
    D3DXVECTOR3 v0(0.0f, 0.0f, -0.5f);
    D3DXVECTOR3 v1(0.0f, 0.0f,  0.5f);

    vertices[0].pos = v0;		vertices[0].otherPos = v1;
    vertices[1].pos = v1;		vertices[1].otherPos = v0;
    vertices[2].pos = v0;		vertices[2].otherPos = v1;
    vertices[3].pos = v1;		vertices[3].otherPos = v0;

    vertices[0].thickness = D3DXVECTOR3( -THICKNESS, 0.f, THICKNESS * 0.5f );
    vertices[1].thickness = D3DXVECTOR3(  THICKNESS, 0.f, THICKNESS * 0.5f );
    vertices[2].thickness = D3DXVECTOR3(  THICKNESS, 0.f, THICKNESS * 0.5f );
    vertices[3].thickness = D3DXVECTOR3( -THICKNESS, 0.f, THICKNESS * 0.5f );

    vertices[0].texOffset = D3DXVECTOR4( THICKNESS, THICKNESS, 0.f, 0.f );
    vertices[1].texOffset = D3DXVECTOR4( THICKNESS, THICKNESS, 0.25f, 0.f );
    vertices[2].texOffset = D3DXVECTOR4( THICKNESS, THICKNESS, 0.f, 0.25f );
    vertices[3].texOffset = D3DXVECTOR4( THICKNESS, THICKNESS, 0.25f, 0.25f );
}

void VolumetricLines::initTexture( GraphicsEngine &graphicsEngine )
{
    HRESULT result = D3DXCreateTextureFromFile( 
                        graphicsEngine.getDirect3DDevice(),
                        TEXT("resources/textures/1d_INNER1.png"),
                        &texture
                     );

    if( FAILED( result ) ) {
        ERR("Could not load volumetric line texture!");
    }
}

void VolumetricLines::initEffect( GraphicsEngine &graphicsEngine )
{
    LPD3DXBUFFER pErrors = NULL;
    HRESULT hr = D3DXCreateEffectFromFile(
        graphicsEngine.getDirect3DDevice(),
        TEXT("resources/effects/VolumeLines.fx"),
        NULL,
        NULL,
        0,
        NULL,
        &effect,
        &pErrors
        );

    if( FAILED( hr ) )
    {
        ERR("Error occurred when loading effect for volumetric line.");
        if( pErrors )
        {
            ERR("Effect error in volumetric lines: " << (LPCSTR)pErrors->GetBufferPointer());
            pErrors->Release();
        }
    }
}

void VolumetricLines::init( GraphicsEngine &graphicsEngine )
{   
    initVertices();
    initTexture(graphicsEngine);
    initEffect(graphicsEngine);

    effect->SetTexture( "lineTexture", texture );
}


void VolumetricLines::draw(GameObject &gameObject, GraphicsEngine &graphicsEngine)
{
    Laser *laser = dynamic_cast<Laser*>(&gameObject);

    if (laser == NULL) {
        throw "This component only works with lasers!";
    }

    D3DXMATRIX worldMatrix;

    
    laser->generateTransformationMatrix(&worldMatrix);
    // graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);

    D3DXVECTOR3 v0 = laser->getPosition();
    D3DXVECTOR3 v1 = laser->getDirection() + laser->getPosition();

    vertices[0].pos = v0;		vertices[0].otherPos = v1;
    vertices[1].pos = v1;		vertices[1].otherPos = v0;
    vertices[2].pos = v0;		vertices[2].otherPos = v1;
    vertices[3].pos = v1;		vertices[3].otherPos = v0;

    UINT passes = 0;
    if( SUCCEEDED( effect->Begin( &passes, 0 ) ) )
    {
        effect->BeginPass( 0 );
        graphicsEngine.getDirect3DDevice()->SetFVF( Vertex::FVF );
        graphicsEngine.getDirect3DDevice()->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, vertices, sizeof( Vertex ) );
        effect->EndPass();
        effect->End();
    }
}