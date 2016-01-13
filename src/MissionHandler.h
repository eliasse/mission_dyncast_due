#ifndef _MISSION_HANDLER_
#define _MISSION_HANDLER_

#include "MissionItem.h"
//#include "LedBlink.h"
#include <Arduino.h>
#include <vector>

extern int op_mode;

/* Class that actually controls the mission */
class MissionHandler {
 public:
  std::vector<MissionItem*> Mission;
  std::vector<MissionItem*>::iterator Current;

  MissionHandler();
  int Begin();
  int Stop();
  void Loop();
  void EraseMission();
  void ResetMission();
  void PrintMission();
  void Swap(int a, int b);
};

#endif
