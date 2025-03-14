#include "st7789.h"
#include <Arduino.h>

#include "defines.h"

#define SPI_transfer(data) SPI0_DATA = data; while (S0_FREE == 0)
#define SPI_writeByte(data) while (S0_FREE == 0); SPI0_DATA = data
#define SPI_finishByte() while(S0_FREE == 0)

#define MAX_CIRCLE_RADIUS 32

uint8_t circleSize = -1;
uint8_t circleBuffer[MAX_CIRCLE_RADIUS];

volatile uint16_t waitCounter = 0;

static void writeNBytes(uint16_t n, uint16_t color) {
  for(uint16_t i=0; i<n; i++) {
    SPI_writeByte(color >> 8);
    SPI_writeByte(color);
  }
  SPI_finishByte();
}

inline void setParam(uint8_t command, uint8_t data) {
  SPI_transfer(command);
  digitalWrite(DC_PIN, HIGH);
  SPI_transfer(data);
  digitalWrite(DC_PIN, LOW);
}

void st7789_init() {
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, LOW);
  delay(25);
  pinMode(DC_PIN, OUTPUT);
  digitalWrite(DC_PIN, LOW);
  digitalWrite(RST_PIN, HIGH);
  delay(250);

  SPI0_CTRL = bS0_MOSI_OE | bS0_SCK_OE;
  SPI0_CK_SE = F_CPU / 6000000;

  SPI_transfer(ST7789_CMD_INVON);
  SPI_transfer(ST7789_CMD_SLPOUT);
  delay(500);

  setParam(ST7789_CMD_MADCTL, ST7789_BASIC_DEFAULT_ACCESS);
  setParam(ST7789_CMD_COLMOD, (ST7789_BASIC_DEFAULT_RGB_INTERFACE_COLOR_FORMAT << 4) | (ST7789_BASIC_DEFAULT_CONTROL_INTERFACE_COLOR_FORMAT << 0));
  SPI_transfer(ST7789_CMD_DISPON);
}

static void setDrawingArea(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2) {
  SPI_transfer(ST7789_CMD_CASET);
  digitalWrite(DC_PIN, HIGH);
  SPI_writeByte(0x00);
  SPI_writeByte(x1);
  SPI_writeByte(0x00);
  SPI_writeByte(x2);
  SPI_finishByte();
  digitalWrite(DC_PIN, LOW);

  SPI_transfer(ST7789_CMD_RASET);
  digitalWrite(DC_PIN, HIGH);
  SPI_writeByte(0x00);
  SPI_writeByte(y1);
  SPI_writeByte(0x00);
  SPI_writeByte(y2);
  SPI_finishByte();
  digitalWrite(DC_PIN, LOW);
}

void st7789_HLine(uint8_t x1, uint8_t x2, uint8_t y, uint16_t color) {
  setDrawingArea(x1, x2, y, y);
  
  SPI_transfer(ST7789_CMD_RAMWR);
  digitalWrite(DC_PIN, HIGH);
  
  writeNBytes(x2 - x1 + 1, color);

  digitalWrite(DC_PIN, LOW);
}

void st7789_FillRect(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2, uint16_t color) {
  setDrawingArea(x1, x2, y1, y2);

  SPI_transfer(ST7789_CMD_RAMWR);
  digitalWrite(DC_PIN, HIGH);

  uint16_t area = (x2 - x1 + 1) * (y2 - y1 + 1);
  writeNBytes(area, color);

  digitalWrite(DC_PIN, LOW);
}

static void fillCircleBuffer(uint8_t r) {
  if (circleSize != r) {
    uint8_t t1 = r/16;
    uint8_t cx = r;
    uint8_t cy = 0;
    while(cx >= cy) {
      circleBuffer[cy] = cx;
      cy++;
      t1 += cy;
      if (cx > t1) {
        t1 -= cx;
        cx--;
        circleBuffer[cx] = cy;
      }
    }
  }
}

void st7789_FillCircle(uint8_t x, uint8_t y, uint8_t r, uint16_t color) {
  if (r > MAX_CIRCLE_RADIUS) return;
  fillCircleBuffer(r);
  for (uint8_t l=0; l<r; l++) {
    st7789_HLine(x-circleBuffer[l], x+circleBuffer[l], y-l, color);
    if (l > 0)
      st7789_HLine(x-circleBuffer[l], x+circleBuffer[l], y+l, color);
  }
}

inline uint8_t getCircleLineW(uint8_t ys, uint8_t y, uint8_t r) {
  uint8_t d = ys > y ? ys - y : y - ys;
  return d < r ? circleBuffer[d] : 0;
}

void st7789_MoveFilledCircle(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2, uint8_t r, uint16_t backgroundColor, uint16_t circleColor) {
  if (r > MAX_CIRCLE_RADIUS) return;
  fillCircleBuffer(r);
  for (uint8_t y=(y1 < y2 ? y1 - r : y2 - r); y<240; y++) {
    uint8_t w1 = getCircleLineW(y1, y, r);
    uint8_t w2 = getCircleLineW(y2, y, r);
    uint8_t x1s = x1 - w1;
    uint8_t x1e = x1 + w1;
    uint8_t x2s = x2 - w2;
    uint8_t x2e = x2 + w2;
    if (w1 && w2 && x1s <= x2e && x2s <= x1e) {
      if (x1s < x2s) st7789_HLine(x1s, x2s - 1, y, backgroundColor);
      if (x1e > x2e) st7789_HLine(x2e+1, x1e, y, backgroundColor);
    } else if (w1)
      st7789_HLine(x1s, x1e, y, backgroundColor);
    if (w2)
      st7789_HLine(x2s, x2e, y, circleColor);
  }
}