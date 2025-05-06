#pragma once

#include "character.h"
#include "chuong_ngai_vat.h"
#include "map.h"
#include "music.h"
#include "power.h" // Thêm include cho lớp PowerUp
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class game:LTexture
{
public:
    struct input
    {
        enum type { QUIT, PLAY, NONE, PAUSE};
        type Type;
    };

    input userInput;
    character duck;
    pipe pipe;
    sound sound;
    land land;
    PowerUp powerUp; // Thêm đối tượng PowerUp

public:
    game();
    ~game();

    bool initGraphic();
    bool isQuit()
    {
        return quit;
    }

    bool isDie()
    {
        return die;
    }

    int getPipeWidth()
    {
        return pipe.width();
    }

    int getPipeHeight()
    {
        return pipe.height();
    }

    void takeInput();
    void display();
    void releaseGraphic();
    void renderScoreSmall();
    void renderScoreLarge();
    void renderBestScore();
    void renderMessage();
    void renderBackground();
    void renderBackgroundNight();
    void renderLand();
    void resume();
    void pause();
    void renderPauseTab();
    void lightTheme();
    void darkTheme();
    void nextButton();
    bool changeTheme();
    void renderGameOver();
    void renderMedal();
    void replay();
    bool checkReplay();
    void Restart();

    // Thêm hàm để kiểm tra và xử lý va chạm với powerup
    void checkPowerUpCollision();

    // Thêm hàm để hiển thị thời gian hiệu ứng còn lại
    void renderEffectTimers();

private:
    const double scaleNumberS = 0.75;
    short int bestScore;
    LTexture backgroundDayTexture;
    LTexture backgroundNightTexture;
};
