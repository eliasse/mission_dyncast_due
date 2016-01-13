#include "MissionHandler.h"
#include <vector>
#include <algorithm>

MissionHandler::MissionHandler()
{
  //std::vector<MissionItem*> Mission;
  //std::vector<MissionItem*>::iterator Current;

  // Initiera vektorn/listan först
  Current = Mission.begin();
}

void MissionHandler::ResetMission()
{
  Current = Mission.begin();
}

void MissionHandler::Swap(int a, int b)
{
  //std::iter_swap(Mission.begin() + a, Mission.begin() + b);
  Serial.print("Trying to Swap A: "); Serial.print(a); Serial.print(" and B: ");
  Serial.println(b);
  std::iter_swap(Mission.begin() + a, Mission.begin() + b);
}

int MissionHandler::Begin()
{
  if (op_mode == MANEUVER) {
    Serial.println("Already running");
    delay(2000);
    return 1;
  }
  else if (op_mode != SERVICE) {
    Serial.println("Not in Service mode");
    delay(2000);
    return 2;
  }

  if (Mission.empty())
    {
      Serial.println("Mission is empty");
      delay(2000);
      return 3;
    }

  if ( Current == Mission.end() ) {
    Serial.println("Current == Mission.end()");
    delay(1000);
    return 4;
  }

  (*Current)->Start();
  op_mode = MANEUVER;
  Serial.println("Mode -> Maneuver");
  return 0;
}

void MissionHandler::Loop() {

  if (op_mode != MANEUVER) {
    Serial.println("Not in Maneuver mode");
    delay(2000);
    return;
  }

  if ((*Current)->Progress())
    {
      // delete *Mission.begin();        // Release memory
      // Mission.erase(Mission.begin()); // Delete vector item
      Current++;

    if (Current != Mission.end())
      {
	       (*Current)->Start();
      }
    else {
      Serial.println("Mission Complete");
      op_mode = SERVICE;
    }
  }
}

void MissionHandler::EraseMission()
{
        std::vector<MissionItem*>::iterator it = Mission.begin();

        while (it != Mission.end()) {delete *it++; } // Destroys derived object

        Mission.clear(); // Destroys base object

        Current = Mission.begin();
}

void MissionHandler::PrintMission()
{
  std::vector<MissionItem*>::iterator it = Mission.begin();

  if (Mission.empty())
  {
    Serial.println("Mission is Empty");
  }

  while (it != Mission.end()) {
    Serial.print(it-Mission.begin());
    Serial.print(": ");
    (*it++)->PrintItem();
  }
}
