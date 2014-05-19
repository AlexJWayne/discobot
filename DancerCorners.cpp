#include "DancerCorners.h"

void DancerCorners::start() {
  color = CHSV(random(0xFF), 0xFF, 0xFF);
  step = 0;

  FL1->tween(30, .2);
  BL1->tween(30, .2);
  FR1->tween(30, .2);
  BR1->tween(30, .2);
  FL2->tween(25, .2);
  BL2->tween(25, .2);
  FR2->tween(25, .2);
  BR2->tween(25, .2);
}

void DancerCorners::onBeatStart(float duration) {
  color.v = 0xFF;
  
  duration *= 0.75;

  switch(step) {
    case 0:
      FL2->tween(60, duration, Joint::EaseOut);
      BL2->tween(60, duration, Joint::EaseOut);
      break;
    case 1:
      FR2->tween(60, duration, Joint::EaseOut);
      BR2->tween(60, duration, Joint::EaseOut);
      break;
    case 2:
      FL2->tween(25, duration, Joint::EaseOut);
      BL2->tween(25, duration, Joint::EaseOut);
      break;
    case 3:
      FR2->tween(25, duration, Joint::EaseOut);
      BR2->tween(25, duration, Joint::EaseOut);
      break;
  }

  step++;
  if (step >= 4) step = 0;
}

void DancerCorners::update() {
  color.hue++;

  if (color.v > 4) {
    color.v -= 4;
  } else {
    color.v = 0;
  }

  CHSV pxColor;


  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 5; y++) {
      pxColor = color;
      if (step % 2 == 0) {
        pxColor.v = scale8(color.v, y * 255/5);
      } else {
        pxColor.v = scale8(color.v, 255 - y * 255/5);
      }
      neoPixels[x + y*8] = pxColor;
    }
  }

  FastLED.show();
}