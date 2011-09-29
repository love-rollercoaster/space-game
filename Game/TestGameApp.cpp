#include "TestGameApp.h"
#include "Block.h"

TestGameApp::TestGameApp(void)
    : GameApp("Space Game")
{
}

TestGameApp::~TestGameApp( void )
{
}

void TestGameApp::init( GameEngine &gameEngine )
{
    // Who kills game objects?
    Block* block1 = new Block(BlockColors::Color::RED);
    Block* block2 = new Block(BlockColors::Color::BLUE);
    Block* block3 = new Block(BlockColors::Color::GREEN);

    testGraphicsComponent.init(gameEngine.getGraphicsEngine());

    // block1->init(&testInputComponent, NULL, &testGraphicsComponent);
    block1->init(NULL, NULL, &testGraphicsComponent);
    block2->init(NULL, NULL, &testGraphicsComponent);
    block3->init(NULL, NULL, &testGraphicsComponent);

    BlockGroup *blockGroup = new BlockGroup(*block1, *block2, *block3);
    testInputComponent.init(blockGroup);

    testGameWorld.init(gameEngine);
    testGameWorld.addGameObject(block1);
    testGameWorld.addGameObject(block2);
    testGameWorld.addGameObject(block3);
}

void TestGameApp::update( time_t time )
{
    testGameWorld.update(time);
}

void TestGameApp::draw(GraphicsEngine &graphicsEngine)
{
    testGameWorld.draw(graphicsEngine);
}
