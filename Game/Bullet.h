#pragma once
#include "gameobject.h"
#include "MoveableGameObject.h"

class Bullet :
    public MoveableGameObject
{
public:
    Bullet(void);
    ~Bullet(void);
};

