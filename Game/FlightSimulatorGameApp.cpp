#include "FlightSimulatorGameApp.h"

FlightSimulatorGameApp::FlightSimulatorGameApp(void)
    : GameApp("Game")
{
}

FlightSimulatorGameApp::~FlightSimulatorGameApp( void )
{
}

void FlightSimulatorGameApp::init( GameEngine &gameEngine )
{
    graphicsComponent.init(gameEngine.getGraphicsEngine());
    gameObject.init(NULL, NULL, &graphicsComponent);
    gameWorld.init(gameEngine);
    gameWorld.addGameObject(&gameObject);
}

void FlightSimulatorGameApp::update( time_t time )
{
    gameWorld.update(time);
}

void FlightSimulatorGameApp::draw( GraphicsEngine &graphicsEngine )
{
    gameWorld.draw(graphicsEngine);
}
