#include "FastLED.h"

#include "Wire.h"
#include "Servo.h"
#include "Adafruit_PWMServoDriver.h"

#include "Switch.h"

#include "Metronome.h"
#include "ReadSerialFloat.h"
#include "Joint.h"

#include "Dancer.h"
#include "DancerPushups.h"
#include "DancerHandup.h"
#include "DancerThrusts.h"
#include "DancerCorners.h"



const int onBoardLedPin = 13;
const int bpmPotPin = 2;
const int inputSwitchPin = 44;

int inputMode = 0;
Switch inputModeSwitch = Switch(inputSwitchPin);

const int neoPixelPin = 40;
const int neoPixelBrightness = 0x20;
const int neoPixelCount = 40;
CRGB neoPixels[neoPixelCount];

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

float currentTime;

Joint FL1;
Joint FL2;
Joint FR1;
Joint FR2;
Joint BR1;
Joint BR2;
Joint BL1;
Joint BL2;

Metronome metronome;

Dancer *currentDancer;

const int dancerCount = 4;
Dancer *dancers[] = {
  new DancerPushups(),
  new DancerHandup(),
  new DancerThrusts(),
  new DancerCorners()
};

void setup() {
  // Get serial going and make it go as fast as it can.
  Serial.begin(115200);

  // Get some noise to seed the random number generator with.
  randomSeed(analogRead(4) * analogRead(5) * analogRead(6) * analogRead(7));

  // Initialize the PWM driver board that all servos are connected to.
  pwmDriver.begin();
  pwmDriver.setPWMFreq(60);

  // Initialize the NeoPixel matrix.
  FastLED.addLeds<NEOPIXEL, neoPixelPin, GRB>(neoPixels, neoPixelCount);
  FastLED.setBrightness(neoPixelBrightness);
  FastLED.show();

  // Set the onboard LED to output mode.
  pinMode(onBoardLedPin, OUTPUT);

  // Initialize all the joints.
  FL1.init(pwmDriver, 0,  10,  1, 30);
  FL2.init(pwmDriver, 1,   6, -1, 80);
  FR1.init(pwmDriver, 2, -10, -1, 30);
  FR2.init(pwmDriver, 3,  17,  1, 80);
  BR1.init(pwmDriver, 4,   7,  1, 30);
  BR2.init(pwmDriver, 5, -10, -1, 80);
  BL1.init(pwmDriver, 6,   3, -1, 30);
  BL2.init(pwmDriver, 7,  -4,  1, 80);

  // Initializers all the dancers, giving them all a reference to each joint.
  for (int i = 0; i < dancerCount; i++) {
    dancers[i]->init(neoPixels, FL1, FL2, FR1, FR2, BR1, BR2, BL1, BL2);
  }

  // Set the first dancer randomly.
  currentDancer = dancers[random(0, dancerCount)];
  currentDancer->start();

  // start ticking the internal metronome at 90 bpm.
  metronome.start(90);
}

void loop() {
  currentTime = (float)millis() / 1000.0;

  changeInputMode();

  updateJoints();
}

void changeInputMode() {
  inputModeSwitch.poll();
  if (inputModeSwitch.pushed()) {
    if (inputMode == 0) {
      inputMode = 1;

    } else {
      inputMode = 0;
      FastLED.showColor(CRGB::Black);

      FL1.tween(FL1.initialAngle, 0.25);
      FR1.tween(FR1.initialAngle, 0.25);
      BL1.tween(BL1.initialAngle, 0.25);
      BR1.tween(BR1.initialAngle, 0.25);
      FL2.tween(FL2.initialAngle, 0.25);
      FR2.tween(FR2.initialAngle, 0.25);
      BL2.tween(BL2.initialAngle, 0.25);
      BR2.tween(BR2.initialAngle, 0.25);
    }
  }

  digitalWrite(onBoardLedPin, inputMode == 0 ? LOW : HIGH);
}

void updateJoints() {
  switch (inputMode) {
    case 0:
      updateSerial(); break;
    case 1:
      updateMetronome(); break;
  }

  currentDancer->update();

  FL1.update(currentTime);
  FR1.update(currentTime);
  BL1.update(currentTime);
  BR1.update(currentTime);
  FL2.update(currentTime);
  FR2.update(currentTime);
  BL2.update(currentTime);
  BR2.update(currentTime);
}

void updateSerial() {
  while (Serial.available() > 0) {
    float duration;
    // segment
    readSerialFloat();

    // tatum
    readSerialFloat();
    
    // beat
    duration = readSerialFloat();
    if (duration > 0) {
      currentDancer->onBeatStart(duration);
    }

    // bar
    duration = readSerialFloat();
    if (duration > 0) {
      currentDancer->onBarStart(duration);
    }

    // section
    duration = readSerialFloat();
    if (duration > 0) {
      switchDancer();
    }
  }
}

void updateMetronome() {

  // Set BPM to pot value
  float bpmScalar = (float)analogRead(bpmPotPin) / 1023;
  metronome.setBPM(60.0 + 180.0 * bpmScalar);

  // update the metronome timer
  metronome.update();

  // Update dancers

  if (metronome.triggerSection()) {
    switchDancer();
  }

  if (metronome.triggerBeat()) {
    // Serial.println("beat ");
    currentDancer->onBeatStart(metronome.spb);
  }

  if (metronome.triggerBar()) {
    // Serial.println("bar ");
    currentDancer->onBarStart(metronome.spb * 4.0);
  }
}

void switchDancer() {
  int newIdx = random(0, dancerCount-1);

  for (int i = 0; i < newIdx; i++) {
    if (dancers[i] == currentDancer) {
      newIdx++;
      break;
    }
  }

  currentDancer = dancers[newIdx];
  currentDancer->start();
}