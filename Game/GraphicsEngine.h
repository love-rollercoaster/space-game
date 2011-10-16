#pragma once

#include <atlbase.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <list>

#include "Window.h"

#pragma comment (lib, "d3d9.lib")

#define CUSTOM_FLEXIBLE_VECTOR_FORMAT (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

using std::list;

struct CustomVertex
{
    D3DXVECTOR3 position;
    FLOAT rhw;
    DWORD color;
};

class GraphicsEngine
{
public:
    GraphicsEngine(void);
    ~GraphicsEngine(void);

    CComPtr<IDirect3DDevice9> getDirect3DDevice() const;

    void initializeD3D(Window window, bool isFullscreen);
    void resetD3DDevice();

    void beginDraw();
    void endDraw();

    LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(CustomVertex vertices[], int numberOfVertices );
    void drawVertexBuffer(LPDIRECT3DVERTEXBUFFER9 &vertexBuffer);

private:
    CComPtr<IDirect3D9> direct3DInterface;
    CComPtr<IDirect3DDevice9> direct3DDevice;
    D3DPRESENT_PARAMETERS d3dPresentationParameters;
    list<LPDIRECT3DVERTEXBUFFER9> vertexBuffers;

    void initDirect3DInterface();
    void initPresentationParameters(HWND window, int windowWidth, int windowHeight, bool isFullscreen);
    void initDirect3DDevice(HWND window);
    void initRenderStates();
    void initSamplerStates();

    void cleanDirect3D();
    void cleanVertexBuffers();
};


