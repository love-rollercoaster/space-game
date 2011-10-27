#include "Scenery.h"

#include "GraphicsEngine.h"
#include "SceneryElement.h"

void Scenery::add( shared_ptr<SceneryElement> sceneryElement )
{
    sceneryElements.push_back(sceneryElement);
}

void Scenery::draw(Camera &camera, GraphicsEngine &graphicsEngine)
{
    preDraw(camera, graphicsEngine);

    for each (shared_ptr<SceneryElement> sceneryElement in sceneryElements) {
        sceneryElement->draw(camera, graphicsEngine);
    }

    postDraw(camera, graphicsEngine);
}

void Scenery::preDraw( Camera &camera, GraphicsEngine &graphicsEngine )
{

}

void Scenery::postDraw( Camera &camera, GraphicsEngine &graphicsEngine )
{
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, previousAntialiazingValue);
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_LIGHTING, previousLightingValue);
}
