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

void FlightSimulatorGameApp::registerKeyboardInputCallbacks()
{
    GameApp::registerKeyboardInputCallbacks();
    registerCallback(VK_SPACE,  MAKE_KEYBOARD_INPUT_HANDLER(FlightSimulatorGameApp::handleSpacePress));
}

void FlightSimulatorGameApp::handleSpacePress(unsigned char key)
{
    gameWorld.shootLaser();
}