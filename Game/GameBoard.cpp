#include "GameBoard.h"


GameBoard::GameBoard(unsigned int width, unsigned int height)
    : width(width)
    , height(height)
    , board(width, vector<Block*>(height))
{
    for (unsigned int i = 0; i < width; i++) {
        board.push_back(vector<Block*>());
        for (unsigned int j = 0; j < height; j++) {
            board[i].push_back(NULL);
        }
    }
}

GameBoard::~GameBoard(void)
{
}

void update(time_t time)
{

}

bool GameBoard::blockGroupCanRotate(BlockGroup &blockGroup)
{
    BlockGroup::Orientation nextOrientation = blockGroup.getNextOrientation();
    Block::Position position = blockGroup.getPosition();

    switch(nextOrientation)
    {
    case(BlockGroup::HORIZONTAL):
    case(BlockGroup::REVERSE_HORIZONTAL):
        return positionsUnblocked(position.x + 1, position.y,
                                  position.x,     position.y,
                                  position.x - 1, position.y);
    case(BlockGroup::VERTICAL):
    case(BlockGroup::REVERSE_VERTICAL):
        return positionsUnblocked(position.x, position.y + 1,
                                  position.x, position.y,
                                  position.x, position.y - 1);
    default:
        // OH NOES!
        // WHAT DO
        break;
    }
}

bool GameBoard::positionWithinBounds( Block::Position position )
{
    return positionWithinBounds(position.x, position.y);
}

bool GameBoard::positionWithinBounds( unsigned int x, unsigned int y )
{
    bool xWithinBounds = x >= 0 && x < width;
    bool yWithinBounds = y >= 0 && x < height;

    return xWithinBounds && yWithinBounds;
}

bool GameBoard::positionsUnblocked( Block::Position p1, Block::Position p2, Block::Position p3 )
{
    return positionUnblocked(p1) && positionUnblocked(p2) && positionUnblocked(p3);
}

bool GameBoard::positionUnblocked( Block::Position position )
{
    return positionUnblocked(position.x, position.y);
}

bool GameBoard::positionsUnblocked( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3 )
{
    return positionUnblocked(x1,y1) && positionUnblocked(x2,y2) && positionUnblocked(x3,y3);
}

bool GameBoard::positionUnblocked( unsigned int x, unsigned int y )
{
    return positionWithinBounds(x,y) && board[x][y] == NULL;
}
