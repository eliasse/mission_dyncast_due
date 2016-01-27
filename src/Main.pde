#include <vector>
#include "Enums.h"
#include "LedBlink.h"
#include <HardwareSerial.h>
#include "MissionHandler.h"
#include "CommandParser.h"

#define LED1 3
#define LED2 4
#define LED3 5

// Type definition of functions to call when command is received
typedef int (*func)(int argc, struct CommandParser::arg argv[]);
#define MAP(X,Y) Map.insert(std::pair<String,func>(String(X), Y))

CommandParser *Menu = new CommandParser(&Serial);

// Create a mapping of command strings and functions to call
std::map<String, func, CommandParser::cmpStrings> Map;

int op_mode = SERVICE;

MissionHandler MH;

void setup()
{
  Serial.begin(115200);
  SetupMenu();            // Must be before Menu->init(Map)
  Menu->init(Map);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  analogWrite(LED1, 0);
  analogWrite(LED2, 0);
  analogWrite(LED3, 0);

  // Setup a mission
  long args1[] = {LED1, 128, 3000};
  long args2[] = {LED2, 128, 2000};
  long args3[] = {LED3, 128, 1000};

  MH.Mission.push_back( new LedBlink(args1) );
  MH.Mission.push_back( new LedBlink(args2) );
  MH.Mission.push_back( new LedBlink(args3) );
  /*MH.Mission.push_back( new LedBlink(args4) );
  MH.Mission.push_back( new LedBlink(args5) );
  MH.Mission.push_back( new LedBlink(args6) );
  MH.Mission.push_back( new LedBlink(args7) );*/

  Serial.print("MISSION SIZE: ");
  Serial.println(MH.Mission.size());

  MH.Current = MH.Mission.begin();
  Serial.print("Current - Begin(): ");
  Serial.println(MH.Current - MH.Mission.begin());

  delay(2000);

  //MH.Begin();
  PrintMissionProgress();
}

void loop()
{
  //if (Serial.available()) { ReadUserInput(); }
  Menu->CheckPort();
  MH.Loop();
}

void PrintMissionProgress()
{
        Serial.print("Items left: ");
        Serial.println(MH.Mission.size()-1);
}
