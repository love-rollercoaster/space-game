#include "GameApp.h"

GameApp::GameApp( string title, int windowWidth, int windowHeight)
    : title(title)
    , windowWidth(windowWidth)
    , windowHeight(windowHeight)
    , gameEngine(*this, graphicsEngine)
{
}

GameApp::~GameApp()
{
    FontSystem::Cleanup();
}

void GameApp::init(HINSTANCE hInstance, int nCmdShow)
{
    initWindow(hInstance, nCmdShow);
    initInputSystem();

    graphicsEngine.init(window, false);
    FontSystem::Init(graphicsEngine); // This should be merged with graphic system

    this->KeyboardInputHandler::init();
    this->init(gameEngine);
}

void GameApp::start()
{
    gameEngine.startGameLoop();
}

string GameApp::getTitle()
{
    return this->title;
}

void GameApp::initWindow(HINSTANCE hInstance, int nCmdShow)
{
    window.init(hInstance, this->getTitle(), this->windowWidth, this->windowHeight);
    Window::RegisterMessageHandler(WM_DESTROY, WindowDestroyHandler);
    Window::ShowWindow(nCmdShow); // FIXME should show the window on start()
}

void GameApp::initInputSystem()
{
    InputSystem::StaticInit();
    inputSystem.init();
}

long GameApp::WindowDestroyHandler(Window &window, HWND hwnd, long wparam, long lparam) 
{
    ::PostQuitMessage(0);
    return 0;
}

void GameApp::quitGame()
{
    ::PostQuitMessage(0);
}

void GameApp::handleEscapeKey( unsigned char key )
{
    this->quitGame();
}

void GameApp::registerKeyboardInputCallbacks()
{
    registerCallback(VK_ESCAPE,  MAKE_KEYBOARD_INPUT_HANDLER(GameApp::handleEscapeKey));
}
