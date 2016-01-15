char input[100];

void ReadUserInput()
{
        int n_read = Serial.readBytesUntil('\n',input,100);
        input[n_read] = '\0';
        char *token = strtok(input," ,");
        Serial.print("Command: "); Serial.println(token);
        Serial.print("Input  : "); Serial.println(input);

        if (!strcmp(token,"PRINT")) {
	         Pilot.PrintMission();
        }
        else if (!strcmp(token,"BEGIN")) {
          Pilot.Begin();
        }
        else if (!strcmp(token,"CLEAR")) {
	         Pilot.ClearMission();
           Serial.println("Mission Cleared");
        }
        else if (!strcmp(token,"ERASE")) {
          int args[2];
          char *pEnd;
          //token   = strtok(NULL, " ,");
          args[0] = (unsigned long)strtol(input, &pEnd, 10);
          args[1] = (unsigned long)strtol(pEnd, NULL, 10);
          Serial.print("Arg 0: "); Serial.println(args[0]);
          Serial.print("Arg 1: "); Serial.println(args[1]);
          delay(1000);
          Pilot.Erase(args);
        }
        else if (!strcmp(token,"CURRENT")) {
          int arg;
          token   = strtok(NULL, " ,");
          arg = (unsigned long)atoi(token);
          Pilot.SetCurrent(arg);
        }
        else if (!strcmp(token,"RESET")) {
          Pilot.ResetMission();
        }
        else if (!strcmp(token,"LED")) {
          unsigned long args[3];
          token   = strtok(NULL, " ,");
          args[0] = (unsigned long)atoi(token);
          token   = strtok(NULL, " ,");
          args[1] = (unsigned long)atoi(token);
          token   = strtok(NULL, " ,");
          args[2] = (unsigned long)atoi(token);

          Pilot.Mission.push_back( new LedBlink(args) );
        }
        else if (!strcmp(token,"SWAP"))
        {
          int args[2];
          token   = strtok(NULL, " ,");
          args[0] = (unsigned long)atoi(token);
          token   = strtok(NULL, " ,");
          args[1] = (unsigned long)atoi(token);

          Pilot.Swap(args[0], args[1]);
        }

        while(Serial.available()) { Serial.read(); } // Removes trailing crap in serial buffer
}
