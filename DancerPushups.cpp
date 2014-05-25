#include "DancerPushups.h"

DancerPushups::DancerPushups() {
  hDirection = 1;
  vDirection = 1;

  color.hue = random8();
  color.s = 0xFF;
  color.v = 0xFF;
}

void DancerPushups::onBeatStart(float duration) {
  hDirection *= -1;

  FL1->tween(45 + 25 * hDirection, duration);
  FR1->tween(45 - 25 * hDirection, duration);
  BL1->tween(45 - 25 * hDirection, duration);
  BR1->tween(45 + 25 * hDirection, duration);
}

void DancerPushups::onBarStart(float duration) {
  float angle;
  color.hue += 0x10;
  vDirection *= -1;

  startMs = millis();
  endMs   = startMs + duration * 1000;

  if (vDirection == 1) {
    angle = 30;
  } else {
    angle = 60;
  }

  FL2->tween(angle, duration);
  FR2->tween(angle, duration);
  BL2->tween(angle, duration);
  BR2->tween(angle, duration);
}

void DancerPushups::update() {
  long now = constrain(millis(), startMs, endMs);
  CHSV onColor, offColor;

  color.v = map(now, startMs, endMs, 0, 0xFF);

  onColor = color;

  if (vDirection == 1) {
    onColor.v = 0xFF - onColor.v;
  }

  offColor = onColor;
  offColor.v = 0xFF - onColor.v;

  onColor.v = dim8_raw(onColor.v);
  offColor.v = dim8_raw(offColor.v);

  for (uint8_t y = 0; y < 5; y++) {
    for (uint8_t x = 0; x < 8; x++) {
      if (y == 2 && x > 2 && x < 5) {
        neoPixels[x + y*8] = offColor;
      } else {
        neoPixels[x + y*8] = onColor;
      }
    }
  }


  FastLED.show();
}