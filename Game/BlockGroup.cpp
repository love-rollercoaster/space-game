#include "BlockGroup.h"

BlockGroup::BlockGroup(Block& blockTop, 
                       Block& blockMiddle, 
                       Block& blockBottom)
    : blockTop(blockTop)
    , blockMiddle(blockMiddle)
    , blockBottom(blockBottom)
    , orientation(Orientation::VERTICAL)
{
    setPosition(0, 1);
}

BlockGroup::~BlockGroup(void)
{
}

void BlockGroup::draw(GraphicsEngine &graphicsEngine)
{
	blockTop.draw(graphicsEngine);
	blockMiddle.draw(graphicsEngine);
	blockBottom.draw(graphicsEngine);
}

Block::Position BlockGroup::getPosition()
{
    return blockMiddle.getPosition();
}

void BlockGroup::setPosition( Block::Position position )
{
    setPosition(position.x, position.y);
}

void BlockGroup::setPosition( int x, int y )
{
    switch(orientation)
    {
    case VERTICAL:
           blockTop.setPosition(x, y - 1);
        blockBottom.setPosition(x, y + 1);
        break;
    case HORIZONTAL:
           blockTop.setPosition(x - 1, y);
        blockBottom.setPosition(x + 1, y);
        break;
    case REVERSE_VERTICAL:
           blockTop.setPosition(x, y + 1);
        blockBottom.setPosition(x, y - 1);
        break;
    case REVERSE_HORIZONTAL:
           blockTop.setPosition(x + 1, y);
        blockBottom.setPosition(x - 1, y);
    }

    blockMiddle.setPosition(x, y);
}

BlockGroup::Orientation BlockGroup::getOrientation()
{
	return orientation;
}

void BlockGroup::cycleOrientation()
{
    orientation = getNextOrientation();
    refreshPosition();
}

BlockGroup::Orientation BlockGroup::getNextOrientation()
{
    switch(orientation)
    {
    case VERTICAL:
        return HORIZONTAL;
    case HORIZONTAL:
        return REVERSE_VERTICAL;
    case REVERSE_VERTICAL:
        return REVERSE_HORIZONTAL;
    case REVERSE_HORIZONTAL:
        return VERTICAL;
    default:
        return orientation;
    }
}

void BlockGroup::refreshPosition() 
{
    Block::Position position = blockMiddle.getPosition();
    setPosition(position.x, position.y);
}

Block* BlockGroup::getTopBlock()
{
	return &blockTop;
}

Block* BlockGroup::getMiddleBlock()
{
	return &blockMiddle;
}

Block* BlockGroup::getBottomBlock()
{
	return &blockBottom;
}