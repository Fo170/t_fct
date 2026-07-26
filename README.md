# t_fct — Arduino uptime & boot-time library

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/fo170/library/t_fct)](https://registry.platformio.org/libraries/fo170/t_fct)

Track device uptime in seconds and estimate the boot time (epoch + human-readable string) using NTP.

## Features

- Uptime counter with millisecond precision (reported in seconds as a `float`)
- Boot-time estimation from NTP: `epoch = now - uptime`
- Human-readable boot-time string (French locale: `JJ/MM/AAAA HH:MM:SS`)
- Single-header — just `#include "t_fct.h"`

## Quick start

### PlatformIO

```ini
lib_deps =
    https://github.com/Fo170/t_fct.git@^1.0.0
```

### Arduino IDE

Clone or copy `t_fct.h` into your sketch folder and `#include` it.

## Usage

```cpp
#include <t_fct.h>

void setup() {
  Serial.begin(115200);
  INIT_Temp_fct();               // start the uptime counter
}

void loop() {
  Calcule_Temp_fct();            // update every loop

  Serial.print("Uptime (s): ");
  Serial.println(t_fct);

  Serial.print("Boot time: ");
  Serial.println(getBootTimeString());

  delay(1000);
}
```

> **NTP note:** `getBootTimeEpoch()` and `getBootTimeString()` return 0 / `"NTP non synchronisé"` until `time(nullptr) >= 1000000000`. Call `configTime()` with your NTP server in `setup()`.

## API

| Function / Global | Returns | Description |
|---|---|---|
| `INIT_Temp_fct()` | — | Start the uptime counter (call once in `setup()`). |
| `Calcule_Temp_fct()` | — | Update `t_fct`. Call regularly (e.g. every `loop()`). |
| `t_fct` | `float` | Uptime in seconds. |
| `t0_fct` | `unsigned long` | `millis()` value at last `INIT_Temp_fct()`. |
| `getBootTimeEpoch()` | `time_t` | Boot epoch from NTP, or 0 if not synced. |
| `getBootTimeString()` | `String` | Boot time as `"JJ/MM/AAAA HH:MM:SS"` or `"NTP non synchronisé"`. |

## NTP defaults

| Setting | Value |
|---|---|
| Server | `fr.pool.ntp.org` |
| Timezone | UTC+1 (CET) |
| DST offset | +3600 s (CEST) |

Override `ntpServer`, `gmtOffset_sec`, or `daylightOffset_sec` before calling `configTime()`.

## Requirements

- Arduino core with `<time.h>` support (ESP32, ESP8266, SAMD, RP2040, etc.)
- Network connection for boot-time functions

## Licence

See `LICENSE` file in the repository.
