#ifndef _COMMAND_PARSER_
#define _COMMAND_PARSER_

#include <Arduino.h>
#include <HardwareSerial.h>
#include <map>

#define MAX_ARGS 10
#define MAX_LEN  100

class CommandParser {
public:

  HardwareSerial *port;
  char buffer[MAX_LEN], *bPtr;

  struct arg {
    const char *str;
    long        i;
    double      f;
  };

  // Comparator for map::find
  struct cmpStrings {
    bool operator() (const String &a, const String &b) const {
      return a<b;
    }
  };

  typedef int (*func)(int argc, struct arg argv[]);
  std::map<String, func, cmpStrings> Map;
  arg argv[MAX_ARGS];

  CommandParser(HardwareSerial * SerialPort) {
    port = SerialPort; bPtr = buffer;
  };
  void init(std::map<String, func, cmpStrings> m);
  void CheckPort();
  void ParseBuffer();
};

#endif
