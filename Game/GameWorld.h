#pragma once

#include <list>
#include <time.h>

class GameEngine;
class GameObject;
class GraphicsEngine;

using std::list;

class GameWorld
{
public:
    virtual void init(GameEngine &gameEngine) = 0;
    virtual void update(float time) = 0;
    virtual void draw(GraphicsEngine &graphicsEngine) = 0;

    void addGameObject(GameObject *gameObject) {
        gameObjects.push_back(gameObject);
    };

protected:
    list<GameObject*> gameObjects;
};
