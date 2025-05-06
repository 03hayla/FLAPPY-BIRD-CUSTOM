#include "power.h"

bool PowerUp::init() {
    srand(static_cast<unsigned int>(time(nullptr)));


    if (Load("anh_amthanh/boxmys.png", 1)) {

        SDL_Surface* speedUpSurface = IMG_Load("anh_amthanh/blackbox.png");
        SDL_Surface* ghostSurface = IMG_Load("anh_amthanh/boxmys.png");

        if (speedUpSurface && ghostSurface) {

            speedUpTexture = SDL_CreateTextureFromSurface(gRenderer, speedUpSurface);
            ghostTexture = SDL_CreateTextureFromSurface(gRenderer, ghostSurface);


            SDL_FreeSurface(speedUpSurface);
            SDL_FreeSurface(ghostSurface);


            if (!speedUpTexture) {

                speedUpTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888,
                                               SDL_TEXTUREACCESS_TARGET, getWidth(), getHeight());
                SDL_SetRenderTarget(gRenderer, speedUpTexture);
                SDL_SetTextureColorMod(Texture, 255, 0, 0);
                SDL_RenderCopy(gRenderer, Texture, NULL, NULL);
                SDL_SetTextureColorMod(Texture, 255, 255, 255);
                SDL_SetRenderTarget(gRenderer, NULL);
            }

            if (!ghostTexture) {

                ghostTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET, getWidth(), getHeight());
                SDL_SetRenderTarget(gRenderer, ghostTexture);
                SDL_SetTextureColorMod(Texture, 0, 0, 255);
                SDL_RenderCopy(gRenderer, Texture, NULL, NULL);
                SDL_SetTextureColorMod(Texture, 255, 255, 255);
                SDL_SetRenderTarget(gRenderer, NULL);
            }
        }


        spawnTimer = 0;
        nextSpawnTime = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME + 1) + MIN_SPAWN_TIME;


        speedUpEffectTimer = 0;
        ghostEffectTimer = 0;

        return true;
    }
    return false;
}

void PowerUp::Free() {

    if (speedUpTexture) {
        SDL_DestroyTexture(speedUpTexture);
        speedUpTexture = NULL;
    }

    if (ghostTexture) {
        SDL_DestroyTexture(ghostTexture);
        ghostTexture = NULL;
    }


    free();
}

void PowerUp::render() {
    for (auto& powerup : powerUps) {
        if (powerup.active) {

            SDL_Texture* currentTexture = Texture;

            if (powerup.type == SPEED_UP && speedUpTexture) {
                currentTexture = speedUpTexture;
            } else if (powerup.type == GHOST && ghostTexture) {
                currentTexture = ghostTexture;
            }

            SDL_Texture* oldTexture = Texture;


            Texture = currentTexture;

            Render(powerup.pos.x, powerup.pos.y);


            Texture = oldTexture;
        }
    }
}


bool PowerUp::isCollidingWithPipe(int x, int y, int width, int height) {

    const int SAFE_DISTANCE = 20;

    for (int i = 0; i < TOTAL_PIPE; i++) {

        if (x + width + SAFE_DISTANCE > pipeInfos[i].pos.x &&
            x - SAFE_DISTANCE < pipeInfos[i].pos.x + 52) {
            return true;
        }
    }
    return false;
}


position PowerUp::findSafePosition() {
    position pos;
    const int MAX_ATTEMPTS = 10;

    for (int attempts = 0; attempts < MAX_ATTEMPTS; attempts++) {

        int randY = rand() % (SCREEN_HEIGHT - LAND_HEIGHT - 32 - 100) + 100;
        pos.getPos(SCREEN_WIDTH, randY);

        if (!isCollidingWithPipe(pos.x, pos.y, 32, 32)) {
            return pos;
        }
    }

    pos.getPos(SCREEN_WIDTH, SCREEN_HEIGHT / 3);
    return pos;
}

void PowerUp::update() {
    if (!die) {

        for (auto& powerup : powerUps) {
            if (powerup.active) {
                powerup.pos.x -= 3;


                if (powerup.pos.x < -32) {
                    powerup.active = false;
                }
            }
        }


        spawnTimer++;
        if (spawnTimer >= nextSpawnTime) {

            for (auto it = powerUps.begin(); it != powerUps.end();) {
                if (!it->active) {
                    it = powerUps.erase(it);
                } else {
                    ++it;
                }
            }


            PowerUpInfo newPowerUp;
            newPowerUp.pos = findSafePosition();
            newPowerUp.active = true;
            newPowerUp.type = static_cast<PowerUpType>(rand() % TOTAL_TYPES);

            powerUps.push_back(newPowerUp);

            spawnTimer = 0;
            nextSpawnTime = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME + 1) + MIN_SPAWN_TIME;
        }

        if (speedUpEffectTimer > 0) {
            speedUpEffectTimer--;
        }

        if (ghostEffectTimer > 0) {
            ghostEffectTimer--;
        }
    }
}

bool PowerUp::checkCollision(int duckX, int duckY, int duckWidth, int duckHeight) {
    for (auto& powerup : powerUps) {
        if (powerup.active) {

            if (duckX < powerup.pos.x + 32 &&
                duckX + duckWidth > powerup.pos.x &&
                duckY < powerup.pos.y + 32 &&
                duckY + duckHeight > powerup.pos.y) {


                activateEffect(powerup.type);


                powerup.active = false;
                return true;
            }
        }
    }

    return false;
}

void PowerUp::activateEffect(PowerUpType type) {

    switch (type) {
        case SPEED_UP:
            activateSpeedUp();
            break;
        case GHOST:
            activateGhost();
            break;
        default:
            break;
    }
}

bool PowerUp::reset() {

    powerUps.clear();


    spawnTimer = 0;
    nextSpawnTime = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME + 1) + MIN_SPAWN_TIME;

    speedUpEffectTimer = 0;
    ghostEffectTimer = 0;

    return true;
}
