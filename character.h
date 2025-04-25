#pragma once

#include "lib.h"
#include "chuong_ngai_vat.h"
#include <string>

class doge : public LTexture
{
public:
    bool init(bool isDark);
    void render();
    void Free();
    void resetTime()
    {
        time = 0;
    }
    void jump();
    void fall();
    void update(pipe& p);

    short int getPosY() const { return posDoge.y; } // Đảm bảo có getter

private:
    short int angle, time, x0;
    size_t ahead = 0;
    std::string saved_path = "";
    position posDoge;
};
