#include "FontSystem.h"

LPD3DXFONT FontSystem::font = NULL;

FontSystem::FontSystem(void)
{
}

FontSystem::~FontSystem(void)
{
}

void FontSystem::Init(GraphicsEngine &graphicsEngine)
{
	D3DXCreateFont(graphicsEngine.getDirect3DDevice()
		          ,20
				  ,0
				  ,FW_NORMAL
				  ,0
				  ,FALSE
				  ,DEFAULT_CHARSET
				  ,OUT_DEFAULT_PRECIS
				  ,DEFAULT_QUALITY
				  ,DEFAULT_PITCH | FF_DONTCARE
				  ,TEXT("Impact")
				  ,&FontSystem::font);
}

void FontSystem::DrawText(string text, int x, int y, D3DCOLOR color)
{
	RECT rect = {x-2,y+2,250,100};
	FontSystem::font->DrawText(NULL, text.c_str(), -1, &rect, 0, D3DCOLOR_XRGB(100,100,100) );
	rect.left = x;
	rect.top = y;
	FontSystem::font->DrawText(NULL, text.c_str(), -1, &rect, 0, color );
}

void FontSystem::Cleanup()
{
    // FontSystem::font->Release();
}