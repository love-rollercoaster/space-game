#include "Block.h"

void Block::setPosition( Position position )
{
    setPosition(position.x, position.y);
}

void Block::setPosition( int x, int y )
{
    this->position.x = x;
    this->position.y = y;
}

Block::Position Block::getPosition()
{
    return this->position;
}

BlockColors::Color Block::getColor()
{
    return this->color;
}