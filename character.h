#pragma once

#include "lib.h"
#include "chuong_ngai_vat.h"
#include <string>

using namespace std;

class character:LTexture
{
public:
    bool init(bool isDark);
    void render();
    void Free();
    void resetTime()
    {
        time = 0;
    }
    void fall();
    void update(short int pileWidth, short int pileHeight, bool ghostActive = false);


    short int getX() { return posChar.x; }
    short int getY() { return posChar.y; }
    short int getWidth() { return DUCK_WIDTH; }
    short int getHeight() { return DUCK_HEIGHT; }

private:
    short int angle, time, x0;
    short int ahead = 0;
    string saved_path = "";
    position posChar;
};
