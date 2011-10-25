#pragma once

#include <memory>
#include "AsteroidGraphicsComponent.h"

class MoveableGameObject;
class GraphicsComponent;
class GraphicsEngine;
class GameEngine;

using std::tr1::shared_ptr;

class Asteroid
{
public:
    Asteroid(void);
    ~Asteroid(void);

    void init(GameEngine &gameEngine);
    void draw(GraphicsEngine &graphicsEngine);
    void update(float time);

    shared_ptr<MoveableGameObject> getGameObjectRepresentation();

private:
    shared_ptr<MoveableGameObject> representation;
    static shared_ptr<GraphicsComponent> graphicsComponent;
};

