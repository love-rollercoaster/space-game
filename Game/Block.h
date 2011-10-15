#pragma once
#include "gameobject.h"
#include <d3dx9.h>
#include <stdlib.h>

namespace BlockColors {
    enum Color {
        RED,
        WHITE,
        GREEN,
        BLUE,
		BACKGROUND_GREY
    };
}

class Block :
    public GameObject
{
public:
    Block(BlockColors::Color color)
        : color(color)
    {
        setPosition(0, 0);
    }

    struct Position {
        unsigned int x;
        unsigned int y;
    };

    Position getPosition();
    BlockColors::Color getColor();

    void setPosition(Position position);
    void setPosition(int x);
    void setPosition(int x, int y);

private:
    Position position;
    BlockColors::Color const color;
};

