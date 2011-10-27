#pragma once

#include <windows.h>
#include <list>
#include <memory>

class Camera;
class GraphicsEngine;
class SceneryElement;

using std::tr1::shared_ptr;
using std::list;

class Scenery
{
public:
    virtual ~Scenery(void) {};

    virtual void add(shared_ptr<SceneryElement> sceneryElement);
    virtual void draw(Camera &camera, GraphicsEngine &graphicsEngine);

protected:
    list<shared_ptr<SceneryElement> > sceneryElements;

    virtual void preDraw(Camera &camera, GraphicsEngine &graphicsEngine);
    virtual void postDraw(Camera &camera, GraphicsEngine &graphicsEngine);

private:
    DWORD previousAntialiazingValue;
    DWORD previousLightingValue;
}

