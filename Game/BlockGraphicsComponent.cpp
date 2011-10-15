#include "BlockGraphicsComponent.h"
#include <sstream>

CComPtr<ID3DXSprite> BlockGraphicsComponent::sprite = NULL;
CComPtr<IDirect3DTexture9> BlockGraphicsComponent::texture = NULL;

// FIXME
LPCSTR BlockGraphicsComponent::textureLocation = "..\\block.png";

using std::stringstream;

void BlockGraphicsComponent::InitTexture(GraphicsEngine &graphicsEngine)
{
    // WTF Fix this OMG noob
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);

	string cwd(buffer);
	stringstream filepath(stringstream::out);

    filepath << cwd.substr(0, cwd.find_last_of("\\")) << "\\" << textureLocation;

    if (FAILED(D3DXCreateTextureFromFileEx(
        graphicsEngine.getDirect3DDevice(), // the device pointer
        filepath.str().c_str(),       // the new file name
        D3DX_DEFAULT_NONPOW2,		  // exact width
        D3DX_DEFAULT_NONPOW2,		  // exact height
        D3DX_DEFAULT,				  // full mip-map chains
        NULL,						  // regular usage
        D3DFMT_A8R8G8B8,			  // 32-bit pixels with alpha
        D3DPOOL_MANAGED,		      // typical memory handling
        D3DX_DEFAULT,			      // no filtering
        D3DX_DEFAULT,				  // no mip filtering
        0,                            // the color key that will be transparent. 0 for none
        NULL,                         // no image info struct
        NULL,                         // not using 256 colors
        &texture				      // load to sprite
        )))
   {
       throw std::runtime_error("Could not initialize texture.");
   }

}

void BlockGraphicsComponent::InitSprite(GraphicsEngine &graphicsEngine)
{
    if (FAILED(D3DXCreateSprite(graphicsEngine.getDirect3DDevice(), &sprite)))
    {
        throw std::runtime_error("Could not initialize sprite.");
    }
}

BlockGraphicsComponent::BlockGraphicsComponent(void)
    : GraphicsComponent("BlockGraphicsComponent")
{
}


void BlockGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    if (BlockGraphicsComponent::texture == NULL) {
        BlockGraphicsComponent::InitTexture(graphicsEngine);
    }

    if (BlockGraphicsComponent::sprite == NULL) {
        BlockGraphicsComponent::InitSprite(graphicsEngine);
    }
}

void BlockGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    Block *block = dynamic_cast<Block*>(&gameObject);
    Block::Position position = block->getPosition();

    BlockGraphicsComponent::sprite->Begin(D3DXSPRITE_ALPHABLEND);
    BlockGraphicsComponent::sprite->Draw(BlockGraphicsComponent::texture,
                                         NULL,
                                         NULL,
                                         &transformBlockPosition(position),
                                         transformBlockColor(block->getColor()));
    BlockGraphicsComponent::sprite->End();
}

D3DXVECTOR3 BlockGraphicsComponent::transformBlockPosition( Block::Position &position )
{
    D3DXVECTOR3 screenPosition;
    screenPosition.x = 64.0 * position.x;
    screenPosition.y = 64.0 * position.y;
    screenPosition.z = 0.0;
    return screenPosition;
}

D3DCOLOR BlockGraphicsComponent::transformBlockColor( BlockColors::Color color )
{
    switch(color)
    {
    case BlockColors::BLUE:
        return D3DCOLOR_XRGB(0, 128, 255);
    case BlockColors::RED:
        return D3DCOLOR_XRGB(240, 0, 0);
    case BlockColors::GREEN:
        return D3DCOLOR_XRGB(0, 240, 0);
    case BlockColors::WHITE:
        return D3DCOLOR_XRGB(255, 255, 255);
	case BlockColors::BACKGROUND_GREY:
		return D3DCOLOR_XRGB(32,32,32);
    default:
        return NULL;
    }
}