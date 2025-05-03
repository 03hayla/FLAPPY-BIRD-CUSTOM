#include "chuong_ngai_vat.h"
#include "stdio.h"

vector<PipeInfo> pipeInfos; // Thay thế vector<position> posPipe

bool pipe::init()
{
    // Đảm bảo đã khởi tạo bộ tạo số ngẫu nhiên
    srand(static_cast<unsigned int>(time(nullptr)));

    pipeInfos.clear();
    for (signed char i = 0; i < TOTAL_PIPE; i++)
    {
        PipeInfo temp;
        temp.pos.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 150, (rand() % (randMax - randMin + 1)) + randMin);
        temp.color = getRandomColor(); // Gán màu ngẫu nhiên cho mỗi ống
        pipeInfos.push_back(temp);
    }

    if (isNULL())
    {
        if (Load("anh_amthanh/pipe.png", 1))
        {
            // Lưu texture gốc để sử dụng cho việc tạo các phiên bản màu khác nhau
            originalTexture = Texture;
            return true;
        }
    }
    return false;
}

void pipe::Free()
{
    free();

    // Giải phóng texture gốc nếu nó tồn tại
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
            // Lưu texture hiện tại
            SDL_Texture* currentTexture = Texture;

            // Tạo texture với màu của ống hiện tại
            Texture = createColoredTexture(originalTexture, pipeInfos[i].color);

            // Render ống
            Render(pipeInfos[i].pos.x, pipeInfos[i].pos.y);
            Render(pipeInfos[i].pos.x, pipeInfos[i].pos.y + getHeight() + PIPE_SPACE, 180);

            // Khôi phục texture gốc nếu cần
            if (Texture != currentTexture && Texture != originalTexture) {
                SDL_DestroyTexture(Texture);
            }
            Texture = currentTexture;
        }
    }
}

void pipe::update()
{
    if (!die)
    {
        for (signed char i = 0; i < TOTAL_PIPE; i++)
        {
            if (pipeInfos[i].pos.x < -getWidth())
            {
                pipeInfos[i].pos.y = (rand() % (randMax - randMin + 1)) + randMin;
                pipeInfos[i].pos.x = pipeInfos[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].pos.x + PIPE_DISTANCE;
                pipeInfos[i].color = getRandomColor(); // Tạo màu mới khi ống được tạo lại
            }
            else
            {
                pipeInfos[i].pos.x -= 3;
            }
        }
    }
}

SDL_Color pipe::getRandomColor()
{
    // Chọn một màu ngẫu nhiên từ mảng các màu sẵn có (10 màu)
    return availableColors[rand() % 10];
}

SDL_Texture* pipe::createColoredTexture(SDL_Texture* original, SDL_Color color)
{
    // Nếu màu là trắng (mặc định), trả về texture gốc
    if (color.r == 255 && color.g == 255 && color.b == 255) {
        return original;
    }

    // Lấy thông tin về kích thước của texture gốc
    int width, height;
    SDL_QueryTexture(original, NULL, NULL, &width, &height);

    // Tạo texture mới từ texture gốc
    SDL_Texture* targetTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_TARGET, width, height);
    if (!targetTexture) {
        return original; // Nếu không tạo được texture, trả về texture gốc
    }

    // Thiết lập texture mới làm đích render
    SDL_SetRenderTarget(gRenderer, targetTexture);

    // Vẽ texture gốc lên texture đích
    SDL_RenderCopy(gRenderer, original, NULL, NULL);

    // Áp dụng màu sắc
    SDL_SetTextureColorMod(targetTexture, color.r, color.g, color.b);

    // Quay lại render target mặc định
    SDL_SetRenderTarget(gRenderer, NULL);

    return targetTexture;
}
