25 June 2026 - Intake decisions: both Pi(s) and resistor load bank (bank as repeatable thermal source for clean KPIs); custom sense board; DS18B20 chosen over DHT11 for control path (accuracy + speed); load bank needs power resistors since 1/4 W kit parts can't dissipate real heat. ACS712 linear Hall Sensor VIOUT(Q) is VCC x 0.5 and VCC is 5V. VIOUT = 2.5V
VIOUT = 2.5V
Sensitivity = 0.185 V/amp
ESP32 ceiling = 3.3V; Amps for 5A rated ACS712 to reach ESP32 ceiling: (3.3 - 2.5) / 0.185 = 4.32A
Conclusion: raw wiring risks over-voltage damage to the ESP32 above 4.3A. ESP32 pins are not 5V tolerant (max - 3.3V); ACS712 output exceeds this, risking pin damage. Sensor idles at 2.5V, bidirectional swing.
Solution: Voltage divider at the cost of resolution. Due to output getting scaled down, signal is compressed and changes per amp shrink by the same ratio. Potential noise interference. 


