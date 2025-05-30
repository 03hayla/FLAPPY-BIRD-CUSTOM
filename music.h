#pragma once

#include <SDL_mixer.h>
#include <string>
#include "lib.h"

using namespace std;

class sound:LTexture
{
public:
    bool init();

    void Free();

    void playBreath();

    void playHit();
    void  playPowerUp();

    void renderSound();

    bool checkSound();

private:

    const short int POS_X = 330;
    const short int POS_Y = 267;
    bool isPlay = 0;
    Mix_Chunk* breath = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* drop = NULL;
    Mix_Chunk* powerUp = NULL;
    SDL_Rect Mute ;
    SDL_Rect Active ;
};

