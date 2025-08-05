// Basic usage example for PKG_timers
#include <PKG_timers.hpp>

PKG_Timer myTimer;

void setup() {
    Serial.begin(115200);
    myTimer.start(1000); // Start timer for 1000ms
}

void loop() {
    if (myTimer.expired()) {
        Serial.println("Timer expired!");
        myTimer.restart();
    }
}
