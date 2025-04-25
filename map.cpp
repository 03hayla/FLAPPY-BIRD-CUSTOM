#include "map.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
//hàm tải hình ảnh mặt đất
bool land::init()
{
    posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
    string back_path = "land.png";
    if (isNULL())
    {
        if (Load(back_path.c_str(), 1))
        {
            return true;
        }
        else
        {
            cout << "Failed to load land.png! SDL_image Error: " << IMG_GetError() <<endl;
            return false;
        }
    }
    return false;
}
//hàm vẽ ảnh ,tạo hiệu ứng cuộn liên tục
void land::render()
{
    Render(posLand.x, posLand.y);
    Render(posLand.x + getWidth(), posLand.y);
    if (posLand.x <= -getWidth())
    {
        posLand.x += getWidth();
    }
}
void land::update()
{
    posLand.x -= 3;
}
//hàm giải phóng tài nguyên
void land::Free()
{
    free();
}

