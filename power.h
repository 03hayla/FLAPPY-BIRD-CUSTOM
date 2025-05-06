#pragma once

#include "lib.h"
#include "chuong_ngai_vat.h"
#include <vector>
#include <ctime>
#include <cstdlib>

enum PowerUpType {
    SPEED_UP,
    GHOST,
    TOTAL_TYPES
};

struct PowerUpInfo {
    position pos;
    bool active;
    PowerUpType type;
};

class PowerUp : public LTexture {
private:
    const short int MIN_SPAWN_TIME = 180;
    const short int MAX_SPAWN_TIME = 360;
    short int spawnTimer;
    short int nextSpawnTime;

    std::vector<PowerUpInfo> powerUps;


    SDL_Texture* speedUpTexture;
    SDL_Texture* ghostTexture;


    bool isCollidingWithPipe(int x, int y, int width, int height);
    position findSafePosition();

public:
    bool init();
    void Free();
    void render();
     bool reset();
    void update();
    bool checkCollision(int duckX, int duckY, int duckWidth, int duckHeight);


    short int speedUpEffectTimer;
    short int ghostEffectTimer;

    bool isSpeedUpActive() { return speedUpEffectTimer > 0; }
    bool isGhostActive() { return ghostEffectTimer > 0; }


    void activateEffect(PowerUpType type);
    void activateSpeedUp() { speedUpEffectTimer = 180; }
    void activateGhost() { ghostEffectTimer = 180; }
};
