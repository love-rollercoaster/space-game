#include "Asteroid.h"
#include "MoveableGameObject.h"

shared_ptr<GraphicsComponent> Asteroid::graphicsComponent(new AsteroidGraphicsComponent);

Asteroid::Asteroid()
    : representation(new MoveableGameObject)
{
}

Asteroid::~Asteroid(void)
{
}

void Asteroid::init( GameEngine &gameEngine )
{
    static bool graphicsComponentInitialized = false;

    if (!graphicsComponentInitialized) {
        graphicsComponent->init(gameEngine);
        graphicsComponentInitialized = true;
    }

    representation->init(NULL, NULL, graphicsComponent);
}

void Asteroid::draw( GraphicsEngine &graphicsEngine )
{
    representation->draw(graphicsEngine);
}

void Asteroid::update( float time )
{
    representation->update(time);
}

shared_ptr<MoveableGameObject> Asteroid::getGameObjectRepresentation()
{
    return this->representation;
}