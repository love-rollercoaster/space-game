#include "GameBoard.h"
#include <sstream>

using std::stringstream;

// warning: contains last minute coding atrocities

GameBoard::GameBoard(unsigned int width, unsigned int height)
    : width(width)
    , height(height)
    , board(width, vector<Block*>(height))
	, blockGroup(makeNewBlockGroup())
	, score(0)
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
	delete dummyBackgroundBlock;
}

void GameBoard::init(GameEngine &gameEngine)
{
	blockFactory.init(gameEngine.getGraphicsEngine());
	dummyBackgroundBlock = blockFactory.makeBlock(BlockColors::BACKGROUND_GREY);
}

void GameBoard::draw(GraphicsEngine &graphicsEngine)
{
	for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            if (board[i][j] != NULL) {
				board[i][j]->draw(graphicsEngine);
			} else {
				dummyBackgroundBlock->setPosition(i,j);
				dummyBackgroundBlock->draw(graphicsEngine);
			}
        }
    }

	blockGroup->draw(graphicsEngine);
}

void GameBoard::update(time_t time)
{
	Block::Position positionBefore = blockGroup->getPosition();
	moveDownBlockGroupPhase();
	Block::Position positionAfter = blockGroup->getPosition();

	if (positionBefore.y == positionAfter.y) {
		newBlockGroupPhase();
		calculateScorePhase();
	}
}

void GameBoard::moveDownBlockGroupPhase()
{
	moveBlockGroupBy(0, 1);
}

void GameBoard::newBlockGroupPhase()
{
	persistBlockGroup(*blockGroup);
	delete blockGroup;
	blockGroup = makeNewBlockGroup();

	if (board[blockGroup->getPosition().x][blockGroup->getPosition().y] != NULL)
	{
		calculateScorePhase();

		stringstream scoreText;
		scoreText << "Congratulations, you lost the game!\n Your score was: " << score;

		MessageBox(NULL, scoreText.str().c_str(), "Noob", MB_OK);
		reset();
	}
}

void GameBoard::reset()
{
	for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            if (board[i][j] != NULL) {
				delete board[i][j];
				board[i][j] = NULL;
			}
        }
    }
}


// Much simpler scoring mechanism, sucks 
void GameBoard::calculateScorePhase()
{
	BlockColors::Color lastColor = BlockColors::BACKGROUND_GREY;
	BlockColors::Color currentColor;

	score = 0;
	for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
			Block *block = board[j][i];
			if (block != NULL)
			{
				currentColor = block->getColor();
				if (lastColor == currentColor)
				{
					score += 10;
					lastColor = currentColor;
				} else {
					score -= 2;
					lastColor = BlockColors::BACKGROUND_GREY;
				}
			}
        }
    }
}

void GameBoard::calculateScoreForRow(unsigned int row)
{

}

void GameBoard::moveBlockGroupBy(int x, int y)
{
	Block::Position currentPosition = blockGroup->getPosition();

	Block::Position newPosition;
	newPosition.x = x + currentPosition.x;
	newPosition.y = y + currentPosition.y;

	bool topPositionUnlocked, middlePositionUnlocked, bottomPositionUnlocked;

	switch(blockGroup->getOrientation())
    {
    case(BlockGroup::HORIZONTAL):
    case(BlockGroup::REVERSE_HORIZONTAL):
		topPositionUnlocked    = positionUnblocked(newPosition.x - 1, newPosition.y);
		middlePositionUnlocked = positionUnblocked(newPosition.x,     newPosition.y);
		bottomPositionUnlocked = positionUnblocked(newPosition.x + 1, newPosition.y);
		break;
    case(BlockGroup::VERTICAL):
    case(BlockGroup::REVERSE_VERTICAL):
		topPositionUnlocked    = positionUnblocked(newPosition.x, newPosition.y - 1);
		middlePositionUnlocked = positionUnblocked(newPosition.x, newPosition.y);
		bottomPositionUnlocked = positionUnblocked(newPosition.x, newPosition.y + 1);
		break;
    default:
        // Do error handling here yo.
        return;
    }

	if (topPositionUnlocked && middlePositionUnlocked && bottomPositionUnlocked)
	{
		blockGroup->setPosition(newPosition);
	}
}

void GameBoard::changeBlockOrientation()
{
	if (blockGroupCanRotate(*blockGroup))
	{
		blockGroup->cycleOrientation();
	}
}


BlockGroup* GameBoard::makeNewBlockGroup()
{
	Block* blockTop    = blockFactory.makeRandomColoredBlock();
	Block* blockMiddle = blockFactory.makeRandomColoredBlock();
	Block* blockBottom = blockFactory.makeRandomColoredBlock();

	BlockGroup* blockGroup = new BlockGroup(*blockTop, *blockMiddle, *blockBottom);
    blockGroup->setPosition((rand() % width),1);

	return blockGroup;
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
		return false;
    }
}



bool GameBoard::positionsUnblocked( Block::Position p1, Block::Position p2, Block::Position p3 )
{
    return positionUnblocked(p1) && positionUnblocked(p2) && positionUnblocked(p3);
}

bool GameBoard::positionWithinBounds( Block::Position position )
{
    return positionWithinBounds(position.x, position.y);
}

bool GameBoard::positionWithinBounds( int x, int y )
{
    bool xWithinBounds = x >= 0 && x < width;
    bool yWithinBounds = y >= 0 && y < height;

    return xWithinBounds && yWithinBounds;
}

bool GameBoard::positionUnblocked( Block::Position position )
{
    return positionUnblocked(position.x, position.y);
}

bool GameBoard::positionsUnblocked( int x1, int y1, int x2, int y2, int x3, int y3 )
{
    return positionUnblocked(x1,y1) && positionUnblocked(x2,y2) && positionUnblocked(x3,y3);
}

bool GameBoard::positionUnblocked( int x, int y )
{
    return positionWithinBounds(x,y) && board[x][y] == NULL;
}


void GameBoard::persistBlockGroup(BlockGroup &blockGroup)
{
	Block *blockTop = blockGroup.getTopBlock();
	Block *blockMiddle = blockGroup.getMiddleBlock();
	Block *blockBottom = blockGroup.getBottomBlock();

	persistBlock(*blockTop);
	persistBlock(*blockMiddle);
	persistBlock(*blockBottom);
}


void GameBoard::persistBlock(Block &block)
{
	Block::Position position = block.getPosition();
	board[position.x][position.y] = &block;
}


int GameBoard::getScore() {
	return score;
}