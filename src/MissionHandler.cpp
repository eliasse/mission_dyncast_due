#include "MissionHandler.h"
#include <vector>
#include <algorithm>

std::vector<MissionItem*> MissionHandler::Mission;
std::vector<MissionItem*>::iterator MissionHandler::Current;

MissionHandler::MissionHandler()
{
  //std::vector<MissionItem*> Mission;
  //std::vector<MissionItem*>::iterator Current;

  /* Make sure Current is pointing at something... Note it's not the same thing
   as starting the mission (Just making sure Current is pointing at beginning
   of vector). */
  Current = Mission.begin();
}

int MissionHandler::ResetMission(int argc, CommandParser::arg argv[])
{
  if (op_mode != MANEUVER) Current = Mission.begin();
  else Serial.println("Cannot reset during maneuver");
}

int MissionHandler::Swap(int argc, CommandParser::arg argv[])
{
  Serial.print("Swapping A: ");
  Serial.print(argv[1].i);
  Serial.print(" and B: ");
  Serial.println(argv[2].i);
  std::iter_swap(Mission.begin() + argv[1].i, Mission.begin() + argv[2].i);
}

int MissionHandler::Erase(int argc, CommandParser::arg argv[])
{
  // Making sure Current doesn't end up pointing at Null
  // if (Current != Mission.begin()) Current--;

  // Let's see it it's a sequence of items that are to be removed
  if (argc == 3) {
    MultiErase(argv[1].i, argv[2].i);
    return 0;
  }

  std::vector<MissionItem *>::iterator it = Mission.begin() + argv[1].i;
  delete *it;

  Mission.erase(Mission.begin() + argv[1].i);
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


int MissionHandler::SetCurrent(int argc, CommandParser::arg argv[])
{
  if (argv[1].i < 0) {
    Serial.println("Must be a positive number");
    return 1;
  }
  if (argv[1].i > (Mission.end() - Mission.begin()) - 1) {
    Serial.println("Chosen item number not in range");
    return 2;
  }
  else if (argc != 2) {
    Serial.println("Wrong number of arguments...");
    return 3;
  }

  Current = Mission.begin() + argv[1].i;
  return 0;
}

int MissionHandler::Begin(int argc, CommandParser::arg argv[])
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
    Serial.println("Mission already finished");
    delay(1000);
    return 4;
  }

  (*Current)->Start();
  op_mode = MANEUVER;
  Serial.println("Running mission");
  return 0;
}

void MissionHandler::Loop()
{
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

int MissionHandler::ClearMission(int argc, CommandParser::arg argv[])
{
  std::vector<MissionItem *>::iterator it = Mission.begin();

  while (it != Mission.end()) delete *it++;  // Destroys derived object

  Mission.clear();                           // Destroys base object

  Current = Mission.begin();

  op_mode = SERVICE;
}

int MissionHandler::PrintMission(int argc, CommandParser::arg argv[])
{
  std::vector<MissionItem *>::iterator it = Mission.begin();

  if (Mission.empty())
  {
    Serial.println("Mission is Empty");
    return 1;
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
