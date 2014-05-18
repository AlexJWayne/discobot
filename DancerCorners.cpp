#include "DancerCorners.h"

void DancerCorners::start() {
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

void DancerCorners::onBarStart(float duration) {
  // step = 0; 
}