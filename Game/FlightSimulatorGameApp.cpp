#include "FlightSimulatorGameApp.h"

FlightSimulatorGameApp::FlightSimulatorGameApp(void)
    : GameApp("Game", 800, 600)
{
}

FlightSimulatorGameApp::~FlightSimulatorGameApp( void )
{
}

void FlightSimulatorGameApp::init( GameEngine &gameEngine )
{

    gameWorld.init(gameEngine);

}

void FlightSimulatorGameApp::update( time_t time )
{
    gameWorld.update(time);
}

void FlightSimulatorGameApp::draw( GraphicsEngine &graphicsEngine )
{
    gameWorld.draw(graphicsEngine);
}
