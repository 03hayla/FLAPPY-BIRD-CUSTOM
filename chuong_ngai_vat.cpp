#include "chuong_ngai_vat.h"
#include <cstdlib>
#include <ctime>

bool pipe::init()
{
    srand(time(0));
    std::string pipe_path = "pipe.png";
    if (isNULL())
    {
        if (Load(pipe_path.c_str(), 1))
        {

            PipePair p;
            p.posPipe.getPos(SCREEN_WIDTH, 0);
            p.gapY = randMin + (rand() % (randMax - randMin + 1));
            p.passed = false;
            pipes.push_back(p);
            return true;
        }
        else
        {
            std::cout << "Failed to load pipe.png! SDL_image Error: " << IMG_GetError() << std::endl;
            return false;
        }
    }
    return false;
}

void pipe::Free()
{
    free();
    pipes.clear();
}

void pipe::render()
{
    for (auto& p : pipes)
    {

        Render(p.posPipe.x, p.gapY + PIPE_DISTANCE, 0, NULL, SDL_FLIP_VERTICAL);

        Render(p.posPipe.x, p.gapY - getHeight(), 0, NULL);
    }
}

void pipe::update()
{

    for (auto& p : pipes)
    {
        p.posPipe.x -= 3;
    }


    if (!pipes.empty() && pipes[0].posPipe.x < -getWidth())
    {
        pipes.erase(pipes.begin());
    }


    if (pipes.empty() || pipes.back().posPipe.x < SCREEN_WIDTH - PIPE_SPACING)
    {
        PipePair p;
        p.posPipe.getPos(SCREEN_WIDTH, 0);
        p.gapY = randMin + (rand() % (randMax - randMin + 1));
        p.passed = false;
        pipes.push_back(p);
    }
}
