#ifndef DancerPushups_H
#define DancerPushups_H
#include "Dancer.h"
#include "FastLED.h"

class DancerPushups : public Dancer {
  public:
    DancerPushups();

    int hDirection;
    int vDirection;

    long startMs;
    long endMs;
    CHSV color;

    void onBeatStart(float duration);
    void onBarStart(float duration);
    void update();
};

#endif