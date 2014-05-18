#ifndef DancerCorners_H
#define DancerCorners_H
#include "Dancer.h"

class DancerCorners : public Dancer {
  public:
    int step;

    void start();
    void onBeatStart(float duration);
    void onBarStart(float duration);
};

#endif