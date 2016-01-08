#include <vector>
#include "MissionItem.h"
#include "Enums.h"
#include "LedBlink.h"

#define LED1 3
#define LED2 4
#define LED3 5

std::vector<MissionItem*> Mission;

void setup()
{
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  analogWrite(LED1, 0);
  analogWrite(LED2, 0);
  analogWrite(LED3, 0);

  // Setup a mission
  unsigned long args1[] = {LED1, 128, 5000};
  unsigned long args2[] = {LED2, 128, 5000};
  unsigned long args3[] = {LED3, 128, 5000};
  unsigned long args4[] = {LED1, 64, 2000};
  unsigned long args5[] = {LED3, 64, 2000};
  unsigned long args6[] = {LED2, 254, 3000};
  unsigned long args7[] = {LED1, 254, 3000};
  Mission.push_back( new LedBlink(args1) );
  Mission.push_back( new LedBlink(args2) );
  Mission.push_back( new LedBlink(args3) );
  Mission.push_back( new LedBlink(args4) );
  Mission.push_back( new LedBlink(args5) );
  Mission.push_back( new LedBlink(args6) );
  Mission.push_back( new LedBlink(args7) );

  Serial.print("MISSION SIZE: ");
  Serial.println(Mission.size());

  Mission.front()->Start();
  PrintMissionProgress();
}

void loop()
{
  if (Mission.front()->Progress())
  {
    delete *Mission.begin();          // Release memory
    Mission.erase(Mission.begin());   // Delete vector item

    if (Mission.begin() != Mission.end()) {
      Mission.front()->Start();
      PrintMissionProgress();
    }
    else Serial.println("Mission Complete");
  }
}

void PrintMissionProgress()
{
  Serial.print("Items left: ");
  Serial.println(Mission.size()-1);
}
