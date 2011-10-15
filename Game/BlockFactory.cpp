#include "BlockFactory.h"
#include <stdlib.h>

BlockFactory::BlockFactory(void)
{
}

BlockFactory::~BlockFactory(void)
{
}

void BlockFactory::init(GraphicsEngine &graphicsEngine)
{
	blockGraphicsComponent.init(graphicsEngine);
}

Block* BlockFactory::makeBlock(BlockColors::Color color)
{
	Block* block = new Block(color);
	block->init(NULL, NULL, &blockGraphicsComponent);
	return block;
}

Block* BlockFactory::makeRandomColoredBlock()
{
	BlockColors::Color color;
	int randomValue = rand() % 4;
	switch(randomValue)
	{
	case 0:
		color = BlockColors::BLUE;
		break;
	case 1:
		color = BlockColors::RED;
		break;
	case 2:
		color = BlockColors::GREEN;
		break;
	case 3:
		color = BlockColors::WHITE;
		break;
	}

	return makeBlock(color);
}