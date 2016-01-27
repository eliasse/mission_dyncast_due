#ifndef _MISSION_HANDLER_
#define _MISSION_HANDLER_

#include "MissionItem.h"
#include "Command.h"
#include <Arduino.h>
#include <vector>

extern int op_mode;

/* Class that actually controls the mission */
class MissionHandler {
 public:
  static std::vector<MissionItem*> Mission;
  static std::vector<MissionItem*>::iterator Current;

  MissionHandler();
  void Loop();
  static int Begin(int argc, CommandParser::arg argv[]);
  static int Stop(int argc, CommandParser::arg argv[]);
  static int ClearMission(int argc, CommandParser::arg argv[]);
  static int ResetMission(int argc, CommandParser::arg argv[]);
  static int PrintMission(int argc, CommandParser::arg argv[]);
  static int Swap(int argc, CommandParser::arg argv[]);
  static int Erase(int argc, CommandParser::arg argv[]);
  static void MultiErase(int a, int b);
  static int SetCurrent(int argc, CommandParser::arg argv[]);
};

#endif
