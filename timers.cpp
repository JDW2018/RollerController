#include "Callback.h"
#include "Ticker.h"
#include "mbed.h"
#include <cstdint>
#include <list>

struct IECTimer {
  float Preset_Time;
  float Elapsed_Time;
  bool In;
  bool Out;
  bool Cumulative;
};

Ticker Microsecond_IRQ;
int64_t Microsecond_Clock;
int64_t Last_Cycle;

void Increment_Microsecond_Clock() {
  // proccess clock update IRQ by incrementing the clock count
  Microsecond_Clock = Microsecond_Clock + 100;
}

void Init_Timers() {
  // initialise the timer IRD by setting hte base clock and callback to the IRQ
  Microsecond_IRQ.attach(&Increment_Microsecond_Clock, 100us);
}

float Calculate_Cycle_Time() {
  // calculate the last cycle time
  float Cycle_Time;
  Cycle_Time = (Microsecond_Clock - Last_Cycle) / 10;
  return Cycle_Time;
}

void Update_Timers(std::list<IECTimer> &Timers) {

  float cycle = Calculate_Cycle_Time();

  std::list<IECTimer>::iterator it;
  // iterate through all the timers and update with the last cycle time
  for (it = Timers.begin(); it != Timers.end(); it++) {
    if (it->In == true) {
      // add last cycle time to the timer
      it->Elapsed_Time = it->Elapsed_Time + cycle;
      // if timer has exceeded the preset time then tigger the output
      if (it->Elapsed_Time >= it->Preset_Time) {
        it->Out = true;
      }
    } else {
      // if the timer is not enabled then reset the timer
      it->Out = false;
      if (it->Cumulative == true) {
        it->Elapsed_Time = 0;
      }
    }
  }
}