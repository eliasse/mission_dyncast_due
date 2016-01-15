#include <vector>
//#include "MissionItem.h"
#include "Enums.h"
#include "LedBlink.h"
#include <HardwareSerial.h>
#include "MissionHandler.h"

#define LED1 3
#define LED2 4
#define LED3 5

int op_mode = SERVICE;

MissionHandler Pilot;

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
  unsigned long args1[] = {LED1, 128, 3000};
  unsigned long args2[] = {LED2, 128, 2000};
  unsigned long args3[] = {LED3, 128, 1000};

  Pilot.Mission.push_back( new LedBlink(args1) );
  Pilot.Mission.push_back( new LedBlink(args2) );
  Pilot.Mission.push_back( new LedBlink(args3) );
  /*Pilot.Mission.push_back( new LedBlink(args4) );
  Pilot.Mission.push_back( new LedBlink(args5) );
  Pilot.Mission.push_back( new LedBlink(args6) );
  Pilot.Mission.push_back( new LedBlink(args7) );*/

  Serial.print("MISSION SIZE: ");
  Serial.println(Pilot.Mission.size());

  Pilot.Current = Pilot.Mission.begin();
  Serial.print("Current - Begin(): ");
  Serial.println(Pilot.Current - Pilot.Mission.begin());

  delay(2000);

  //Pilot.Begin();
  PrintMissionProgress();
}

void loop()
{
  if (Serial.available()) { ReadUserInput(); }
  Pilot.Loop();
}

void PrintMissionProgress()
{
        Serial.print("Items left: ");
        Serial.println(Pilot.Mission.size()-1);
}
