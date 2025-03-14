#include "gem.h"
#include "st7789.h"
#include "src/xorshiftrng/xorshift_rng.h"

void randomGemImage(struct GemImage *image)
{
    image->r = xorshift8_uint(8);
    image->b = xorshift8_uint(8);
}

void displayGemImage(struct GemImage *image) {
    uint8_t mask = 1;
    for (uint8_t x=0; x<2; x++) for (uint8_t y=0; y<4; y++) {
      uint16_t color = 0;
      if (image->r & mask) color += 0xF800;
      if (image->b & mask) color += 0x001F;
      if (image->r & image -> b & mask) color += 0x07E0;
      st7789_FillRect(104 + x*40, 144 + x*40, y*30, 30 + y*30, color);
      st7789_FillRect(104 - x*40, 144 - x*40, y*30, 30 + y*30, color);
      mask<<=1;
    }
}

void gemAnimationFrame(struct GemAnimation *animation) {
    animation->frame++;
    uint8_t y = (animation->frame & 0b001) ? 0 : 60;
    uint8_t x = (animation->frame & 0b010) ? 60 : 120;
    st7789_FillRect(x, x + 60, y, y + 60, (animation->frame & 0b100) ? 0xFFFF : 0);
}