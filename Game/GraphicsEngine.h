#pragma once
#pragma comment (lib, "d3d9.lib")

#include <atlbase.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <memory>
#include <string>

#define CUSTOM_FVF  (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define TEXTURE_FVF (D3DFVF_XYZ | D3DFVF_TEX1)

using std::tr1::shared_ptr;
using std::list;
using std::string;

struct CustomVertex
{
    D3DXVECTOR3 position;
    DWORD color;
};

struct TexturedVertex
{
    D3DXVECTOR3 position;
    D3DXVECTOR2 texture;
};

class Window;
class Camera;
class Scenery;
class SceneryElement;


class GraphicsEngine
{
public:
    GraphicsEngine(void);
    ~GraphicsEngine(void);

    CComPtr<IDirect3DDevice9> getDirect3DDevice() const;

    void init(Window window, bool isFullscreen);
    void resetD3DDevice();

    void beginDraw();
    void endDraw();  

    void setCamera(Camera &camera);
    void setBackgroundColor(DWORD backgroundColor);
    void enableFog(float fogStart, float fogEnd);

    D3DXMATRIX getProjectionMatrix();

    void addSceneryElement(shared_ptr<SceneryElement> sceneryElement);

    HRESULT loadMesh(string fileName, LPD3DXMESH *meshP, D3DMATERIAL9** mats, LPDIRECT3DTEXTURE9 **texture, DWORD *numMats);

private:
    CComPtr<IDirect3D9> direct3DInterface;
    CComPtr<IDirect3DDevice9> direct3DDevice;
    D3DPRESENT_PARAMETERS d3dPresentationParameters;
    Camera *camera;
    DWORD backgroundColor;
    list<shared_ptr<SceneryElement> > scenery;

    void initDirect3DInterface();
    void initPresentationParameters(HWND window, int windowWidth, int windowHeight, bool isFullscreen);
    void initDirect3DDevice(HWND window);
    void initRenderStates();
    void initSamplerStates();
    void initScenery();

    void drawScenery();

    void setupViewMatrix();
    void setupProjectionMatrix();

    bool antialiazingEnabled;
};