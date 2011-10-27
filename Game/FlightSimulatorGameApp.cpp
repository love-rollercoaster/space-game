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
    registerCallback(VK_OEM_COMMA,  MAKE_KEYBOARD_INPUT_HANDLER(FlightSimulatorGameApp::handleCommaPress));
    registerCallback(VK_OEM_PERIOD,  MAKE_KEYBOARD_INPUT_HANDLER(FlightSimulatorGameApp::handlePeriodPress));
    registerCallback(VK_OEM_2,  MAKE_KEYBOARD_INPUT_HANDLER(FlightSimulatorGameApp::handleSlashPress)); //slash key
    registerCallback('1',  MAKE_KEYBOARD_INPUT_HANDLER(FlightSimulatorGameApp::handle1KeyPress));
    registerCallback('3',  MAKE_KEYBOARD_INPUT_HANDLER(FlightSimulatorGameApp::handle3KeyPress));
}

void FlightSimulatorGameApp::handleSpacePress(unsigned char key)
{
    gameWorld.shootLaser();
}

void FlightSimulatorGameApp::handleCommaPress(unsigned char key)
{
    gameWorld.followNextAsteroid();
}

void FlightSimulatorGameApp::handlePeriodPress(unsigned char key)
{
    gameWorld.followPreviousAsteroid();
}

void FlightSimulatorGameApp::handleSlashPress(unsigned char key)
{
    gameWorld.followShip();
}

void FlightSimulatorGameApp::handle1KeyPress(unsigned char key)
{
    gameWorld.setFirstPersonCamera();
}

void FlightSimulatorGameApp::handle3KeyPress(unsigned char key)
{
    gameWorld.setThirdPersonCamera();
}