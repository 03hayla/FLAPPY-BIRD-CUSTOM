#include "power.h"

bool PowerUp::init() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Load texture chính cho đối tượng (có thể dùng texture mặc định)
    if (Load("anh_amthanh/boxmys.png", 1)) {
        // Tạo texture riêng cho hai loại power-up
        SDL_Surface* speedUpSurface = IMG_Load("anh_amthanh/blackbox.png");
        SDL_Surface* ghostSurface = IMG_Load("anh_amthanh/boxmys.png");

        if (speedUpSurface && ghostSurface) {
            // Tạo texture từ surface
            speedUpTexture = SDL_CreateTextureFromSurface(gRenderer, speedUpSurface);
            ghostTexture = SDL_CreateTextureFromSurface(gRenderer, ghostSurface);

            // Giải phóng surface
            SDL_FreeSurface(speedUpSurface);
            SDL_FreeSurface(ghostSurface);

            // Nếu không tìm thấy ảnh, tạo texture màu khác nhau
            if (!speedUpTexture) {
                // Fallback: Sử dụng texture chính và thay đổi màu
                speedUpTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888,
                                               SDL_TEXTUREACCESS_TARGET, getWidth(), getHeight());
                SDL_SetRenderTarget(gRenderer, speedUpTexture);
                SDL_SetTextureColorMod(Texture, 255, 0, 0); // Màu đỏ cho Speed Up
                SDL_RenderCopy(gRenderer, Texture, NULL, NULL);
                SDL_SetTextureColorMod(Texture, 255, 255, 255); // Đặt lại màu
                SDL_SetRenderTarget(gRenderer, NULL);
            }

            if (!ghostTexture) {
                // Fallback: Sử dụng texture chính và thay đổi màu
                ghostTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET, getWidth(), getHeight());
                SDL_SetRenderTarget(gRenderer, ghostTexture);
                SDL_SetTextureColorMod(Texture, 0, 0, 255); // Màu xanh cho Ghost
                SDL_RenderCopy(gRenderer, Texture, NULL, NULL);
                SDL_SetTextureColorMod(Texture, 255, 255, 255); // Đặt lại màu
                SDL_SetRenderTarget(gRenderer, NULL);
            }
        }

        // Khởi tạo các bộ đếm thời gian
        spawnTimer = 0;
        nextSpawnTime = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME + 1) + MIN_SPAWN_TIME;

        // Khởi tạo bộ đếm thời gian hiệu ứng
        speedUpEffectTimer = 0;
        ghostEffectTimer = 0;

        return true;
    }
    return false;
}

void PowerUp::Free() {
    // Giải phóng texture riêng
    if (speedUpTexture) {
        SDL_DestroyTexture(speedUpTexture);
        speedUpTexture = NULL;
    }

    if (ghostTexture) {
        SDL_DestroyTexture(ghostTexture);
        ghostTexture = NULL;
    }

    // Giải phóng texture chính
    free();
}

void PowerUp::render() {
    for (auto& powerup : powerUps) {
        if (powerup.active) {
            // Chọn texture dựa vào loại power-up
            SDL_Texture* currentTexture = Texture; // Mặc định

            if (powerup.type == SPEED_UP && speedUpTexture) {
                currentTexture = speedUpTexture;
            } else if (powerup.type == GHOST && ghostTexture) {
                currentTexture = ghostTexture;
            }

            // Lưu texture hiện tại
            SDL_Texture* oldTexture = Texture;

            // Cập nhật texture tạm thời để render
            Texture = currentTexture;

            // Render power-up
            Render(powerup.pos.x, powerup.pos.y);

            // Khôi phục texture cũ
            Texture = oldTexture;
        }
    }
}

// Kiểm tra xem vị trí (x, y) có trùng với bất kỳ cột nào không
bool PowerUp::isCollidingWithPipe(int x, int y, int width, int height) {
    // Khoảng cách an toàn từ cột
    const int SAFE_DISTANCE = 20;

    for (int i = 0; i < TOTAL_PIPE; i++) {
        // Kiểm tra nếu power-up nằm trong phạm vi của cột (theo chiều ngang)
        if (x + width + SAFE_DISTANCE > pipeInfos[i].pos.x &&
            x - SAFE_DISTANCE < pipeInfos[i].pos.x + 52) { // 52 là chiều rộng của cột
            return true;
        }
    }
    return false;
}

// Tìm vị trí an toàn không đè lên cột
position PowerUp::findSafePosition() {
    position pos;
    const int MAX_ATTEMPTS = 10; // Số lần thử tối đa

    for (int attempts = 0; attempts < MAX_ATTEMPTS; attempts++) {
        // Tạo vị trí ngẫu nhiên
        int randY = rand() % (SCREEN_HEIGHT - LAND_HEIGHT - 32 - 100) + 100;
        pos.getPos(SCREEN_WIDTH, randY);

        // Kiểm tra nếu vị trí này an toàn
        if (!isCollidingWithPipe(pos.x, pos.y, 32, 32)) {
            return pos;
        }
    }

    // Nếu không tìm được vị trí an toàn sau nhiều lần thử, chọn vị trí xa nhất từ các cột
    pos.getPos(SCREEN_WIDTH, SCREEN_HEIGHT / 3);
    return pos;
}

void PowerUp::update() {
    if (!die) {
        // Cập nhật vị trí của các powerup hiện có
        for (auto& powerup : powerUps) {
            if (powerup.active) {
                powerup.pos.x -= 3; // Di chuyển cùng tốc độ với cột

                // Loại bỏ powerup nếu đi ra khỏi màn hình
                if (powerup.pos.x < -32) {
                    powerup.active = false;
                }
            }
        }

        // Tạo powerup mới
        spawnTimer++;
        if (spawnTimer >= nextSpawnTime) {
            // Xóa các powerup không còn hoạt động
            for (auto it = powerUps.begin(); it != powerUps.end();) {
                if (!it->active) {
                    it = powerUps.erase(it);
                } else {
                    ++it;
                }
            }

            // Tạo powerup mới với loại xác định và vị trí an toàn
            PowerUpInfo newPowerUp;
            newPowerUp.pos = findSafePosition();
            newPowerUp.active = true;
            newPowerUp.type = static_cast<PowerUpType>(rand() % TOTAL_TYPES); // Chọn loại ngẫu nhiên

            powerUps.push_back(newPowerUp);

            // Đặt lại bộ đếm thời gian
            spawnTimer = 0;
            nextSpawnTime = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME + 1) + MIN_SPAWN_TIME;
        }

        // Cập nhật bộ đếm thời gian hiệu ứng
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
            // Kiểm tra va chạm
            if (duckX < powerup.pos.x + 32 &&
                duckX + duckWidth > powerup.pos.x &&
                duckY < powerup.pos.y + 32 &&
                duckY + duckHeight > powerup.pos.y) {

                // Kích hoạt hiệu ứng tương ứng với loại power-up
                activateEffect(powerup.type);

                // Đánh dấu power-up đã được sử dụng
                powerup.active = false;
                return true;
            }
        }
    }

    return false;
}

void PowerUp::activateEffect(PowerUpType type) {
    // Kích hoạt hiệu ứng dựa trên loại power-up
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
// Thêm phương thức reset() cho lớp PowerUp trong power.cpp
bool PowerUp::reset() {
    // Xóa tất cả power-up hiện có
    powerUps.clear();

    // Đặt lại các bộ đếm thời gian
    spawnTimer = 0;
    nextSpawnTime = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME + 1) + MIN_SPAWN_TIME;

    // Đặt lại bộ đếm thời gian hiệu ứng
    speedUpEffectTimer = 0;
    ghostEffectTimer = 0;

    return true;
}
