#include "Callback.h"
#include "PinNames.h"
#include "Ticker.h"
#include "Timer.h"
#include "mbed.h"
#include <cstdint>
#include <list>

Ticker Microsecond_IRQ;
int64_t Microsecond_Clock;

struct IECTimerStatus {
  float ElapsedTime;
  bool out;
};

void IncrementMicrosecondClock() {
  // proccess clock update IRQ by incrementing the clock count
  Microsecond_Clock = Microsecond_Clock + 100;
}

void InitMicrosecondClock() {
  // initialise the timer IRD by setting hte base clock and callback to the IRQ
  Microsecond_IRQ.attach(&IncrementMicrosecondClock, 100us);
}

class IECTimer {
private:
  float LastSystemTime;
  float ElapsedTime;
  float PresetTime;
  bool In;
  bool Out;
  int Type;

  void UpdateTimer() {
    float period;
    switch (Type) {
    case (1):  // On Delay
      if (In == true) {
        if (ElapsedTime > PresetTime) {
          Out = true;
        }
        period = Microsecond_Clock - LastSystemTime;
        ElapsedTime = ElapsedTime + period;
      } else {
        Out = false;
        ElapsedTime = 0;
      }
      break;
    
    //case (2): // Off Delay
    //  if (In == true) {
    //    Out = true;
    //    ElapsedTime = 0;
    //  } else if (Out == true and In == false) {
    //    if (ElapsedTime > PresetTime) {
    //      Out = false;
    //      ElapsedTime = 0;
    //    }
    //    period = Microsecond_Clock - LastSystemTime;
    //    ElapsedTime = ElapsedTime + period;
    //  } else {
    //   Out = false;
    //    ElapsedTime = 0;
    //  }
    //  break;
    
    //case (3):  // Culmative Timer
     // if (In == true) {
      //  period = Microsecond_Clock - LastSystemTime;
       // ElapsedTime = ElapsedTime + period;
     // }
      //break;
    
    }
  }

public:
  IECTimerStatus Timer(bool Input) { // update the timer
    IECTimerStatus status;
    In = Input;
    UpdateTimer();
    status.ElapsedTime = ElapsedTime;
    status.out = Out;
    return status;
  }

  void SetTimerDuration(float SetTime) { PresetTime = SetTime; }

  void InitTimer(int TimerType) { // Set up the timer ready for operation
    Type = TimerType;
  }

  void ResetTimer() { ElapsedTime = 0; }
};