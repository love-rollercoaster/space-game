#pragma once

class GraphicsEngine;
class Camera;

class SceneryElement
{
public:
    virtual void init(GraphicsEngine &graphicsEngine) = 0;
    virtual void draw(Camera &camera, GraphicsEngine &graphicsEngine) = 0;
};
