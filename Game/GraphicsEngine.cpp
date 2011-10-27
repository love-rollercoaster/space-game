#include "GraphicsEngine.h"
#include "Window.h"
#include "SceneryElement.h"
#include "Skybox.h"
#include "Camera.h"

#include "Log.h"


GraphicsEngine::GraphicsEngine(void)
    : backgroundColor(D3DCOLOR_XRGB(0,0,0))
    , camera(nullptr)
    , antialiazingEnabled(false)
{
}

GraphicsEngine::~GraphicsEngine(void)
{
}

CComPtr<IDirect3DDevice9> GraphicsEngine::getDirect3DDevice() const
{
    return direct3DDevice;
}

void GraphicsEngine::enableFog(float fogStart, float fogEnd)
{
    // Reference
    // http://www.two-kings.de/tutorials/dxgraphics/dxgraphics15.html

    direct3DDevice->SetRenderState(D3DRS_FOGENABLE,true);
    direct3DDevice->SetRenderState(D3DRS_RANGEFOGENABLE,true);
    direct3DDevice->SetRenderState(D3DRS_FOGCOLOR, backgroundColor);
    direct3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
    direct3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fogStart));
    direct3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fogEnd));
}

void GraphicsEngine::init(Window window, bool isFullscreen)
{
    HWND hwnd = window.GetHandle();

    initDirect3DInterface();
    initPresentationParameters(hwnd, window.getWidth(), window.getHeight(), isFullscreen);
    initDirect3DDevice(hwnd);
    initRenderStates();
    initScenery();
    initSamplerStates();
}

void GraphicsEngine::initDirect3DInterface()
{
    direct3DInterface.Attach(::Direct3DCreate9(D3D_SDK_VERSION));
    if (direct3DInterface == NULL) {
        // TODO: Change this throw to send an instance of some exception class,
        //       D3DInterfaceCreationException for example
        throw "Direct3d9 interface could not be created";
    }
}

void GraphicsEngine::initPresentationParameters(HWND window, int windowWidth, int windowHeight, bool isFullscreen)
{
    ZeroMemory(&d3dPresentationParameters, sizeof(d3dPresentationParameters));
    d3dPresentationParameters.Windowed          = !isFullscreen;
    d3dPresentationParameters.SwapEffect        = D3DSWAPEFFECT_DISCARD;
    d3dPresentationParameters.hDeviceWindow     = window;
    d3dPresentationParameters.BackBufferFormat  = D3DFMT_X8R8G8B8;
    d3dPresentationParameters.BackBufferWidth   = windowWidth;
    d3dPresentationParameters.BackBufferHeight  = windowHeight;
    d3dPresentationParameters.EnableAutoDepthStencil = TRUE;
    d3dPresentationParameters.AutoDepthStencilFormat = D3DFMT_D24S8;

    if (antialiazingEnabled) {
        d3dPresentationParameters.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
    }
}

void GraphicsEngine::initDirect3DDevice(HWND window)
{
    HRESULT result = direct3DInterface->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dPresentationParameters,
        &direct3DDevice
    );

    if (result != D3D_OK){
        throw "Error creating the Direct3d9 device";
    }
}

void GraphicsEngine::initRenderStates()
{
    direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    direct3DDevice->SetRenderState(D3DRS_ZENABLE, true);
    direct3DDevice->SetRenderState(D3DRS_LIGHTING, true);

    if (antialiazingEnabled) {
        direct3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
    }
}


void GraphicsEngine::initSamplerStates()
{
    direct3DDevice->SetSamplerState(D3DSAMP_MAXANISOTROPY, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
    direct3DDevice->SetSamplerState(D3DSAMP_MAXANISOTROPY, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
    direct3DDevice->SetSamplerState(D3DSAMP_MAXANISOTROPY, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
}


void GraphicsEngine::initScenery()
{
    shared_ptr<SceneryElement> skybox(new Skybox);
    skybox->init(*this);
    addSceneryElement(skybox);
}


void GraphicsEngine::beginDraw()
{
    setupViewMatrix();
    setupProjectionMatrix();

    direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, backgroundColor, 1.0f, 0);
    direct3DDevice->BeginScene();

    drawScenery();
}


void GraphicsEngine::endDraw()
{
    direct3DDevice->EndScene();
    direct3DDevice->Present(NULL, NULL, NULL, NULL);
}


// TODO: Fix this method, it was not ported correctly.
void GraphicsEngine::resetD3DDevice()
{
    if (direct3DDevice == NULL) {
        return; // FIXME: throw instead?
    }
    // d3dspt->OnLostDevice();
    HRESULT err = direct3DDevice->Reset(&d3dPresentationParameters);

    switch(err) {
    case D3D_OK:
        break;
    case D3DERR_INVALIDCALL:
        ERR("invalid call when resetting the d3d device. Make sure all stateblocks are freed first");
        break;
    case D3DXERR_INVALIDDATA:
        ERR("Invalid data");
        break;
    default:
        ERR("Unhandled error when resetting d3d device");
        break;
    }

    // d3dspt->OnResetDevice();
    initRenderStates();
}


void GraphicsEngine::setCamera( Camera &camera )
{
    this->camera = &camera;
}


void GraphicsEngine::setBackgroundColor( DWORD backgroundColor )
{
    this->backgroundColor = backgroundColor;
    direct3DDevice->SetRenderState(D3DRS_FOGCOLOR, backgroundColor);
}


void GraphicsEngine::setupViewMatrix()
{
    if (camera != NULL) {
        direct3DDevice->SetTransform(D3DTS_VIEW, &camera->getViewMatrix());
    }
}


void GraphicsEngine::setupProjectionMatrix()
{
    if (camera != NULL) {
        direct3DDevice->SetTransform(D3DTS_PROJECTION, &camera->getProjectionMatrix()); 
    }
}


HRESULT GraphicsEngine::loadMesh(string fileName, LPD3DXMESH *meshP, D3DMATERIAL9** mats, LPDIRECT3DTEXTURE9 **texture, DWORD *numMats) {
    LPD3DXBUFFER matsTemp;
    HRESULT result;

    result = D3DXLoadMeshFromX(fileName.c_str(),
                             D3DXMESH_MANAGED,
                             getDirect3DDevice(),
                             NULL,
                             &matsTemp,
                             NULL,
                             numMats,
                             meshP);

    
    if (result != D3D_OK)
        return result;

    D3DXMATERIAL* tempMaterials = (D3DXMATERIAL*)matsTemp->GetBufferPointer();
    D3DMATERIAL9* materialsArray = new D3DMATERIAL9[*numMats];
    LPDIRECT3DTEXTURE9 *textureArray = new LPDIRECT3DTEXTURE9[*numMats];

    for(DWORD i = 0; i < *numMats; i++)
    {
        materialsArray[i] = tempMaterials[i].MatD3D;
        materialsArray[i].Ambient = materialsArray[i].Diffuse;
        if (FAILED(D3DXCreateTextureFromFileA(getDirect3DDevice(),
                                            tempMaterials[i].pTextureFilename,
                                            &textureArray[i]))) {
            textureArray[i] = NULL;
        }
    }
    *mats = materialsArray;
    *texture = textureArray;
    return D3D_OK;
}

void GraphicsEngine::addSceneryElement( shared_ptr<SceneryElement> sceneryElement )
{
    scenery.push_back(sceneryElement);
}

void GraphicsEngine::drawScenery()
{
    if (camera == nullptr) {
        return;
    }
    
    // DWORD previousAntialiazingValue;
    DWORD previousLightingValue;
    DWORD previousFogValue;

    //direct3DDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &previousAntialiazingValue);
    direct3DDevice->GetRenderState(D3DRS_LIGHTING, &previousLightingValue);
    direct3DDevice->GetRenderState(D3DRS_FOGENABLE, &previousFogValue);

    //direct3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);
    direct3DDevice->SetRenderState(D3DRS_LIGHTING, false);
    direct3DDevice->SetRenderState(D3DRS_FOGENABLE, false);
    direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

    for each (shared_ptr<SceneryElement> sceneryElement in scenery) {
        sceneryElement->draw(*camera, *this);
    }
    
    direct3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
    direct3DDevice->SetRenderState(D3DRS_FOGENABLE, previousFogValue);
    direct3DDevice->SetRenderState(D3DRS_LIGHTING, previousLightingValue);
    //direct3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, previousAntialiazingValue);
}
