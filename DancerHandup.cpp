#include "DancerHandup.h"

void DancerHandup::start() {
  bounceUp  = false;
  handUp    = false;
  handRight = true;
  beatCount = 0;
  barCount  = 0;
  hue       = random8();

  switch (random(0, 4)) {
    case 0:
      hand1 = FL1; break;
    case 1:
      hand1 = FR1; break;
    case 2:
      hand1 = BL1; break;
    case 3:
      hand1 = BR1; break;
  }

  setup();
}

void DancerHandup::update() {
  CHSV pxColor;
  int targX = 7;
  int targY = 4;

  long now = millis();
  now = constrain(now, msAtBeatStart, msAtBeatEnd);
  uint8_t completion8 = map(now, msAtBeatStart, msAtBeatEnd, 0, 0xFF);
  if (bounceUp) completion8 = 0xFF - completion8;

  if (hand1 == FR1 || hand1 == FL1) targX = 0;
  if (hand1 == FR1 || hand1 == BR1) targY = 0;

  for (uint8_t y = 0; y < 5; y++) {
    for (uint8_t x = 0; x < 8; x++) {
      uint8_t x2 = abs(targX - x);
      uint8_t y2 = abs(targY - y);

      pxColor.s = 0xFF;
      pxColor.v = dim8_raw(constrain(0xFF/6 * y2, 0, 0xFF));
      pxColor.v = qadd8(pxColor.v, dim8_raw(constrain(0xFF/6 * x2, 0, 0xFF)));
      pxColor.v = dim8_raw(pxColor.v);
      pxColor.v = scale8(pxColor.v, completion8);
      pxColor.h = hue + scale8(pxColor.v, 0x80);

      neoPixels[x + y*8] = pxColor;
    }
  }

  FastLED.show();
}

void DancerHandup::onBeatStart(float duration) {
  beatCount++;
  bounceUp = !bounceUp;
  msAtBeatStart = millis();
  msAtBeatEnd = msAtBeatStart + duration * 1000;
  hue += 0x10;

  float dir = bounceUp ? 1 : 0;

  back2->tween(      5 + 10 * dir, duration, bounceUp ? Joint::EaseOut : Joint::EaseIn);
  sideLong2->tween( 55 + 20 * dir, duration, bounceUp ? Joint::EaseOut : Joint::EaseIn);
  sideShort2->tween(55 + 20 * dir, duration, bounceUp ? Joint::EaseOut : Joint::EaseIn);

  back1->tween(     45, duration);
  sideLong1->tween( 65, duration);
  sideShort1->tween(25, duration);

  float angle;
  if (beatCount % 2 == 0) {
    handRight = !handRight;
    angle = handRight ? -10 : 60;
    hand1->tween(angle, duration * 2.0);
  } else {
    handUp = !handUp;
    angle = handUp ? -80 : 0;
    hand2->tween(angle, duration * 2.0, handUp ? Joint::EaseIn : Joint::EaseOut);
  }
}

void DancerHandup::onBarStart(float duration) {
  barCount++;

  if (barCount % 5 == 0) {
    setup();
  }
}

void DancerHandup::setup() {
  if (hand1 == BL1) {
    back1       = BR1;
    back2       = BR2;
    sideLong1   = BL1;
    sideLong2   = BL2;
    sideShort1  = FR1;
    sideShort2  = FR2;
    hand1       = FL1;
    hand2       = FL2;
  } else if (hand1 == FL1) {
    back1 = BL1;
    back2 = BL2;
    sideLong1 = BR1;
    sideLong2 = BR2;
    sideShort1 = FL1;
    sideShort2 = FL2;
    hand1 = FR1;
    hand2 = FR2;
  } else if (hand1 == FR1) {
    back1 = FL1;
    back2 = FL2;
    sideLong1 = FR1;
    sideLong2 = FR2;
    sideShort1 = BL1;
    sideShort2 = BL2;
    hand1 = BR1;
    hand2 = BR2;
  } else {
    back1 = FR1;
    back2 = FR2;
    sideLong1 = FL1;
    sideLong2 = FL2;
    sideShort1 = BR1;
    sideShort2 = BR2;
    hand1 = BL1;
    hand2 = BL2;
  }
}