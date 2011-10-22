#include "GraphicsEngine.h"

#include "QuatCamera.h"

GraphicsEngine::GraphicsEngine(void)
    : backgroundColor(D3DCOLOR_XRGB(0,0,0))
    , camera(NULL)
{
}

GraphicsEngine::~GraphicsEngine(void)
{
}

CComPtr<IDirect3DDevice9> GraphicsEngine::getDirect3DDevice() const
{
    return direct3DDevice;
}

void GraphicsEngine::initializeD3D(Window window, bool isFullscreen)
{
    HWND hwnd = window.GetHandle();
    initDirect3DInterface();
    initPresentationParameters(hwnd, window.getWidth(), window.getHeight(), isFullscreen);
    initDirect3DDevice(hwnd);
    initRenderStates();
    // initSamplerStates();
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
    // d3dPresentationParameters.MultiSampleType   = D3DMULTISAMPLE_4_SAMPLES;

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
    direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    direct3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    direct3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    // direct3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE , TRUE);
}

void GraphicsEngine::initSamplerStates()
{
    direct3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
    direct3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
    direct3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
}

LPDIRECT3DVERTEXBUFFER9 GraphicsEngine::createVertexBuffer( CustomVertex vertices[], int numberOfVertices )
{
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    direct3DDevice->CreateVertexBuffer(numberOfVertices * sizeof(CustomVertex),
        0,
        CUSTOM_FLEXIBLE_VECTOR_FORMAT,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL);

    vertexBuffers.push_front(vertexBuffer);

    VOID* pVoid;
    vertexBuffer->Lock(0, 0, static_cast<void**>(&pVoid), 0);
    memcpy(pVoid, vertices, numberOfVertices * sizeof(CustomVertex));
    vertexBuffer->Unlock();

    return vertexBuffer;
}

void GraphicsEngine::beginDraw()
{
    setupViewMatrix();
    setupProjectionMatrix();

    direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET,  this->backgroundColor, 1.0f, 0);
    direct3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, this->backgroundColor, 1.0f, 0);
    direct3DDevice->BeginScene();
}

void GraphicsEngine::drawVertexBuffer( LPDIRECT3DVERTEXBUFFER9 &vertexBuffer)
{
    direct3DDevice->SetFVF(CUSTOM_FLEXIBLE_VECTOR_FORMAT);
    direct3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
    direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
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
        // ERR("invalid call when resetting the d3d device. Make sure all stateblocks are freed first");
        break;
    case D3DXERR_INVALIDDATA:
        // ERR("Invalid data");
        break;
    default:
        // ERR("Unhandled error when resetting d3d device");
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

void GraphicsEngine::cleanVertexBuffers()
{
    for each (LPDIRECT3DVERTEXBUFFER9 vertexBuffer in vertexBuffers) {
        vertexBuffer->Release();
    }
}

void GraphicsEngine::cleanDirect3D()
{
    cleanVertexBuffers();
}