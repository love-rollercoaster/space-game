#pragma once

#include "Block.h"

/*  =Orientations
 *
 *            [A]                       [C]
 *  VERTICAL: [B]     REVERSE_VERTICAL: [B]
 *            [C]                       [A]
 *
 *  HORIZONTAL: [A][B][C]
 *  REVERSE_HORIZONTAL: [C][B][A]
 *
 */

class BlockGroup
    : public GameObject
{
public:
    BlockGroup(Block& blockTop, 
               Block& blockMiddle, 
               Block& blockBottom);

    ~BlockGroup(void);

    enum Orientation 
    {
          VERTICAL
        , HORIZONTAL
        , REVERSE_VERTICAL
        , REVERSE_HORIZONTAL
    };

    Orientation getOrientation();
    void cycleOrientation();
    Orientation getNextOrientation();

    Block::Position getPosition(); 
    void setPosition(Block::Position position);
    void setPosition(unsigned int x, unsigned int y);

private:
    Orientation orientation;

    Block &blockTop;
    Block &blockMiddle;
    Block &blockBottom;

    void refreshPosition();
};
