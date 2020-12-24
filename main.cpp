#include "BufferedSerial.h"
#include "DigitalIn.h"
#include "DigitalOut.h"

#include "PinNames.h"

#include "mbed.h"


#include "timers.h"
#include <cstdio>





// main() runs in its own thread in the OS
int main() {

  InitMicrosecondClock();
  
  bool flag;
  DigitalOut led1(LED1);
    DigitalOut led2(LED2);
  DigitalIn a(USER_BUTTON);
  IECTimer clocktimer1;
  clocktimer1.InitTimer(1);
  clocktimer1.SetTimerDuration(1000000.0);
  IECTimerStatus clocktimer1status;

  while (true) {
    clocktimer1status = clocktimer1.Timer(a);
    led1 = a;
    led2 = clocktimer1status.out;
  }
}
