#include "FlightSimulatorGameApp.h"

FlightSimulatorGameApp::FlightSimulatorGameApp(void)
    : GameApp("Game", 1024, 768)
{
}

FlightSimulatorGameApp::~FlightSimulatorGameApp( void )
{
}

void FlightSimulatorGameApp::init( GameEngine &gameEngine )
{

    gameWorld.init(gameEngine);

}

void FlightSimulatorGameApp::update( float time )
{
    gameWorld.update(time);
}

void FlightSimulatorGameApp::draw( GraphicsEngine &graphicsEngine )
{
    gameWorld.draw(graphicsEngine);
}
