#pragma once

#include <d3d9.h>
#include "GameObject.h"

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

class TestGameObject :
    public GameObject
{
public:
    void setPosition(D3DVECTOR position);

private:
    D3DVECTOR position;
};
