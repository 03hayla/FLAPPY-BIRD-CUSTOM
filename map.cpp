#include "map.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool land::init()
{
    posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
    string back_path = "anh_amthanh/land.png";
    if (isNULL())
    {
        if ( Load( back_path.c_str(), 1 ) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void land::Free()
{
    free();
}

void land::render()
{

    int landWidth = getWidth();
    int numTiles = (SCREEN_WIDTH / landWidth) + 2;


    int offset = posLand.x % landWidth;
    if (offset > 0) offset -= landWidth;

    for (int i = 0; i < numTiles; i++) {
        Render(offset + i * landWidth, posLand.y);
    }
}

void land::update()
{
    posLand.x -= 3;
}
