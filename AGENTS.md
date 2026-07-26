# t_fct — Arduino uptime & boot-time library

## What it is

Single-header Arduino library (`t_fct.h`) that tracks device uptime in seconds and
estimates the boot time (epoch + human-readable) using NTP.

## Key facts

- **No build system, no tests, no CI** — just `#include "t_fct.h"`.
- Globals `t_fct` and `t0_fct` live at file scope; call `INIT_Temp_fct()` in `setup()`,
  then `Calcule_Temp_fct()` periodically (e.g. each `loop()`).
- NTP server defaults to `fr.pool.ntp.org` (France, UTC+1/CEST).
- `getBootTimeEpoch()` returns 0 if NTP hasn't synced (`time(nullptr) < 1000000000`).
- `getBootTimeString()` formats as `JJ/MM/AAAA HH:MM:SS` (French locale — no i18n).

## Using in a project

Clone or copy `t_fct.h` into your Arduino sketch folder and `#include` it.
No `library.properties` — this is not a library manager package.
