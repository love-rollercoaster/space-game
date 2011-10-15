#pragma once

#include "GameObject.h"
#include "GraphicsEngine.h"

class ScorePanel
	// : public GameObject
{
public:
	ScorePanel(void);
	~ScorePanel(void);

	// void draw(GraphicsEngine &graphicsEngine);

	// void setScore(int score);

private:
	int score;
};

