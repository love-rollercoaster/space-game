#include "FlightSimulatorGameApp.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

FlightSimulatorGameApp::FlightSimulatorGameApp(void)
    : GameApp("Game", WINDOW_WIDTH, WINDOW_HEIGHT)
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
