25 June 2026 - Intake decisions: both Pi(s) and resistor load bank (bank as repeatable thermal source for clean KPIs); custom sense board; DS18B20 chosen over DHT11 for control path (accuracy + speed); load bank needs power resistors since 1/4 W kit parts can't dissipate real heat. <br> ACS712 linear Hall Sensor VIOUT(Q) is VCC x 0.5 and VCC is 5V. <br> VIOUT = 2.5V <br>
Sensitivity = 0.185 V/amp <br>
ESP32 ceiling = 3.3V; Amps for 5A rated ACS712 to reach ESP32 ceiling: (3.3 - 2.5) / 0.185 = 4.32A <br>
Conclusion: raw wiring risks over-voltage damage to the ESP32 above 4.3A. ESP32 pins are not 5V tolerant (max - 3.3V); ACS712 output exceeds this, risking pin damage. Sensor idles at 2.5V, bidirectional swing. <br>
Solution: Voltage divider at the cost of resolution. Due to output getting scaled down, signal is compressed and changes per amp shrink by the same ratio. Potential noise interference. 

27 June 2026 - **BOM:** 
<br> &nbsp;&nbsp; **Fans:** 3 x be quiet! Pure Wings 3 120mm PWM Fans | (3 pack, using 2) | $26 
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 4th wire takes the speed-control signal for closed-loop fan control; 3-wire can't be cleanly PWM'd.
<br> &nbsp;&nbsp; **Power Supply:** 1 x PowerSpecFX V2 500 Watt ATX Non-Modular Power Supply | $40
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 12/5/3.3V rails matching real rack powering; 500W creates ample headroom for a ~40W - 50W load.
<br> &nbsp;&nbsp; **Sensor:** 3 x Ferwooh ACS712-05B 5A module | (3 pack, using 1) | $7.75
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 185 mV/A sensitivity gives finer resolution per amp than 20A/30A parts.
<br> &nbsp;&nbsp; **Breakout Board:** 1 x MELIFE 24 Pin ATX Breakout | (2 pack, using 1) | $10
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Per-rail screw terminals + built-in switch (handles PS_ON) + per-channel fuses for protection during bring-up.
<br> &nbsp;&nbsp; **Power resistors:** 2 x AISIBO 10Ω 50W aluminum power resistors | $7
<br> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Opted for 50 W resistors for ~29W load to keep them thermally stable and protect measurement integrity.


