#pragma once

#define LED_PIN 34
#define DC_PIN 14
#define RST_PIN 16
#define DATA_PIN 15
#define CLOCK_PIN 17

#include <stdint.h>

void st7789_init();
void st7789_HLine(uint8_t x1, uint8_t x2, uint8_t y, uint16_t color);
void st7789_FillRect(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2, uint16_t color);
void st7789_FillCircle(uint8_t x, uint8_t y, uint8_t r, uint16_t color);
void st7789_MoveFilledCircle(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2, uint8_t r, uint16_t backgroundColor, uint16_t circleColor);