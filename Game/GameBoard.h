#pragma once

#include <vector>
#include <time.h>

#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "BlockGroup.h"
#include "Block.h"
#include "BlockFactory.h"
#include "BlockGraphicsComponent.h"

using std::vector;

class GameBoard
	: public GameObject
{
public:
    GameBoard(unsigned int width, unsigned int height);
    ~GameBoard(void);

	void init(GameEngine &gameEngine);
	void draw(GraphicsEngine &graphicsEngine);
    void update(time_t time);

	void moveBlockGroupBy(int x, int y);

	void changeBlockOrientation();

	int getScore();

	void reset();

private:
    const unsigned int width;
    const unsigned int height;

	int score;

	BlockFactory blockFactory;

    vector< vector< Block* > > board;

	BlockGroup *blockGroup;
	BlockGroup* makeNewBlockGroup();

	Block* dummyBackgroundBlock;

	void checkIfBlockGroupIsStuckPhase();
    void moveDownBlockGroupPhase();
    void checkForColorTriplesPhase();
	void newBlockGroupPhase();
	void calculateScorePhase();

	void calculateScoreForRow(unsigned int row);

    bool blockGroupCanRotate(BlockGroup &blockGroup);

    bool positionsUnblocked(Block::Position p1,
                            Block::Position p2,
                            Block::Position p3);

    bool positionsUnblocked(int x1,
                            int y1,
                            int x2,
                            int y2,
                            int x3,
                            int y3);

    bool positionUnblocked(Block::Position position);
    bool positionUnblocked(int x, int y);

    bool positionWithinBounds(Block::Position position);
    bool positionWithinBounds(int x, int y);


	void persistBlockGroup(BlockGroup &blockGroup);
	void persistBlock(Block &block);
};

