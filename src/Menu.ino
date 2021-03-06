char input[100];

int PrintHelp(int argc, CommandParser::arg argv[])
{
  Serial.println("============================== COMMANDS ==============================");
  PrintCommand(String("PRINT"), String("Prints Mission."));
  PrintCommand(String("BEGIN"), String("Begin Mission."));
  PrintCommand(String("CLEAR"), String("Clears Mission (Removes all times)."));
  PrintCommand(String("ERASE <1> <2>"), String("Removes items <1> to <2>. Optionally just <1> to remove one item."));
  PrintCommand(String("CURRENT <1>"), String("Set active mission item to <1>."));
  PrintCommand(String("RESET"), String("Set current mission item to beginning."));
  PrintCommand(String("SWAP <1> <2>"), String("Swap mission items <1> and <2>."));
  PrintCommand(String("LED <1> <2> <3>"), String("<Pin[3-5]> <Brightness[0-254]> <Duration[ms]> Add a LED mission item."));
  PrintCommand(String("INSERT <1> <2> <1*> <2*> <...>"), String("Insert mission item <2> in place <1>. *Arguments to the mission item."));
}

void PrintCommand(String cmd, String expl) {
  // Print the command
  Serial.print(cmd);
  // Print spaces
  for (int i = 0; i < 50 - cmd.length(); i++) {
    Serial.print(" ");
  }
  // Print explanation
  Serial.println(expl);
}

int AddLED(int argc, CommandParser::arg argv[])
{
  if (argc != 4) {
    Serial.println("Not matching number of arguments...");
    return 1;
  }
  long args[] = {argv[1].i, argv[2].i, argv[3].i};
  MissionHandler::Mission.push_back( new LedBlink(args) );
  return 0;
}

int Insert(int argc, CommandParser::arg argv[])
{
        // Lets create a reduced set of arguments
        int argc_tmp = argc - 2;
        CommandParser::arg argv_tmp[MAX_ARGS];

        for (int i = 0; i<argc_tmp; i++) {
                argv_tmp[i] = argv[i+2];
        }

        if (strcmp(argv_tmp[0].str,"LED") == 0) {
                long args[] = {argv_tmp[1].i, argv_tmp[2].i, argv_tmp[3].i};
                MissionHandler::Mission.insert(MissionHandler::Mission.begin() + argv[1].i,
                                               new LedBlink(args) );
        }
}

// För menysystemet
void SetupMenu()
{
  //Map.insert(std::pair<String,func>(String("BAJS"), &bajsa));
  //Map.insert(std::pair<String,func>(String("TJENA"), &Tjena));

  //Map[String("BAJS")] = &bajsa;
  //Map[String("TJENA")] = &Tjena;
  MAP("PRINT",    MissionHandler::PrintMission);
  MAP("BEGIN",    MissionHandler::Begin);
  MAP("CLEAR",    MissionHandler::ClearMission);
  MAP("ERASE",    MissionHandler::Erase);
  MAP("CURRENT",  MissionHandler::SetCurrent);
  MAP("RESET",    MissionHandler::ResetMission);
  MAP("SWAP",     MissionHandler::Swap);
  MAP("LED",      AddLED);
  MAP("INSERT",   Insert);
  MAP("HELP",     PrintHelp);

  Serial.print("Menu size: "); Serial.println(Map.size());
}
