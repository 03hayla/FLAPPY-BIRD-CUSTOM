#include "chuong_ngai_vat.h"
#include "stdio.h"

vector<PipeInfo> pipeInfos;

bool pipe::init()
{

    srand(static_cast<unsigned int>(time(nullptr)));

    pipeInfos.clear();
    for (signed char i = 0; i < TOTAL_PIPE; i++)
    {
        PipeInfo temp;
        temp.pos.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 150, (rand() % (randMax - randMin + 1)) + randMin);
        temp.color = getRandomColor();
        pipeInfos.push_back(temp);
    }

    if (isNULL())
    {
        if (Load("anh_amthanh/pipe.png", 1))
        {

            originalTexture = Texture;
            return true;
        }
    }
    return false;
}

void pipe::Free()
{
    free();


    if (originalTexture != NULL && originalTexture != Texture) {
        SDL_DestroyTexture(originalTexture);
        originalTexture = NULL;
    }
}

void pipe::render()
{
    for (signed char i = 0; i < TOTAL_PIPE; i++)
    {
        if (pipeInfos[i].pos.x <= SCREEN_WIDTH && pipeInfos[i].pos.x > -getWidth())
        {

            SDL_Texture* currentTexture = Texture;


            Texture = createColoredTexture(originalTexture, pipeInfos[i].color);


            Render(pipeInfos[i].pos.x, pipeInfos[i].pos.y);
            Render(pipeInfos[i].pos.x, pipeInfos[i].pos.y + getHeight() + PIPE_SPACE, 180);


            if (Texture != currentTexture && Texture != originalTexture) {
                SDL_DestroyTexture(Texture);
            }
            Texture = currentTexture;
        }
    }
}

void pipe::update(bool isSpeedUp)
{
    if (!die)
    {

        short int speed = isSpeedUp ? 6 : 3;

        for (signed char i = 0; i < TOTAL_PIPE; i++)
        {
            if (pipeInfos[i].pos.x < -getWidth())
            {
                pipeInfos[i].pos.y = (rand() % (randMax - randMin + 1)) + randMin;
                pipeInfos[i].pos.x = pipeInfos[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].pos.x + PIPE_DISTANCE;
                pipeInfos[i].color = getRandomColor();
            }
            else
            {
                pipeInfos[i].pos.x -= speed;
            }
        }
    }
}

SDL_Color pipe::getRandomColor()
{
    return availableColors[rand() % 10];
}

SDL_Texture* pipe::createColoredTexture(SDL_Texture* original, SDL_Color color)
{
    if (color.r == 255 && color.g == 255 && color.b == 255) {
        return original;
    }

    int width, height;
    SDL_QueryTexture(original, NULL, NULL, &width, &height);

    SDL_Texture* targetTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_TARGET, width, height);
    if (!targetTexture) {
        return original;
    }

    SDL_SetRenderTarget(gRenderer, targetTexture);
    SDL_RenderCopy(gRenderer, original, NULL, NULL);
    SDL_SetTextureColorMod(targetTexture, color.r, color.g, color.b);
    SDL_SetRenderTarget(gRenderer, NULL);

    return targetTexture;
}
