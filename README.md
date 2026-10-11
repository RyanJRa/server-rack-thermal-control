# Local AI Server Rack
 
A server rack built to run local AI agents on my own hardware. The build is reliability-first: the power and thermal monitoring layer comes before any compute, because AI workloads can't run reliably on infrastructure you can't measure.
 
## Status
 
| Layer | Status |
| --- | --- |
| Current sensing (ACS712 + ESP32) | Verified — voltage divider within 1% of calculated values |
| Firmware (C++ / PlatformIO) | Verified — ADC1 pin (avoids ADC2/WiFi conflict), 100-sample averaging cut reading spread from 20 counts to 2 |
| Telemetry (Mosquitto MQTT → Node-RED) | Verified — live dashboard; diagnosed zero-point drift caused by USB supply sag |
| Power PCB (9V → 5V buck → 3.3V LDO, Altium) | Designed — fabrication pending |
| Temperature sensing | In progress |
| Closed-loop PWM fan control (PID) | Next |
| Compute node (Jetson Orin Nano) | Planned |
 
## Roadmap
 
1. **Reliable monitoring core** — accuracy against a reference, multi-day uptime with no dropped data, automatic recovery from WiFi or power loss, and stable PID control under a step load.
2. **Compute integration** — add a Jetson Orin Nano, powered and monitored by the rack's own system.
3. **Local agents under load** — run AI agents locally and measure throttling and clock retention with closed-loop cooling vs. without.
## Metrics
 
The rack tracks data-center-style KPIs, including PUE-lite (cooling power relative to load power). Targets and results: [KPI results](KPI.md)

**Stack:** ESP32 (C++/PlatformIO) · ACS712 current sensor · Mosquitto MQTT · Node-RED · Linux · Altium Designer

( [architecture diagram](flowchart.md), and [BOM](https://github.com/RyanJRa/server-rack-thermal-control/blob/main/build-log.md#:~:text=Fans%3A%203,protect%20measurement%20integrity.)— updated as the build progresses._)
