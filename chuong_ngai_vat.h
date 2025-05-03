// Thay đổi trong file chuong_ngai_vat.h
#pragma once

#include "lib.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Cấu trúc lưu thông tin về vị trí và màu của ống
struct PipeInfo {
    position pos;
    SDL_Color color; // Thông tin về màu sắc
};

extern vector<PipeInfo> pipeInfos;

class pipe:LTexture
{
private:
    const short int randMin = -373 + 30;
    const short int randMax = SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_DISTANCE - 30;

    // Mảng các màu sắc có thể có - bao gồm đỏ, lục, lam, chàm, tím
    SDL_Color availableColors[10] = {
        {255, 255, 255, 255},  // Trắng (bình thường)
        {255, 100, 100, 255},  // Đỏ
        {100, 255, 100, 255},  // Lục
        {100, 100, 255, 255},  // Lam
        {75, 0, 130, 255},     // Chàm
        {148, 0, 211, 255},    // Tím
        {255, 165, 0, 255},    // Cam
        {255, 255, 0, 255},    // Vàng
        {0, 255, 255, 255},    // Lục lam
        {255, 0, 255, 255}     // Hồng tím
    };

    SDL_Texture* originalTexture; // Lưu texture gốc

public:
    bool init();

    void Free();

    void render();

    void update();

    short int width() {return getWidth();}

    short int height() {return getHeight();}

    // Hàm để tạo màu ngẫu nhiên cho ống
    SDL_Color getRandomColor();

    // Hàm để tạo texture với màu cụ thể
    SDL_Texture* createColoredTexture(SDL_Texture* original, SDL_Color color);
};
