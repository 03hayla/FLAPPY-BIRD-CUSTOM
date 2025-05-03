
#pragma once

#include "lib.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;


struct PipeInfo {
    position pos;
    SDL_Color color;
};

extern vector<PipeInfo> pipeInfos;

class pipe:LTexture
{
private:
    const short int randMin = -373 + 30;
    const short int randMax = SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_DISTANCE - 30;


    SDL_Color availableColors[10] = {
        {255, 255, 255, 255},
        {255, 100, 100, 255},
        {100, 255, 100, 255},
        {100, 100, 255, 255},
        {75, 0, 130, 255},
        {148, 0, 211, 255},
        {255, 165, 0, 255},
        {255, 255, 0, 255},
        {0, 255, 255, 255},
        {255, 0, 255, 255}
    };

    SDL_Texture* originalTexture;

public:
    bool init();

    void Free();

    void render();

    void update();

    short int width() {return getWidth();}

    short int height() {return getHeight();}


    SDL_Color getRandomColor();


    SDL_Texture* createColoredTexture(SDL_Texture* original, SDL_Color color);
};
