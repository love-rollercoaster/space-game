#include "GraphicsEngine.h"


GraphicsEngine::GraphicsEngine(void)
{
}

GraphicsEngine::~GraphicsEngine(void)
{
}

CComPtr<IDirect3DDevice9> GraphicsEngine::getDirect3DDevice() const
{
    return direct3DDevice;
}

void GraphicsEngine::initializeD3D(HWND window, int windowWidth, int windowHeight, bool isFullscreen)
{
    initDirect3DInterface();
    initPresentationParameters(window, windowWidth, windowHeight, isFullscreen);
    initDirect3DDevice(window);

    //     this fun stuff is for setting up the view
    //     D3DXMATRIX matOrtho;
    //     D3DXMATRIX matIdentity;
    //     D3DXMatrixOrthoLH (&matOrtho, (float)(clientRect.right - clientRect.left), (float)(clientRect.bottom - clientRect.top), 1.0f, 10.0f);
    //     D3DXMatrixIdentity (&matIdentity);
    //     d3ddev->SetTransform (D3DTS_PROJECTION, &matOrtho);
    //     d3ddev->SetTransform (D3DTS_WORLD, &matIdentity);
    //     d3ddev->SetTransform (D3DTS_VIEW, &matIdentity);

    initRenderStates();
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
    d3dPresentationParameters.Windowed            = !isFullscreen;             // program is fullscreen or windowed
    d3dPresentationParameters.SwapEffect        = D3DSWAPEFFECT_DISCARD;     // discard old frames
    d3dPresentationParameters.hDeviceWindow        = window;                     // set the window to be used by Direct3D
    d3dPresentationParameters.BackBufferFormat    = D3DFMT_X8R8G8B8;             // set the back buffer format to 32-bit
    d3dPresentationParameters.BackBufferWidth    = windowWidth;               // set the width of the buffer
    d3dPresentationParameters.BackBufferHeight    = windowHeight;              // set the height of the buffer
    d3dPresentationParameters.MultiSampleType    = D3DMULTISAMPLE_4_SAMPLES;  // anti-aliasing
}

void GraphicsEngine::initDirect3DDevice(HWND window)
{
    HRESULT result = direct3DInterface->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window,
        D3DCREATE_MIXED_VERTEXPROCESSING,
        &d3dPresentationParameters,
        &direct3DDevice
    );

    if (result != D3D_OK){
        throw "Error creating the Direct3d9 device";
    }
}

void GraphicsEngine::initRenderStates()
{
    direct3DDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE , true);
    direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
}


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





