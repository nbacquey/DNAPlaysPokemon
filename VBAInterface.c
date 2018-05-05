#include "VBAInterface.h"


char* windowCommand = "xdotool search --class VisualBoyAdvance";
char* commandFormat = "xdotool key --window %d --delay %d %s";

int delay[8] = {
  100,    //UP
  100,    //DOWN
  100,    //A
  100,    //B
  100,    //LEFT
  100,    //RIGHT
  100,    //SELECT
  100     //START
};

char* btnString[8] = {
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
  sprintf(command,commandFormat,findWindowID(),delay[commandCode],btnString[commandCode]);
  pclose(popen(command, "r"));
}
