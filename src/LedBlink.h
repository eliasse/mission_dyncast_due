#ifndef _LEDBLINK_
#define _LEDBLINK_

#include "MissionItem.h"
#include "Enums.h"

#include <Arduino.h>

class LedBlink : public MissionItem {
public:
  uint8_t Pin, Brightness;
  unsigned long duration;
  LedBlink(long args[]);    // Constructor
  void Cloops();            // Activating controlloops
  void Start();             // Function called when maneuver starts
  int  Progress();          // Check progress (return true if done?)
  void onCompletion();      // Function called when maneuver finished
  void PrintItem();         // Function called when mission is printed
  ~LedBlink();
};

#endif
