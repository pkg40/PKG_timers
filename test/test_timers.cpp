
#include <Arduino.h>
#include <PKG_timers.hpp>

void test_timer_basic() {
    PKG_Timer t;
    t.start(500);
    delay(500);
    if (!t.expired()) {
        Serial.println("Test failed: timer should be expired");
    } else {
        Serial.println("Test passed: timer expired as expected");
    }
}

void setup() {
    Serial.begin(115200);
    test_timer_basic();
}

void loop() {}
