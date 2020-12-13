#include <types.h>
#include <list>  

void Update_Timers(int lastcycle, std::list<Timer>&  Timers) {

std::list<Timer>::iterator it;

//iterate through all the timers and update with the last cycle time 

for (it = Timers.begin(); it != Timers.end(); it++) {
  if (it->In == true) {
      //add last cycle time to the timer
      it->Elapsed_Time = it->Elapsed_Time + lastcycle;

      //if timer has exceeded the preset time then tigger the output
      if (it->Elapsed_Time >= it->Preset_Time){
          it->Out = true;
      }
  } else {
      it->Out = false;
      it->Elapsed_Time = 0;
  }
}

}