# PKG_timers Library - Build Instructions

This document provides instructions for building and testing the PKG_timers library using PlatformIO.

## Overview

PKG_timers is an Arduino timer library that provides:
- `myTimer` class for basic timing operations
- `myTimedPin` class for timed pin control with beep functionality  
- `PKG_Timer` wrapper class for simplified API

## Prerequisites

- [PlatformIO Core](https://platformio.org/install/cli) or [PlatformIO IDE](https://platformio.org/install/ide)
- ESP32 or ESP8266 development board (optional for testing on hardware)

## Project Structure

```
PKG_timers/
├── doc/                    # Documentation
├── examples/               # Example sketches
│   └── BasicTimerExample/
├── src/                    # Library source code
│   ├── PKG_timers.hpp     # Main header file
│   ├── PKG_timers.cpp     # Implementation
│   ├── main_example.cpp   # PlatformIO example runner
│   └── main_test.cpp      # PlatformIO test runner
├── test/                   # Test files
├── library.json           # Library metadata
├── library.properties     # Arduino library properties
├── platformio.ini         # PlatformIO configuration
└── README.md
```

## Building with PlatformIO

### Available Build Environments

The `platformio.ini` file defines 4 build environments:

- **esp32-example** - Build example code for ESP32
- **esp32-test-app** - Build tests for ESP32
- **esp8266-example** - Build example code for ESP8266
- **esp8266-test-app** - Build tests for ESP8266

### Build Commands

Open a terminal in the library root directory and use these commands:

```bash
# Build example for ESP32
pio run -e esp32-example

# Build tests for ESP32
pio run -e esp32-test-app

# Build example for ESP8266
pio run -e esp8266-example

# Build tests for ESP8266
pio run -e esp8266-test-app

# Build all environments
pio run

# Clean build files
pio run -t clean
```

### Upload and Monitor

To upload to a connected board and monitor serial output:

```bash
# Upload example to ESP32 and monitor
pio run -e esp32-example -t upload -t monitor

# Upload tests to ESP32 and monitor
pio run -e esp32-test-app -t upload -t monitor
```

## Library Usage

### Basic Timer Example

```cpp
#include <PKG_timers.hpp>

PKG_Timer myTimer;

void setup() {
    Serial.begin(115200);
    myTimer.start(1000); // Start 1-second timer
}

void loop() {
    if (myTimer.expired()) {
        Serial.println("Timer expired!");
        myTimer.restart();
    }
}
```

### Using myTimer Class Directly

```cpp
#include <PKG_timers.hpp>

myTimer timer(1000); // 1-second period

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (timer.test()) {
        Serial.println("Timer fired!");
        // timer.test() automatically restarts the timer
    }
}
```

### Timed Pin Control

```cpp
#include <PKG_timers.hpp>

myTimedPin buzzer(13, 500, false); // Pin 13, 500ms, active high

void setup() {
    buzzer.setEnable(true);
}

void loop() {
    buzzer.beep(3); // Beep 3 times
    delay(2000);
}
```

## API Reference

### PKG_Timer Class

- `PKG_Timer()` - Default constructor
- `PKG_Timer(unsigned long period)` - Constructor with period
- `void start(unsigned long period)` - Start timer with specified period (ms)
- `bool expired()` - Check if timer has expired (non-destructive)
- `void restart()` - Restart the timer

### myTimer Class

- `myTimer(unsigned long period)` - Constructor with period in milliseconds
- `bool test(bool verbose = false)` - Test if period elapsed, auto-restarts
- `unsigned long read()` - Get elapsed time
- `bool start()` - Resume a stopped timer
- `bool stop()` - Stop the timer
- `void restart()` - Restart from current time

### myTimedPin Class

- `myTimedPin(uint8_t pin, unsigned long time, bool assertedLow = false)` - Constructor
- `void beep(uint8_t count = 1, unsigned int time = 0)` - Generate beep pattern
- `void setEnable(bool enable)` - Enable/disable pin control
- `bool getEnable()` - Get enable state
- `void testStop()` - Call in loop() to handle beep timing
- `void suddenStop()` - Immediately stop beeping

## Troubleshooting

### Build Issues

1. **"cannot open source file Arduino.h"** - This is normal in the IDE; the library builds correctly with PlatformIO.

2. **Missing TRACE.h** - The library gracefully handles missing TRACE.h. If you have a custom TRACE.h, place it in your include path.

3. **Board not found** - Modify `platformio.ini` to use your specific board:
   ```ini
   [env:esp32-example]
   board = your_board_here  # e.g., esp32doit-devkit-v1, lolin_s2_mini
   ```

### Platform Support

The library is tested on:
- ESP32 (Espressif ESP32)
- ESP8266 (Espressif ESP8266)

Other Arduino-compatible platforms may work but are not officially tested.

## Contributing

1. Make changes to the library source code
2. Test with both example and test environments
3. Update documentation if needed
4. Commit changes with descriptive messages

## License

MIT License - See source files for full copyright notice.
