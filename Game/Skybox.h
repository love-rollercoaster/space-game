#pragma once
#include "GraphicsComponent.h"
#include "Camera.h"

// Reference
// http://www.gameengineer.net/samples-graphics.html

class Skybox :
    public GraphicsComponent
{
public:
    Skybox(void);
    ~Skybox(void);

    struct TexturedVertex
    {
        D3DXVECTOR3 position;
        D3DXVECTOR2 texture;
    };

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

    Camera *camera;

protected:
    virtual void initVertexBuffer(GraphicsEngine &graphicsEngine);
    virtual void initTexture(GraphicsEngine &graphicsEngine);

    virtual void performWorldTransformations(GameObject &gameObject, GraphicsEngine &graphicsEngine);

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DTEXTURE9 texture[6];
    LPDIRECT3DINDEXBUFFER9 indexBuffer;

    


};

