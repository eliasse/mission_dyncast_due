char input[100];

void ReadUserInput()
{
        int n_read = Serial.readBytesUntil('\n',input,100);
        input[n_read] = '\0';
        char *token = strtok(input," ,");

        if (!strcmp(token,"PRINT")) {
	         Pilot.PrintMission();
        }
        else if (!strcmp(token,"BEGIN")) {
          Pilot.Begin();
        }
        else if (!strcmp(token,"ERASE")) {
	         Pilot.EraseMission();
           Serial.println("Mission Cleared");
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

        while(Serial.available()) { Serial.read(); } // Removes trailing crap in serial buffer
}
