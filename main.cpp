#include "game.h"
#include "lib.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


const short int FPS = 60;
const short int frameDelay = 1000 / FPS;

using namespace std;
pipe g_pipe;

int main(int argc, char** argv)
{
    Uint32 frameStart;
    short int frameTime;
    game g;
    bool isMenu = 0;
    bool isPause = 0;
    bool isSound = 1;
    bool isDark = 0;

    while(!g.isQuit())
    {
        frameStart = SDL_GetTicks();

        if (g.isDie())
        {
            if (isMenu) {
                g.sound.playHit();
                g.duck.render();
            }
            g.userInput.Type = game::input::NONE;
            while(g.isDie() && !g.isQuit())
            {
                g.takeInput();
                if (isMenu == 1 && g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isMenu = 0;
                    }
                    g.userInput.Type = game::input::NONE;
                }
                if (!isDark) g.renderBackground();
                else g.renderBackgroundNight();
                g.pipe.render();
                g.land.render();
                if (isMenu)
                {
                    g.duck.render();
                    g.duck.fall();
                    g.renderGameOver();
                    g.renderMedal();
                    g.renderScoreSmall();
                    g.renderBestScore();
                    g.replay();
                }
                else
                {
                    g.pipe.init();
                    g.duck.init(isDark);
                    g.powerUp.init();
                    g.duck.render();
                    g.renderMessage();
                    if (g.userInput.Type == game::input::PLAY)
                    {
                        g.Restart();
                        isMenu = 1;
                        g.userInput.Type = game::input::NONE;
                    }
                    g.land.update();
                }
                g.display();
            }
            g.pipe.init();
            g.powerUp.reset();
        }
        else
        {
            g.takeInput();

            if (g.userInput.Type == game::input::PAUSE)
            {
                isPause = abs(1 - isPause);
                g.userInput.Type = game::input::NONE;
            }

            if (isPause == 0 && g.userInput.Type == game::input::PLAY)
            {
                if (isSound) g.sound.playBreath();
                g.duck.resetTime();
                g.userInput.Type = game::input::NONE;
            }

            if (!isDark) g.renderBackground();
            else g.renderBackgroundNight();
            g.pipe.render();
            g.powerUp.render();
            g.land.render();
            g.duck.render();
            g.renderScoreLarge();
            g.renderEffectTimers();

            if (!isPause)
            {

                g.checkPowerUpCollision();


                g.duck.update(g.getPipeWidth(), g.getPipeHeight(), g.powerUp.isGhostActive());


                g.pipe.update(g.powerUp.isSpeedUpActive());

                g.powerUp.update();
                g.land.update();
                g.pause();
            }
            else
            {
                g.resume();
                g.renderPauseTab();
                g.renderScoreSmall();
                g.renderBestScore();
                g.replay();
                g.sound.renderSound();
                if (!isDark) g.lightTheme(); else g.darkTheme();
                g.nextButton();
                if (g.userInput.Type == game::input::PLAY)
                {
                    if (g.checkReplay())
                    {
                        isPause = 0;
                    }
                    else if (g.sound.checkSound())
                    {
                        isSound = abs(1 - isSound);
                    }
                    else if (g.changeTheme())
                    {
                        isDark = abs(1 - isDark);
                        g.duck.init(isDark);
                    }
                    g.userInput.Type = game::input::NONE;
                }
            }
            g.display();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}
