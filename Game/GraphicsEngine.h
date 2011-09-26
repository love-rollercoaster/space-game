#pragma once

#include <atlbase.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <list>

#pragma comment (lib, "d3d9.lib")

#define CUSTOM_FLEXIBLE_VECTOR_FORMAT (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

using std::list;

struct CustomVertex
{
    FLOAT x, y, z, rhw; // D3DFVF_XYZRHW
    DWORD color;        // D3DFVF_DIFFUSE
};

class GraphicsEngine
{
public:
    GraphicsEngine(void);
    ~GraphicsEngine(void);

    CComPtr<IDirect3DDevice9> getDirect3DDevice() const;

    void initializeD3D(HWND window, int windowWidth, int windowHeight, bool isFullscreen);
    void resetD3DDevice();

    void beginDraw();
    void endDraw();

    void createVertexBuffer( LPDIRECT3DVERTEXBUFFER9 &vertexBuffer, CustomVertex vertices[], int numberOfVertices );

private:
    CComPtr<IDirect3D9> direct3DInterface;
    CComPtr<IDirect3DDevice9> direct3DDevice;
    D3DPRESENT_PARAMETERS d3dPresentationParameters;

    void initDirect3DInterface();
    void initPresentationParameters(HWND window, int windowWidth, int windowHeight, bool isFullscreen);
    void initDirect3DDevice(HWND window);
    void initRenderStates();

    void cleanDirect3D();
};


