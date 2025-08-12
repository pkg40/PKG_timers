# PKG_timers Library - Quick Start Guide

## Installation & Setup

1. **Clone or copy** the PKG_timers library to your PlatformIO project
2. **Navigate** to the library directory:
   ```bash
   cd path/to/PKG_timers
   ```

## Quick Build & Test

### Build Examples
```bash
# ESP32 example
pio run -e esp32-example

# ESP8266 example  
pio run -e esp8266-example
```

### Build Tests
```bash
# ESP32 tests
pio run -e esp32-test-app

# ESP8266 tests
pio run -e esp8266-test-app
```

### Upload to Hardware
```bash
# Upload and monitor ESP32 example
pio run -e esp32-example -t upload -t monitor

# Upload and monitor ESP32 tests
pio run -e esp32-test-app -t upload -t monitor
```

## Simple Usage Example

```cpp
#include <PKG_timers.hpp>

PKG_Timer myTimer;

void setup() {
    Serial.begin(115200);
    myTimer.start(1000); // 1 second timer
}

void loop() {
    if (myTimer.expired()) {
        Serial.println("Timer expired!");
        myTimer.restart();
    }
}
```

## Available Classes

- **PKG_Timer** - Simple timer with start()/expired() interface
- **myTimer** - Full-featured timer with test()/read()/stop() methods  
- **myTimedPin** - Timer-controlled pin with beep functionality

## Need More Help?

See `BUILD_INSTRUCTIONS.md` for comprehensive documentation including:
- Complete API reference
- Advanced usage examples
- Troubleshooting guide
- Platform compatibility info
