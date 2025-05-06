#pragma once

#include "lib.h"
#include "chuong_ngai_vat.h" // Thêm include để truy cập thông tin cột
#include <vector>
#include <ctime>
#include <cstdlib>

enum PowerUpType {
    SPEED_UP, // Tăng tốc độ cột
    GHOST,    // Xuyên qua cột
    TOTAL_TYPES // Sử dụng để đếm tổng số loại
};

struct PowerUpInfo {
    position pos;
    bool active;
    PowerUpType type; // Xác định loại power-up
};

class PowerUp : public LTexture {
private:
    const short int MIN_SPAWN_TIME = 180; // Khoảng 3 giây
    const short int MAX_SPAWN_TIME = 360; // Khoảng 6 giây
    short int spawnTimer;
    short int nextSpawnTime;

    std::vector<PowerUpInfo> powerUps;

    // Texture cho hai loại hộp khác nhau
    SDL_Texture* speedUpTexture;
    SDL_Texture* ghostTexture;

    // Thêm các phương thức hỗ trợ để tránh va chạm với cột
    bool isCollidingWithPipe(int x, int y, int width, int height);
    position findSafePosition();

public:
    bool init();
    void Free();
    void render();
     bool reset();
    void update();
    bool checkCollision(int duckX, int duckY, int duckWidth, int duckHeight);

    // Các hiệu ứng kéo dài 3 giây (180 frames với 60 FPS)
    short int speedUpEffectTimer;
    short int ghostEffectTimer;

    bool isSpeedUpActive() { return speedUpEffectTimer > 0; }
    bool isGhostActive() { return ghostEffectTimer > 0; }

    // Thay thế activateRandomEffect bằng các hàm kích hoạt từng hiệu ứng cụ thể
    void activateEffect(PowerUpType type);
    void activateSpeedUp() { speedUpEffectTimer = 180; } // 3 giây với 60 FPS
    void activateGhost() { ghostEffectTimer = 180; } // 3 giây với 60 FPS
};
