#pragma once

#include <stdint.h>

struct GemAnimation {
    uint8_t frame;
};

struct GemImage {
    uint8_t r, b;
};

void randomGemImage(struct GemImage *image);
void displayGemImage(struct GemImage *image);
void gemAnimationFrame(struct GemAnimation *animation);