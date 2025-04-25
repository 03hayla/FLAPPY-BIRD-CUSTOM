#ifndef CHUONG_NGAI_VAT_H
#define CHUONG_NGAI_VAT_H
#include "lib.h"
#include <vector>

class pipe : public LTexture
{
public:
    bool init();
    void Free();
    void render();
    void update();

    struct PipePair
    {
        position posPipe;
        short int gapY;
        bool passed;
    };

    size_t getPipeCount() const { return pipes.size(); }
    const PipePair& getPipe(size_t index) const { return pipes[index]; }
    short int width() const { return getWidth(); }
    short int height() const { return getHeight(); }
    short int getPipeDistance() const { return PIPE_DISTANCE; }
    void markPipeAsPassed(size_t index) { if (index < pipes.size()) pipes[index].passed = true; }

private:
    std::vector<PipePair> pipes;
    short int randMin = 150; // Giá trị Y tối thiểu của khoảng trống
    short int randMax = 350; // Giá trị Y tối đa của khoảng trống
    const short int PIPE_SPACING = PIPE_SPACE + PIPE_DISTANCE;
};

#endif // CHUONG_NGAI_VAT_H
