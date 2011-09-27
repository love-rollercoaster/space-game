#pragma once

#include <vector>
#include <string>
#include "GraphicsComponent.h"
#include "GraphicsEngine.h"
#include "GameObject.h"

using std::string;
using std::vector;

class TestGraphicsComponent :
    public GraphicsComponent
{
public:
    TestGraphicsComponent(void);

    void init(GraphicsEngine &graphicsEngine);
    void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

private:
    static const int NUMBER_OF_VERTICES = 3;
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    CustomVertex vertices[TestGraphicsComponent::NUMBER_OF_VERTICES];
};