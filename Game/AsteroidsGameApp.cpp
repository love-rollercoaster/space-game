#include "AsteroidsGameApp.h"

AsteroidsGameApp::AsteroidsGameApp(void)
    : GameApp("Game", 1024, 768)
{
}

AsteroidsGameApp::~AsteroidsGameApp( void )
{
}

void AsteroidsGameApp::init( GameEngine &gameEngine )
{

    gameWorld.init(gameEngine);

}

void AsteroidsGameApp::update( float time )
{
    gameWorld.update(time);
}

void AsteroidsGameApp::draw( GraphicsEngine &graphicsEngine )
{
    gameWorld.draw(graphicsEngine);
}

void AsteroidsGameApp::registerKeyboardInputCallbacks()
{
    GameApp::registerKeyboardInputCallbacks(); // fixme
    registerCallback(VK_SPACE,  MAKE_KEYBOARD_INPUT_HANDLER(AsteroidsGameApp::handleSpacePress));
    registerCallback(VK_OEM_COMMA,  MAKE_KEYBOARD_INPUT_HANDLER(AsteroidsGameApp::handleCommaPress));
    registerCallback(VK_OEM_PERIOD,  MAKE_KEYBOARD_INPUT_HANDLER(AsteroidsGameApp::handlePeriodPress));
    registerCallback(VK_OEM_2,  MAKE_KEYBOARD_INPUT_HANDLER(AsteroidsGameApp::handleSlashPress)); //slash key
    registerCallback('1',  MAKE_KEYBOARD_INPUT_HANDLER(AsteroidsGameApp::handle1KeyPress));
    registerCallback('3',  MAKE_KEYBOARD_INPUT_HANDLER(AsteroidsGameApp::handle3KeyPress));
}

void AsteroidsGameApp::handleSpacePress(unsigned char key)
{
    gameWorld.shootLaser();
}

void AsteroidsGameApp::handleCommaPress(unsigned char key)
{
    gameWorld.followNextAsteroid();
}

void AsteroidsGameApp::handlePeriodPress(unsigned char key)
{
    gameWorld.followPreviousAsteroid();
}

void AsteroidsGameApp::handleSlashPress(unsigned char key)
{
    gameWorld.followShip();
}

void AsteroidsGameApp::handle1KeyPress(unsigned char key)
{
    gameWorld.setFirstPersonCamera();
}

void AsteroidsGameApp::handle3KeyPress(unsigned char key)
{
    gameWorld.setThirdPersonCamera();
}