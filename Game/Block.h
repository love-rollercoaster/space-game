#pragma once
#include "gameobject.h"
#include <d3dx9.h>


namespace BlockColors {
    enum Color {
        RED,
        WHITE,
        GREEN,
        BLUE
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
    void setPosition(unsigned int x);
    void setPosition(unsigned int x, unsigned int y);

private:
    Position position;
    BlockColors::Color const color;
};

