#ifndef _LEDBLINK_
#define _LEDBLINK_

#include "MissionItem.h"
#include "Enums.h"

class LedBlink : public MissionItem {
public:
  uint8_t Pin, Brightness;
  unsigned long duration, start;
  LedBlink(unsigned long args[]);    // Constructor
  virtual void Cloops();             // Controlloops
  virtual void Start();
  virtual int  Progress();            // Check progress (return true if done?)
  virtual void onCompletion();
  virtual ~LedBlink();
};

LedBlink::LedBlink(unsigned long args[])
{
  type = LEDBLINK;

  Serial.println("Setting arguments");

  Pin = args[0];
  Brightness = args[1];
  duration = args[2];

  Serial.print("Pin: "); Serial.println(Pin);
  Serial.print("Led Brightness: "); Serial.println(Brightness);
  Serial.print("Duration: "); Serial.println(duration);
}

LedBlink::~LedBlink()
{
  Serial.println("Deleting LedBlink object");
}

void LedBlink::Cloops()
{
  Serial.println("Setting control loops");
}

int LedBlink::Progress()
{
  static unsigned long print_timer = 0;

  float progress = (float)(millis()-start) / (float)duration;

  if ((millis() - print_timer > 1000) || print_timer == 0)
  {
    print_timer = millis();
    Serial.println("Progress: ");
    Serial.println(progress,1);
  }

  if (progress > 1)
    {
      onCompletion();
      return 1;
    }
  return 0;
}

void LedBlink::Start()
{
  Serial.println("Starting LedBlink");
  start = millis();
  analogWrite(Pin, Brightness);
}

void LedBlink::onCompletion()
{
  Serial.println("LedBlink complete");
  analogWrite(Pin,0);
}

#endif
