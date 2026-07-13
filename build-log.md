**25 June 2026** - Intake decisions: both Pi(s) and resistor load bank (bank as repeatable thermal source for clean KPIs); custom sense board; DS18B20 chosen over DHT11 for control path (accuracy + speed); load bank needs power resistors since 1/4 W kit parts can't dissipate real heat. <br> ACS712 linear Hall Sensor VIOUT(Q) is VCC x 0.5 and VCC is 5V. <br> VIOUT = 2.5V <br>
Sensitivity = 0.185 V/amp <br>
ESP32 ceiling = 3.3V; Amps for 5A rated ACS712 to reach ESP32 ceiling: (3.3 - 2.5) / 0.185 = 4.32A <br>
Conclusion: raw wiring risks over-voltage damage to the ESP32 above 4.3A. ESP32 pins are not 5V tolerant (max - 3.3V); ACS712 output exceeds this, risking pin damage. Sensor idles at 2.5V, bidirectional swing. <br>
Solution: Voltage divider at the cost of resolution. Due to output getting scaled down, signal is compressed and changes per amp shrink by the same ratio. Potential noise interference. 

**27 June 2026** - **BOM:** 
<br> &nbsp;&nbsp; **Fans:** 3 x be quiet! Pure Wings 3 120mm PWM Fans | (3 pack, using 2) | $26 
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 4th wire takes the speed-control signal for closed-loop fan control; 3-wire can't be cleanly PWM'd.
<br> &nbsp;&nbsp; **Power Supply:** 1 x PowerSpec FX V2 500 Watt ATX Non-Modular Power Supply | $40
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 12/5/3.3V rails matching real rack powering; 500W creates ample headroom for a ~40W - 50W load.
<br> &nbsp;&nbsp; **Sensor:** 3 x Ferwooh ACS712-05B 5A module | (3 pack, using 1) | $7.75
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 185 mV/A sensitivity gives finer resolution per amp than 20A/30A parts.
<br> &nbsp;&nbsp; **Breakout Board:** 1 x MELIFE 24 Pin ATX Breakout | (2 pack, using 1) | $10
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Per-rail screw terminals + built-in switch (handles PS_ON) + per-channel fuses for protection during bring-up.
<br> &nbsp;&nbsp; **Power resistors:** 2 x AISIBO 10Ω 50W aluminum power resistors | $7
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Opted for 50 W resistors for ~29W load to keep them thermally stable and protect measurement integrity.

**28 June 2026** - ESP32 toolchain bring-up (PlatformIO + Arduino framework, esp32dev). Blink + serial counter working. Upload initially failed with pySerial connection error; Device Manager showed no CP210x COM port -> root cause was a charge-only USB cable, fixed by swapping to a data cable. Onboard LED not visible on this WROOM-32E board, so wired an external LED on GPIO 2 (220Ω, ~6mA) to verify GPIO output.  Confirmed running via serial monitor at 115200 baud.

<img width="691" height="528" alt="Screenshot 2026-06-28 193414" src="https://github.com/user-attachments/assets/340b8908-381d-4523-9f1c-0ade0ae456f4" />

https://github.com/user-attachments/assets/4ce04e39-1df1-4afa-b1c2-e18521d48242

**29 June 2026** - Stood up MQTT broker. Installed WSL2 + Ubuntu (chose Linux for broker per industry-standard goal). Initial Linux password mistyped during blind install setup; reset via **wsl -u root** + **passwd**. Installed Mosquitto 2.0.22 (broker + clients) via apt; confirmed service active. Verified pub/sub in isolation: mosquitto_sub -t test/topic in one terminal received mosquitto_pub message from another. Broker proven working standalone before adding Node-RED.

**30 June 2026** - Installed Node.js v20 via NodeSource since apt's version was too old; installed Node-RED, editor reachable at localhost:1880.

**1 July 2026** - Sized the ACS712 voltage divider
<br> Goal: scale the ACS712's output voltage down so it never exceeds the ESP32's 3.3V input limit, while keeping good measurement resolution.
<br><br>
The decision: Instead of designing for the sensor's full 5A range (safe but wastes resolution) or just my exact expected load (good resolution but risky if current spikes), I sized the divider for a realistic ceiling of ~4A which is above anything my load can actually draw (~2.4A from the load bank), with margin. This keeps resolution high at my operating point while staying safe. I added a 1N4728 3.3V Zener diode as clamp on the ESP32 pin for fault protection so that even an unexpected spike can't push the pin over 3.3V. The divider handles the normal range while Zener catches abnormal ranges. 
<br> <br>
My numbers: 
<br> - ACS712 outputs 2.5V at 0A, rising 0.185V per amp
<br> - At my 4A design ceiling: 2.5 + (4 x 0.185) = 3.24V (the max the divider must handle)
<br> - Chose divider resistors R1 = 1kΩ (from sensor output) and R2 = 10kΩ (to ground), tap at the junction to the ESP32
<br> - Ratio = R2/(R1 + R2) = 10/11 = 0.909
<br> - Total resistance 11kΩ - low enough that the ESP32's ADC won't distort the reading (avoids the high-impedance loading effect)

Predicted test values to verify
<br> - At 0A: sensor = 2.5V -> ESP32 pin = 2.5 x 0.909 = ~2.27V
<br> - At 4A: sensor = 3.24V -> ESP32 pin = ~2.95V
<br> - Measurement range at the ADC sits between ~2.27V and ~2.95V

**7 July 2026** - KPI targets committed
<br> <img width="518" height="596" alt="image" src="https://github.com/user-attachments/assets/5b4f555d-135b-4667-aefc-4ab2f811bba2" />

**9 July 2026** - Completed Node-RED telemetry pipeline end to end. 
<br> Built flow: mqtt-in -> debug + gauge. 
<br> Confirmed broker -> Node-RED by publishing test message to debug panel. Dashboard 2.0 (@flowfuse/node-red-dashboard because old node-red-dashboard deprecated).
<br> Wired gauge and built simple UI hierarchy, published numeric value, needle tracked on dashboard. Full pipeline proven: CLI -> Mosquitto -> Node-RED -> live dashboard. 
<br> System is ready to swap CLI publisher for ESP32.

**10 July 2026** - ATX PSU bring-up.
<br> Connected PowerSpec FX V2 non-modular 24-pin to MELIFE breakout; other cables left dangling/isolated.
<br> Rails verified with multimeter: 12V rail = 12.1V, 5V = 5.2V, 3.3V = 3.4V. All within ATX ±5% tolerance. Power source confirmed good in isolation before connecting any load.

**11 July 2026** - Voltage Divider verified.
<br> Built 1kΩ (R1)/10kΩ (R2) divider on breadboard, fed from PSU 3.3V rail (measured 3.4V). Predicted junction voltage 3.4 x 0.909 = 3.09V; measured 3.06V - within resistor tolerance (±5%). Divider ratio and values confirmed in isolation before integrating with ACS712/ESP32.

**12 July 2026** - Wrote current-sensing firmware (esp32-current-sense).
<br> Built the raw-ADC-to-amps conversion chain, all constants derived from datasheet + divider design:
<br> - analogRead(GPIO32) -> raw 0-4095. Used GPIO32 specifically because it's on ADC1; ADC2 shares hardware with WiFi and breaks analog reads when WiFi is active (needed for MQTT)
<br> - raw x (3.3 / 4095.0) -> ESP32 voltage. Used 4095.0 (not 4095) to force floating point division and avoid integer division clipping.
<br> - voltage / 0.909 -> sensor voltage (undoes the hardware divider in software)
<br> - (sensorVoltage - 2.5) / 0.185 -> amps (undoes ACS712 zero-offset and sensitivity). Verified each step against raw values on a floating pin: readings printed cleanly at 1 Hz (matches KPI sample rate), and floating input correctly computed as large negative current (~-11.8A), as predicted - nonsense input, but processed correctly, confirming the math.
<br> **Note: Not yet accurate -** needs averaging (noise reduction) and calibration against multimeter (ideal vs. real constants - measured divider ratio was 0.900 vs. ideal 0.909; real ACS712 offset varies; ESP32 ADC is nonlinear).

**13 July 2026** - Added 100-sample averaging to current-sensing firmware. 
<br> Reads ADC 100 times per cycle, averages (sum/100) before conversion, to reduce random noise (SNR imporvement). 
<br> Chose 100 samples: strong noise reduction, negligible time (~sub-ms vs. 1s loop), past the point of meaningful diminishing returns. 
<br> Verified on floating pin: reading spread tightened from ~20 counts (single read) to ~2 counts (averaged).
<br> **Note:** mangnitude of values still meaningless (floating pin); confims stabalization only. Real accuracy pending sensor connection + multimeter calibration at makerpace.





