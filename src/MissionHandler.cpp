#include "MissionHandler.h"
#include <vector>
#include <algorithm>

MissionHandler::MissionHandler()
{
  //std::vector<MissionItem*> Mission;
  //std::vector<MissionItem*>::iterator Current;

  /* Make sure Current is pointing at something... Note it's not the same thing
   as starting the mission (Just making sure Current is pointing at beginning
   of vector). */
  Current = Mission.begin();
}

void MissionHandler::ResetMission()
{
  if (op_mode != MANEUVER) Current = Mission.begin();
  else Serial.println("Cannot reset during maneuver");
}

void MissionHandler::Swap(int a, int b)
{
  // std::iter_swap(Mission.begin() + a, Mission.begin() + b);
  Serial.print("Swapping A: ");
  Serial.print(a);
  Serial.print(" and B: ");
  Serial.println(b);
  std::iter_swap(Mission.begin() + a, Mission.begin() + b);
}

void MissionHandler::Erase(int args[])
{
  // Making sure Current doesn't end up pointing at Null
  // if (Current != Mission.begin()) Current--;

  // Let's see it it's a sequence of items that are to be removed
  if (args[1] != 0) {
    MultiErase(args[0], args[1]);
    return;
  }

  std::vector<MissionItem *>::iterator it = Mission.begin() + args[0];
  delete *it;

  Mission.erase(Mission.begin() + args[0]);
}

void MissionHandler::MultiErase(int a, int b)
{
  std::vector<MissionItem *>::iterator first = Mission.begin() + a;
  std::vector<MissionItem *>::iterator last  = Mission.begin() + b;

  bool correctCurrent = false;

  // Check if the Current item is in the sequence of those being deleted
  if ((Current - Mission.begin() > first - Mission.begin()) &&
      (Current - Mission.begin() < last  - Mission.begin()))
  {
    // Lets temporarily make Current point att something that won't disappear
    Current = first - 1;
    correctCurrent = true;
  }

  while (std::distance(first, last) >= 0) delete *first++;

  // Lets put Current to point att item originally after "last"
  if (correctCurrent) Current++;
}


void MissionHandler::SetCurrent(int a)
{
  if (a < 0) {
    Serial.print("Must be a positive number");
    return;
  }
  if (a > (Mission.end() - Mission.begin()) - 1) {
    Serial.print("Chosen item number not in reach");
  }

  Current = Mission.begin() + a;
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
    //Serial.println("Not in Maneuver mode");
    //delay(2000);
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

void MissionHandler::ClearMission()
{
  std::vector<MissionItem *>::iterator it = Mission.begin();

  while (it != Mission.end()) delete *it++;  // Destroys derived object

  Mission.clear();                           // Destroys base object

  Current = Mission.begin();
}

void MissionHandler::PrintMission()
{
  std::vector<MissionItem *>::iterator it = Mission.begin();

  if (Mission.empty())
  {
    Serial.println("Mission is Empty");
    return;
  }

  Serial.print("Current: "); Serial.println(Current - Mission.begin());

  while (it != Mission.end()) {
    Serial.print(it - Mission.begin());
    Serial.print(": ");
    (*it++)->PrintItem();

    if ((int)(Current - Mission.begin()) + 1 == (int)(it - Mission.begin())) {
      Serial.print(" (Current)");
    }
    Serial.println();
  }
}
