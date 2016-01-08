#ifndef _MISSION_ITEM_
#define _MISSION_ITEM_

#include "Enums.h"

class MissionItem {
public:
  int type;
  virtual ~MissionItem();
  virtual void Cloops() = 0;
  virtual void Start() = 0;
  virtual int  Progress() = 0;
  virtual void onCompletion() = 0;
  void GetTypeId();
};

MissionItem::~MissionItem() {
  Serial.println("Destroying MissionItem");
}

void MissionItem::GetTypeId() {
  Serial.println("Mission Item Type: ");

  switch (type)
    {
    default:
      Serial.println("Non-existing mission item type");
      break;
    case COURSE:
      Serial.print("COURSE (Id ");
      Serial.print(type);
      Serial.println(")");
      break;
    case LEDBLINK:
      Serial.println("LEDBLINK (Id ");
      Serial.print(type);
      Serial.println(")");
      break;
    }
}

#endif
