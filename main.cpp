#include "mbed.h"
#include "timers.cpp"
#include "types.h"

std::list<IECTimer> Timers;

// main() runs in its own thread in the OS
int main() {

  Init_Timers();

  while (true) {
    Update_Timers(Timers);
  }
}
