#include <TouchKey.h>
#include <Serial.h>
#include "st7789.h"
#include "eye.h"
#include "gem.h"
#include "src/xorshiftrng/xorshift_rng.h"

struct Eye leftEye;
struct Eye rightEye;
struct GemImage image;

uint32_t frameStart = 0;
uint32_t lastBlink = 0;
uint32_t lastGazeChange = 0;
bool directLooking = true;

#define SAO_ACTION_PIN 33
#define TOUCH_PIN 11
#define FRAMETIME 15UL
#define SHIFTCHANCE 85

enum ACTION {
  ACTION_NONE,
  ACTION_BLINK,
  ACTION_CHANGE,
  ACTION_SHIFT,
  ACTION_WINK,
  ACTION_DIRECTLOOK,
  ACTION_BLINKSHIFT
};

static void waitForNextFrame() {
  while(millis() - frameStart < FRAMETIME) ;
  frameStart = millis();
}

static void blink(bool closeOnly, bool oneEye) {
  struct BlinkAnimation rightEyeBlink;
  struct BlinkAnimation leftEyeBlink;
  blinkAnimationInit(&leftEyeBlink, &leftEye, closeOnly);
  blinkAnimationInit(&rightEyeBlink, &rightEye, closeOnly);
  if (oneEye) rightEyeBlink.finished = true;
  while(!leftEyeBlink.finished) {
    blinkAnimationFrame(&leftEyeBlink);
    blinkAnimationFrame(&rightEyeBlink);
    waitForNextFrame();
  }
}

static void moveEyesTo(int8_t x, int8_t y) {
  struct ShiftAnimation rightEyeMove;
  struct ShiftAnimation leftEyeMove;
  shiftAnimationInit(&leftEyeMove, &leftEye, x, y);
  shiftAnimationInit(&rightEyeMove, &rightEye, x, y);
  while(!leftEyeMove.finished) {
    shiftAnimationFrame(&leftEyeMove);
    shiftAnimationFrame(&rightEyeMove);
    waitForNextFrame();
  }
}

static void freakOut() {
  freakAnimationInit(&leftEye);
  freakAnimationInit(&rightEye);
  struct GemAnimation gem;
  while(!digitalRead(SAO_ACTION_PIN)) {
    gemAnimationFrame(&gem);
    freakAnimationFrame(&leftEye);
    freakAnimationFrame(&rightEye);
  }
  displayGemImage(&image);
  blink(false, false);
}

static void seedXorshift() {
  delay(200); //wait for voltages to stabilize
  uint8_t random = 0;
  for (uint8_t i=0; i<8; i++) {
    random<<=1;
    random+=(analogRead(TOUCH_PIN) & 1);
    delay(1);
  }
  xorshift8_seed(random);
}

static void initGemImage() {
  image.r = eeprom_read_byte(0);
  image.b = eeprom_read_byte(1);
  if (image.r == 0xFF && image.b == 0xFF) {
    randomGemImage(&image);
    eeprom_write_byte(0, image.r);
    eeprom_write_byte(1, image.b);
  }
  displayGemImage(&image);
}

void setup() {
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(SAO_ACTION_PIN, INPUT_PULLUP);
  pinMode(TOUCH_PIN, INPUT);

  seedXorshift();

  TouchKey_begin(1 << 1);
  st7789_init();
  st7789_FillRect(0,240,0,240, 0);

  initGemImage();
  eyeInit(&leftEye, 12, 114, 136, 236);
  eyeInit(&rightEye, 134, 236, 136, 236);
  frameStart = millis();
  digitalWrite(LED_PIN, HIGH);

  blink(false, false);
  blink(false, false);
}

static enum ACTION pickAction() {
  uint8_t blinkChance = (millis() - lastBlink) / 150UL;
  uint8_t changeChance = (millis() - lastGazeChange) / 250UL;
  uint8_t random = xorshift8();
  if (random < blinkChance) {
    lastBlink = millis();
    return ACTION_BLINK;
  } else if (random - blinkChance < changeChance) {
    lastGazeChange = millis();
    return ACTION_CHANGE;
  } else if (random - blinkChance - changeChance < SHIFTCHANCE) {
    if (!directLooking) return ACTION_NONE;
    return ACTION_SHIFT;
  } else if (random - blinkChance - changeChance - SHIFTCHANCE == 0 && directLooking) {
    return ACTION_WINK;
  }
  return ACTION_NONE;
}

void loop() {
  uint32_t loopStart = millis();
  switch(pickAction()) {
    case ACTION_BLINK: {
      blink(false, false);
    } break;
    case ACTION_CHANGE: {
      directLooking = !directLooking;
      if (directLooking)
        moveEyesTo(xorshift8_int(4), xorshift8_int(4));
      else
        moveEyesTo(0, 0);
    } break;
    case ACTION_SHIFT:
      moveEyesTo(xorshift8_int(4), xorshift8_int(4));
    break;
    case ACTION_WINK: {
      blink(false, true);
    } break;
  }
  while(millis() - loopStart < 333UL) {
    TouchKey_Process();
    if (TouchKey_Get()) {
      blink(true, false);
      while(TouchKey_Get()) {
        delay(10);
        TouchKey_Process();
      }
      blink(false, false);
    }
    if (!digitalRead(SAO_ACTION_PIN)) {
      freakOut();
    }
  }
}
