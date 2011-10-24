#pragma once
#include "graphicscomponent.h"
#include "Log.h"
#include "Bullet.h"

class BulletGraphicsComponent :
    public GraphicsComponent
{
public:
    BulletGraphicsComponent(void);
    ~BulletGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    LPD3DXMESH bulletMesh;
};

