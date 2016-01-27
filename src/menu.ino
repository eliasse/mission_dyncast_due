char input[100];

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

  Serial.print("Map size: "); Serial.println(Map.size());
}

// void ReadUserInput()
// {
//         int n_read = Serial.readBytesUntil('\n',input,100);
//         input[n_read] = '\0';
//         char *token = strtok(input," ,");
//         Serial.print("Command: "); Serial.println(token);
//         Serial.print("Input  : "); Serial.println(input);

//         else if (!strcmp(token,"ERASE")) {
//           int args[2];
//           char *pEnd;
//           //token   = strtok(NULL, " ,");
//           args[0] = (unsigned long)strtol(input, &pEnd, 10);
//           args[1] = (unsigned long)strtol(pEnd, NULL, 10);
//           Serial.print("Arg 0: "); Serial.println(args[0]);
//           Serial.print("Arg 1: "); Serial.println(args[1]);
//           delay(1000);
//           Pilot.Erase(args);
//         }
//         else if (!strcmp(token,"CURRENT")) {
//           int arg;
//           token   = strtok(NULL, " ,");
//           arg = (unsigned long)atoi(token);
//           Pilot.SetCurrent(arg);
//         }
//         else if (!strcmp(token,"RESET")) {
//           Pilot.ResetMission();
//         }
//         else if (!strcmp(token,"LED")) {
//           unsigned long args[3];
//           token   = strtok(NULL, " ,");
//           args[0] = (unsigned long)atoi(token);
//           token   = strtok(NULL, " ,");
//           args[1] = (unsigned long)atoi(token);
//           token   = strtok(NULL, " ,");
//           args[2] = (unsigned long)atoi(token);
//
//           Pilot.Mission.push_back( new LedBlink(args) );
//         }
//         else if (!strcmp(token,"SWAP"))
//         {
//           int args[2];
//           token   = strtok(NULL, " ,");
//           args[0] = (unsigned long)atoi(token);
//           token   = strtok(NULL, " ,");
//           args[1] = (unsigned long)atoi(token);
//
//           Pilot.Swap(args[0], args[1]);
//         }
//
//         while(Serial.available()) { Serial.read(); } // Removes trailing crap in serial buffer
// }
