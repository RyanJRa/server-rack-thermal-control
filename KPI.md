# Server Rack KPI Table

**POWER**

| **KPI** | **Target** | **Achieved** | **Reason / Basis** |
| --- | --- | --- | --- |
| ACS712 current accuracy (vs. multimeter) | ±2% |  | ESP32 ADC is nonlinear + noisy, divider resistors add tolerance; ±2% is realistic floor after averaging + calibration. 0.5% rejected as beyond this hardware. |
| PUE-lite | 1.24 → 1.10 |  | (29W load + ~7W fans dumb)/29 ≈ 1.24 baseline; (29W + ~3W tuned)/29 ≈ 1.10.  |

**THERMAL (Pre-build estimates to be refined)**

| **KPI** | **Target** | **Achieved** | **Reason / Basis** |
| --- | --- | --- | --- |
| Steady-state ΔT above ambient | 15°C |  | Enough load to work fans without saturating; refine after enclosure built |
| Overshoot after load step | 2°C |  | Well-tuned target; expect higher early in tuning; closing the gap to 2°C |
| Settling time to setpoint | 30s |  | Balances responsiveness vs. stability; paired with overshoot |
| Setpoint hold (±°C) | ±1°C |  | Achievable given sensor resolution + thermal mass; enables consistent data |

**TELEMETRY**

| **KPI** | **Target** | **Achieved** | **Reason / Basis** |
| --- | --- | --- | --- |
| Sample rate | 1 Hz |  | Above Nyquist for slow thermal signal; no wasted bandwidth |
| Dropped message | ~0% (<1%) |  | Local network near-ideal; tight target catches faults; QoS 1 available |
| Sensor-to-dashboard latency | <200ms |  | Near-real-time fault visibility; grounded in utility ops |
