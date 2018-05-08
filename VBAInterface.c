#include "VBAInterface.h"


char* windowCommand = "xdotool search --class VisualBoyAdvance";
char* commandFormat = "xdotool key --window %d --delay %d %s";

int delay[8] = {
  100/(THROTTLE/100),    //UP
  100/(THROTTLE/100),    //DOWN
  100/(THROTTLE/100),    //A
  100/(THROTTLE/100),    //B
  100/(THROTTLE/100),    //LEFT
  100/(THROTTLE/100),    //RIGHT
  100/(THROTTLE/100),    //SELECT
  100/(THROTTLE/100)     //START
};

char* btnStrings[8] = {
  "Up",     //UP
  "Down",   //DOWN
  "A",      //A
  "B",      //B
  "Left",   //LEFT
  "Right",  //RIGHT
  "S",      //SELECT
  "E"       //START
};

int windowID = 0;

int findWindowID(){
  if(windowID == 0){
    FILE *f = popen(windowCommand,"r");
    fscanf(f,"%d",&windowID);
    pclose(f);
  }  
  return windowID;
}

void sendCommand(int commandCode){
  char* command = malloc(sizeof(char)*256);
  char* btnString = btnStrings[commandCode];
  sprintf(command,commandFormat,findWindowID(),delay[commandCode],btnString);
  pclose(popen(command, "r"));
  printf("\r           ");
  fflush(stdout);
  printf("\r%s",btnString);
  fflush(stdout);
}
