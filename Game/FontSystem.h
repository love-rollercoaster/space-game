#pragma once


#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "GameEngine.h"

using std::string;

class FontSystem
{
public:
	FontSystem(void);
	~FontSystem(void);

	static void Init(GraphicsEngine &graphicsEngine);
	static void DrawText(string text, int x, int y, D3DCOLOR color);
	static void Cleanup();

private:
	static LPD3DXFONT font;
};