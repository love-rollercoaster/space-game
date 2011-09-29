#pragma once

#include <vector>
#include <time.h>
#include "BlockGroup.h"
#include "Block.h"

using std::vector;

class GameBoard
{
public:
    GameBoard(unsigned int width, unsigned int height);
    ~GameBoard(void);

    void update(time_t time);

private:
    const unsigned int width;
    const unsigned int height;

    vector< vector< Block* > > board;

    void updateBlockGroupPhase();
    void checkForColorTriplesPhase();

    bool blockGroupCanRotate(BlockGroup &blockGroup);

    bool positionsUnblocked(Block::Position p1,
                            Block::Position p2,
                            Block::Position p3);

    bool positionsUnblocked(unsigned int x1,
                            unsigned int y1,
                            unsigned int x2,
                            unsigned int y2,
                            unsigned int x3,
                            unsigned int y3);

    bool positionUnblocked(Block::Position position);
    bool positionUnblocked(unsigned int x, unsigned int y);

    bool positionWithinBounds(Block::Position position);
    bool positionWithinBounds(unsigned int x, unsigned int y);
};

