#include "character.h"
#include <stdio.h>
#include <iostream>

bool character::init(bool isDark)
{
    string duck_path = "anh_amthanh/duck-01.png";
    if (isDark) duck_path = "anh_amthanh/Duck-02.png";
    if (saved_path == duck_path)
    {
        posChar.getPos(150, SCREEN_HEIGHT / 2 - 10);
        ahead = 0;
        angle = 0;
    }
    if (isNULL() || saved_path != duck_path)
    {
        saved_path = duck_path;
        if ( Load(duck_path.c_str() , 1) )
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

void character::Free()
{
    free();
}

void character::render()
{
    Render(posChar.x, posChar.y, angle);
}

void character::fall()
{
    if (die && posChar.y < SCREEN_HEIGHT - LAND_HEIGHT - DUCK_HEIGHT - 5)
    {
        if (time == 0)
        {
            x0 = posChar.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posChar.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }
    }
    else return;
}

void   character::update(short int pipeWidth, short int pipeHeight)
{
    if (!die)
    {
        if (time == 0)
        {
            x0 = posChar.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posChar.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }


        if ( (posChar.x + getWidth() > pipeInfos[ahead].pos.x + 5) && (posChar.x + 5 < pipeInfos[ahead].pos.x + pipeWidth) &&
             (posChar.y + 5 < pipeInfos[ahead].pos.y + pipeHeight || posChar.y  + getHeight() > pipeInfos[ahead].pos.y + pipeHeight + PIPE_SPACE + 5) )
        {
            die = true;
        }
        else if (posChar.x > pipeInfos[ahead].pos.x + pipeWidth )
        {
            ahead = ( ahead + 1 ) % TOTAL_PIPE;
            score++;
        }

        if (posChar.y > SCREEN_HEIGHT - LAND_HEIGHT -  DUCK_HEIGHT - 5 || posChar.y < - 10 )
        {
            die = true;
        }
    }
}
