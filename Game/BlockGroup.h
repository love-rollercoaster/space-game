#pragma once

#include "Block.h"
#include "GraphicsEngine.h"

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

	void draw(GraphicsEngine &graphicsEngine);

    void cycleOrientation();
	Orientation getOrientation();
    Orientation getNextOrientation();

    Block::Position getPosition(); 
    void setPosition(Block::Position position);
    void setPosition(int x, int y);

	Block* getTopBlock();
	Block* getMiddleBlock();
	Block* getBottomBlock();

private:
    Orientation orientation;

    Block &blockTop;
    Block &blockMiddle;
    Block &blockBottom;

    void refreshPosition();
};
