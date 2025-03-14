#pragma once

#include <stdint.h>
#include <stdbool.h>

#define PUPIL_RADIUS 26
#define EYE_COLOR 0xAFFF
// #define PUPIL_COLOR 0x000F
#define PUPIL_COLOR 0x0000

struct Eye {
  uint8_t x1, x2, y1, y2;
  uint8_t pupilX, pupilY;
};

struct ShiftAnimation {
  struct Eye *eye;
  uint8_t startX, startY, targetX, targetY, frame;
  bool finished;
};

struct BlinkAnimation {
  struct Eye *eye;
  uint8_t frame;
  bool direction, finished, closeOnly;
};

void eyeInit(struct Eye *eye, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
void eyeDraw(struct Eye *eye);
void eyeDrawColor(struct Eye *eye, uint16_t color);
void eyePupilDraw(struct Eye *eye, uint16_t color);

void shiftAnimationInit(struct ShiftAnimation *animation, struct Eye *eye, int8_t targetX, int8_t targetY);
void shiftAnimationFrame(struct ShiftAnimation *animation);

void blinkAnimationInit(struct BlinkAnimation *animation, struct Eye *eye, bool closeOnly);
void blinkAnimationFrame(struct BlinkAnimation *animation);

void freakAnimationInit(struct Eye *eye);
void freakAnimationFrame(struct Eye *eye);