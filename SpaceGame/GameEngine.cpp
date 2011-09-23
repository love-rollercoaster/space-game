#include "GameEngine.h"

GameEngine::GameEngine(GameApp &gameApp, GraphicsEngine &graphicsEngine)
    : TIME_PER_FRAME(1000 / TARGET_FRAMERATE)
    , gameApp(gameApp)
    , graphicsEngine(graphicsEngine)
{
}

GameEngine::~GameEngine(void)
{
}

WPARAM GameEngine::startGameLoop()
{
    MSG    msg;
    time_t elapsedTime, lastUpdateTime, lastRenderTime;
    lastUpdateTime = lastRenderTime = GetTickCount();

    do {
        msg = getMessage();

        updateGameState(GetTickCount() - lastUpdateTime);
        lastUpdateTime = GetTickCount();

        graphicsEngine.beginDraw();
        // gameApp.draw(graphicsEngine);
        graphicsEngine.drawTestVertices();
        graphicsEngine.endDraw();

        elapsedTime = GetTickCount() - lastRenderTime;
        if (elapsedTime < TIME_PER_FRAME){
            Sleep(static_cast<DWORD>(TIME_PER_FRAME - elapsedTime));
        }

        lastRenderTime = GetTickCount();
    }
    while (msg.message != WM_QUIT);

    return msg.wParam;
}

void GameEngine::updateGameState(time_t time)
{

}

MSG GameEngine::getMessage()
{
    MSG msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg;
}
