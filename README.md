# Server-Rack Thermal Control & Monitoring
An instrumented server rack that mirrors a data-center cell: a controlled compute/thermal load, real-time power monitoring, closed-loop fan control, and live telemetry. Built to develop hands-on power, thermal, and embedded-systems engineering.

**What it does:**

- Measures current and rail voltage with an ACS712 sensor and ESP32
- Drives PWM fans via a closed-loop temperature control loop to hold a thermal setpoint under load
- Streams telemetry over MQTT to a live Node-RED dashboard
- Tracks data-center-style KPIs including PUE-lite (cooling overhead ratio)

**Stack:** ESP32 (C++/PlatformIO) · ACS712 current sensor · DS18B20 temperature · PWM fans · Mosquitto MQTT · Node-RED dashboard · custom KiCad sense board

(_[KPI results](KPI.md), [architecture diagram](flowchart.md), and [BOM](https://github.com/RyanJRa/server-rack-thermal-control/blob/main/build-log.md#:~:text=Fans%3A%203,protect%20measurement%20integrity.)— updated as the build progresses._)
