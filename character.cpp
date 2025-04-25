#include "character.h"
#include <stdio.h>
#include <iostream>

bool doge::init(bool isDark)
{
    std::string shiba_path = "shiba.png";
    if (isDark) shiba_path = "shiba-dark.png";
    if (saved_path == shiba_path)
    {
        posDoge.getPos(75, SCREEN_HEIGHT / 2 - 10);
        angle = 0;
        time = 0;
    }
    if (isNULL() || saved_path != shiba_path)
    {
        saved_path = shiba_path;
        if (Load(shiba_path.c_str(), 1))
        {
            posDoge.getPos(75, SCREEN_HEIGHT / 2 - 10);
            angle = 0;
            time = 0;
            return true;
        }
        else
        {
            std::cout << "Failed to load shiba.png! SDL_image Error: " << IMG_GetError() << std::endl;
            return false;
        }
    }
    return false;
}

void doge::Free()
{
    free();
}

void doge::render()
{
    Render(posDoge.x, posDoge.y, angle);
}

void doge::jump()
{
    time = 0;
    x0 = posDoge.y;
    angle = -25;
}

void doge::fall()
{
    if (die && posDoge.y < SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5)
    {
        if (time == 0)
        {
            x0 = posDoge.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        posDoge.y = x0 + time * time * 0.05; // Chỉ rơi khi chết
        time++;
    }
    else if (posDoge.y >= SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5)
    {
        posDoge.y = SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5; // Dừng tại đất
    }
}

void doge::update(pipe& p)
{
    if (!die)
    {
        if (time == 0)
        {
            x0 = posDoge.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posDoge.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }

        // Kiểm tra va chạm với tất cả các cột
        for (size_t i = 0; i < p.getPipeCount(); ++i)
        {
            const auto& pipePair = p.getPipe(i);
            short int pipeWidth = p.width();
            short int pipeHeight = p.height();
            short int pipeX = pipePair.posPipe.x;
            short int pipeY = pipePair.gapY;

            // Kiểm tra va chạm với cột trên hoặc cột dưới
            if ((posDoge.x + getWidth() > pipeX + 5) && (posDoge.x + 5 < pipeX + pipeWidth) &&
                (posDoge.y + 5 < pipeY || posDoge.y + getHeight() > pipeY + p.getPipeDistance() + 5))
            {
                die = true;
                break; // Thoát vòng lặp ngay khi va chạm
            }

            // Cộng điểm khi vượt qua cột
            if (posDoge.x > pipeX + pipeWidth && !pipePair.passed)
            {
                score++;
                p.markPipeAsPassed(i);
            }
        }

        // Kiểm tra va chạm với đất hoặc trần
        if (posDoge.y > SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5 || posDoge.y < -10)
        {
            die = true;
        }
    }
}
