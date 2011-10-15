#pragma once

#include "GraphicsEngine.h"
#include "Block.h"
#include "BlockGraphicsComponent.h"

class BlockFactory
{
public:
	BlockFactory(void);
	~BlockFactory(void);

	void init(GraphicsEngine &graphicsEngine);

	Block* makeBlock(BlockColors::Color color);
	Block* makeRandomColoredBlock();
private:
	BlockGraphicsComponent blockGraphicsComponent;
};

