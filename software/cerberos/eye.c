#include "eye.h"
#include "st7789.h"
#include "src/xorshiftrng/xorshift_rng.h"

void eyeInit(struct Eye *eye, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2) {
  eye->x1 = x1;
  eye->x2 = x2;
  eye->y1 = y1;
  eye->y2 = y2;
  eye->pupilX = x1 + (x2 - x1) / 2;
  eye->pupilY = y1 + (y2 - y1) / 2;
  eyeDraw(eye);
}

void eyeDraw(struct Eye *eye) {
  eyeDrawColor(eye, EYE_COLOR);
}

void eyeDrawColor(struct Eye *eye, uint16_t color) {
  st7789_FillRect(eye->x1, eye->x2, eye->y1, eye->y2, color);
  eyePupilDraw(eye, PUPIL_COLOR);
}

void eyePupilDraw(struct Eye *eye, uint16_t color) {
  st7789_FillCircle(eye->pupilX, eye->pupilY, PUPIL_RADIUS, color);
}

void shiftAnimationInit(struct ShiftAnimation *animation, struct Eye *eye, int8_t targetX, int8_t targetY) {
  animation->frame = 0;
  animation->finished = false;
  animation->eye = eye;
  animation->targetX = eye->x1 + (eye->x2 - eye->x1) / 2 + targetX;
  animation->targetY = eye->y1 + (eye->y2 - eye->y1) / 2 + targetY;
  animation->startX = eye->pupilX;
  animation->startY = eye->pupilY;
}

void shiftAnimationFrame(struct ShiftAnimation *animation) {
  if (animation->finished) return;
  animation->frame++;
  float progress = (float)animation->frame / 4.0;
  uint8_t newX, newY;
  if (progress < 1.0) {
    newX = (float)animation->targetX * progress + (float)animation->startX * (1.0-progress);
    newY = (float)animation->targetY * progress + (float)animation->startY * (1.0-progress);
  } else {
    newX = animation->targetX;
    newY = animation->targetY;
    animation->finished = true;
  }
  st7789_MoveFilledCircle(animation->eye->pupilX, newX, animation->eye->pupilY, newY, PUPIL_RADIUS, EYE_COLOR, PUPIL_COLOR);
  animation->eye->pupilX = newX;
  animation->eye->pupilY = newY;
}

void blinkAnimationInit(struct BlinkAnimation *animation, struct Eye *eye, bool closeOnly) {
  animation->frame = 1;
  animation->finished = false;
  animation->eye = eye;
  animation->direction = true;
  animation->closeOnly = closeOnly;
}

void blinkAnimationFrame(struct BlinkAnimation *animation) {
  if (animation->finished) return;
  struct Eye *eye = animation->eye;
  uint8_t nextFrame = animation->frame*2;
  if (animation->direction) {
    for (uint8_t y = animation->frame - 1; y < nextFrame; y++) {
      st7789_HLine(eye->x1, eye->x2, eye->y1 + y, 0);
      if (y >= (eye->y2 - eye->y1)) {
        animation->direction = false;
        nextFrame = 1;
        if (animation->closeOnly)
          animation->finished = true;
        break;
      }
    }
  } else {
    for (uint8_t y = animation->frame - 1; y < nextFrame; y++) {
      st7789_HLine(eye->x1, eye->x2, eye->y2 - y, EYE_COLOR);
      if (y >= (eye->y2 - eye->y1)) {
        animation->finished = true;
        break;
      }
    }
    uint8_t start = eye->y2-animation->frame;
    if (start-animation->frame <= eye->pupilY + PUPIL_RADIUS && start >= eye->pupilY - PUPIL_RADIUS)
      eyePupilDraw(eye, PUPIL_COLOR);
  }
  animation->frame=nextFrame;
}

void freakAnimationInit(struct Eye *eye) {
  st7789_FillRect(eye->x1, eye->x2, eye->y1, eye->y2, 0);
  eyePupilDraw(eye, 0xF800);
}

void freakAnimationFrame(struct Eye *eye) {
  uint8_t newX = eye->x1 + (eye->x2 - eye->x1)/2 + xorshift8_int(5);
  uint8_t newY = eye->y1 + (eye->y2 - eye->y1)/2 + xorshift8_int(5);
  st7789_MoveFilledCircle(eye->pupilX, newX, eye->pupilY, newY, PUPIL_RADIUS, 0, 0xF800);
  eye->pupilX = newX;
  eye->pupilY = newY;
}