#pragma once
#include "GameApp.h"

class SpaceGameApp : public GameApp
{
public:
    SpaceGameApp(void);

    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);
};

