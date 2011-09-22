#pragma once

#include <atlbase.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")

class GraphicsEngine
{
public:
    GraphicsEngine(void);
    ~GraphicsEngine(void);

    CComPtr<IDirect3DDevice9> getDirect3DDevice() const;

    void initializeD3D(HWND window, int windowWidth, int windowHeight, bool isFullscreen);
    void resetD3DDevice();

private:
    CComPtr<IDirect3D9> direct3DInterface;
    CComPtr<IDirect3DDevice9> direct3DDevice;
    D3DPRESENT_PARAMETERS d3dPresentationParameters;

    // Initialization helpers
    void initDirect3DInterface();
    void initPresentationParameters(HWND window, int windowWidth, int windowHeight, bool isFullscreen);
    void initDirect3DDevice(HWND window);
    void initRenderStates();
};