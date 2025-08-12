#include <Arduino.h>
#include <PKG_timers.hpp>

// Bridge the example from examples/BasicTimerExample into a single-compilation unit
static PKG_Timer myTimer;

void setup() {
  Serial.begin(115200);
  myTimer.start(1000);
}

void loop() {
  if (myTimer.expired()) {
    Serial.println("Timer expired!");
    myTimer.restart();
  }
}
