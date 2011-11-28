#pragma once
#include "graphicscomponent.h"
#include "Log.h"
#include "Laser.h"

#define LASER_RADIUS 0.08f
#define LASER_LENGTH 1.0f

#define LASER_AMBIENT_COLOR D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f)
#define LASER_DIFFUSE_COLOR D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f)
#define LASER_EMISSIVE_COLOR D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f)
#define LASER_SPECULAR_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)
#define LASER_SPECULAR_POWER 0.0f

class LaserGraphicsComponent :
    public GraphicsComponent
{
public:
    LaserGraphicsComponent(void);
    ~LaserGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    LPD3DXMESH laserMesh;
    D3DMATERIAL9 material;
};

