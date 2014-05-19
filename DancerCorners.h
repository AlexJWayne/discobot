#ifndef DancerCorners_H
#define DancerCorners_H
#include "Dancer.h"

class DancerCorners : public Dancer {
  public:
    int step;

    CHSV color;

    void start();
    void update();
    void onBeatStart(float duration);
};

#endif