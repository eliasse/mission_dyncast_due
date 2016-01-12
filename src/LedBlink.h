#ifndef _LEDBLINK_
#define _LEDBLINK_

#include "MissionItem.h"
#include "Enums.h"

#include <Arduino.h>

class LedBlink : public MissionItem {
public:
  uint8_t Pin, Brightness;
  unsigned long duration, start;
  LedBlink(unsigned long args[]);    // Constructor
  void Cloops();             // Controlloops
  void Start();
  int  Progress();            // Check progress (return true if done?)
  void onCompletion();
  void PrintItem();
  ~LedBlink();
};

#endif
