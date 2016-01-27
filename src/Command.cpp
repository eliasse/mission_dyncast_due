#include "Command.h"

void CommandParser::init(std::map<String, func, cmpStrings> m)
{
  Map = m;
}

void CommandParser::CheckPort()
{
  if (port->available()) {
    int b = port->read();
    //port->print((char)b);

    if ((b == '\r') || (b == '\n')) {
      // Parse line
      //port->println("Parsing buffer...");
      //port->print("Buffer contains: "); port->println(buffer);
      delay(100);

      // Reset pointer
      bPtr = &buffer[0];
      ParseBuffer();
    }
    else {
      if (bPtr - &buffer[0] > MAX_LEN-2) {
        port->println("Buffer full");
        bPtr = &buffer[0];
        return;
      }
      // Add char to buffer
      *bPtr++ = (char)b;
      *bPtr = '\0';
    }
  }
  else return;
}

void CommandParser::ParseBuffer()
{
  int argc = 0;
  argv[argc++].str = strtok(buffer, ", ");

  while (argc < MAX_ARGS) {
    argv[argc].str = strtok(NULL, ", ");
    if (argv[argc].str == NULL) { break; }
    argv[argc].i = atol(argv[argc].str);
    argv[argc].f = atof(argv[argc].str);
    argc++;
  }

  int i = argc;
  while (i < MAX_ARGS) {
      argv[i].str = "";
      argv[i].i = 0;
      argv[i].f = 0;
      i++;
  }

  // Print result
  port->print("Command: ");
  port->println(argv[0].str);
  for (int j = 1; j < argc; j++) {
    port->print("Arg ");
    port->print(j);
    port->print(": ");
    port->println(argv[j].f);
  }

  // Create function handle
  func fn;

  // Find map entry
  std::map<String,func>::iterator it = Map.find(String(argv[0].str));

  // If no entry was found (find returns pointer to end)
  if (it == Map.end()) {
    port->println("Command not found...");
    return;
  }

  delay(100);

  // Call function
  fn = it->second;
  fn(argc, argv);
}
