# Arduino Mega Multi-Component Test Kit

A complete electronics diagnostics product built around the Arduino Mega 2560, an ESP32 Wi‑Fi bridge, Supabase cloud storage, and a web dashboard for live monitoring, history, and pass/fail analytics.

This product is designed to test common hobby electronics components, store every test event, and present the results in a professional browser dashboard. It is more than a sensor reader: it is a reusable diagnostics platform that can count how many components were tested, which passed, which failed, and how the device is performing over time.

---

## Product Overview

The Arduino Mega acts as the local hardware test engine. It runs the component tests, shows the status on the OLED, and sends structured results to the ESP32. The ESP32 receives the data over serial, connects to Wi‑Fi, and uploads the test records to Supabase. The web dashboard reads the cloud records and displays summary counts, charts, tables, alerts, and device status.

This design turns the project into a complete product because every test becomes a stored event. That makes it possible to track history, reliability, and test quality instead of only showing the current sensor reading.

---

## System Architecture

```text
+-----------------------+
| Sensors / Outputs     |
| DHT11, MQ-2, LDR,     |
| IR, PIR, Rain, Soil,  |
| Sound, LED, Buzzer,   |
| Servo, HC-SR04, HC-05 |
+-----------+-----------+
            |
            v
+-----------------------+
| Arduino Mega 2560     |
| Local tests + OLED UI |
| Button navigation     |
| Serial test output    |
+-----------+-----------+
            |
            v
+-----------------------+
| ESP32 Wi‑Fi Bridge    |
| Receives serial data  |
| Uploads to Supabase   |
+-----------+-----------+
            |
            v
+-----------------------+
| Supabase Backend      |
| Postgres tables       |
| History + analytics   |
+-----------+-----------+
            |
            v
+-----------------------+
| Web App Dashboard     |
| Counts, charts, logs  |
| Device status cards   |
+-----------------------+
```

---

## Why Arduino Mega

The Arduino Mega 2560 is used because it provides 54 digital I/O pins, 16 analog inputs, and 4 hardware serial ports, which makes it ideal for a large multi-test firmware. It also has dedicated I2C pins on SDA 20 and SCL 21, which lets multiple I2C devices share the same bus cleanly. [web:12][web:14][web:42]

The multiple serial ports are especially useful for a product like this because one serial line can be kept for USB debugging, one for HC-05 Bluetooth, and one for the ESP32 bridge. [web:12][web:14][web:109]

---

## Product Goals

- Test many common components from one device.
- Reduce repeated sketch uploading.
- Display immediate results locally on OLED.
- Upload every test event to the cloud.
- Show counts, pass rate, fail rate, and history in a web app.
- Make the project feel like a complete product, not a lab demo.
- Keep the system expandable for future sensors and dashboards.

---

## Core Features

- OLED menu-driven interface.
- Push-button navigation.
- Bluetooth AT-mode verification.
- Servo sweep testing.
- Ultrasonic live distance testing.
- Basic sensor testing.
- Output device testing.
- ESP32 serial bridge.
- Supabase cloud logging.
- Web dashboard analytics.
- Pass/fail counters.
- Per-device test history.
- Trend charts.
- Search and filter support.

---

## Supported Components

### Core modules
- HC-05 Bluetooth module.
- SG90 servo motor.
- HC-SR04 ultrasonic sensor.

### Sensors
- DHT11 temperature and humidity.
- MQ-2 gas sensor.
- LDR light sensor.
- IR obstacle sensor.
- PIR motion sensor.
- Rain sensor.
- Soil moisture sensor.
- Sound sensor.

### Outputs
- LED.
- Buzzer.
- RGB LED.

### I2C modules
- OLED display.
- BMP280 pressure sensor.
- DS3231 RTC.

---

## Hardware Improvements

| ID | Improvement | Benefit |
|---|---|---|
| H1 | Reset button on Mega RESET pin | Restart without unplugging USB |
| H2 | Capacitive soil sensor | More durable than resistive probe |
| H3 | Logic level shifter for HC-05 | Safer and cleaner serial interface |
| H4 | 100µF decoupling capacitors | Reduces resets during current spikes |
| H5 | 1.3" OLED | Easier to read |
| H6 | 5th button for auto-run mode | Batch testing in one press |
| H7 | Hardware debounce capacitors | Fewer false button triggers |
| H8 | ESP32 via Serial2 | Enables Wi‑Fi upload |

The HC-05 RX pin should not be driven directly from a 5V Arduino TX line because the module logic side is typically 3.3V, so a level shifter or divider is required for safe operation. The HC-05 TX side can be read by the Arduino Mega RX input without a divider in normal use. [web:17][web:23][web:45][web:48]

---

## Firmware Features

| ID | Improvement | Benefit |
|---|---|---|
| F1 | EEPROM saves last menu page | Resume where the user left off |
| F2 | Auto-run all tests | Batch diagnostics |
| F3 | 30-second auto-exit on live tests | Prevents lock-in |
| F4 | Serial mirror for all readings | PC logging |
| F5 | Split sketch into tabs | Easier maintenance |
| F6 | Version string on boot | Firmware traceability |
| F7 | Calibration mode per sensor | Better accuracy |
| F8 | Threshold alerts | OLED and buzzer warnings |
| F9 | Rolling average on analog sensors | Smoother values |
| F10 | JSON serial output | Dashboard-ready data |

---

## Dashboard Features

| ID | Improvement | Benefit |
|---|---|---|
| D1 | Progress bar for timed tests | Better UX |
| D2 | Boot splash screen | Professional startup |
| D3 | Consistent units | Clearer readings |
| D4 | PASS / FAIL badge | Quick diagnosis |
| D5 | Battery indicator | For portable version |

---

## Cloud Stack

### Backend
Supabase is used as the cloud backend because it is a Postgres-based platform with table support and a data API, which is a strong fit for test-event storage and analytics. [web:74][web:75][web:81][web:100]

### Web app
The web app should show:
- total tests run,
- unique components tested,
- passed count,
- failed count,
- warning count,
- recent activity,
- test history,
- device health,
- and charts by component and time.

### Why cloud storage matters
A cloud-backed dashboard is better than SD logging for a complete product because it gives browser access, searchable history, trends, and professional reporting without manual card handling.

---

## Data Model

### Recommended table: `test_events`

| Column | Type | Purpose |
|---|---|---|
| `id` | uuid / bigint | Unique row ID |
| `device_id` | text | Board or product ID |
| `session_id` | text | Test session grouping |
| `component_name` | text | DHT11, MQ-2, etc. |
| `test_name` | text | Specific test action |
| `status` | text | passed, failed, warning |
| `reading_value` | text / numeric | Output value |
| `units` | text | °C, %, cm, hPa |
| `timestamp` | timestamptz | Time of test |
| `notes` | text | Failure or calibration note |

### Dashboard counters
- Total tests = all rows in `test_events`.
- Passed = rows where status is `passed`.
- Failed = rows where status is `failed`.
- Warnings = rows where status is `warning`.
- Components tested = distinct `component_name`.
- Pass rate = passed / total.
- Failure rate = failed / total.

---

## System Data Flow

```text
1. Mega runs a test.
2. Mega creates a result line.
3. Mega sends the line over UART.
4. ESP32 receives the line.
5. ESP32 connects to Wi‑Fi.
6. ESP32 uploads the row to Supabase.
7. Web dashboard reads the database.
8. Dashboard updates counts, charts, and status.
```

---

## Communication Map

### Serial buses

| Port | Pins | Use |
|---|---|---|
| Serial | USB | Debug Monitor |
| Serial1 | 19 RX1, 18 TX1 | HC-05 Bluetooth |
| Serial2 | 17 RX2, 16 TX2 | ESP32 bridge |
| Serial3 | 15 RX3, 14 TX3 | Future reserved |

The Mega’s multiple serial ports make this architecture practical and clean. [web:12][web:14][web:109]

### I2C bus

| Device | Mega Pins |
|---|---|
| OLED | SDA 20, SCL 21 |
| BMP280 | SDA 20, SCL 21 |
| DS3231 | SDA 20, SCL 21 |

Multiple I2C devices can share the same bus as long as their addresses do not conflict. [web:42][web:75][web:101]

Typical addresses:
- OLED: often `0x3C`
- BMP280: `0x76` or `0x77`
- DS3231: commonly `0x68`

---

## Pinout Table

### Buttons

| Button | Mega Pin | Function |
|---|---|---|
| Button 1 | 30 | Test row 1 |
| Button 2 | 32 | Test row 2 |
| Button 3 | 34 | Test row 3 |
| Button 4 | 36 | Next page |
| Button 5 | 38 | Auto-run all tests |

### OLED

| Pin | Mega Pin |
|---|---|
| SDA | 20 |
| SCL | 21 |
| VCC | 5V or 3.3V depending on module |
| GND | GND |

### HC-05

| Pin | Mega Pin | Notes |
|---|---|---|
| TXD | 19 | Direct input |
| RXD | 18 | Level shift required |
| KEY | 22 | AT mode control |
| VCC | 5V | Check module spec |
| GND | GND | Shared ground |

### Servo

| Wire | Mega Pin |
|---|---|
| Signal | 44 |
| VCC | 5V |
| GND | GND |

### HC-SR04

| Pin | Mega Pin |
|---|---|
| TRIG | 40 |
| ECHO | 42 |
| VCC | 5V |
| GND | GND |

### DHT11

| Pin | Mega Pin |
|---|---|
| DATA | 46 |
| VCC | 5V |
| GND | GND |

### MQ-2

| Pin | Mega Pin |
|---|---|
| AOUT | A0 |
| DOUT | 48 |
| VCC | 5V |
| GND | GND |

### LDR

| Wiring | Mega Pin |
|---|---|
| Divider output | A1 |

### IR Sensor

| Pin | Mega Pin |
|---|---|
| OUT | 50 |
| VCC | 5V |
| GND | GND |

### PIR Sensor

| Pin | Mega Pin |
|---|---|
| OUT | 52 |
| VCC | 5V |
| GND | GND |

### Rain Sensor

| Pin | Mega Pin |
|---|---|
| AOUT | A2 |
| DOUT | 53 |
| VCC | 5V |
| GND | GND |

### Soil Moisture

| Pin | Mega Pin |
|---|---|
| AOUT | A3 |
| VCC | 5V |
| GND | GND |

### Sound Sensor

| Pin | Mega Pin |
|---|---|
| AOUT | A4 |
| DOUT | 51 |
| VCC | 5V |
| GND | GND |

### LED

| Connection | Mega Pin |
|---|---|
| Anode through 220Ω | 24 |
| Cathode | GND |

### Buzzer

| Pin | Mega Pin |
|---|---|
| + | 26 |
| - | GND |

### RGB LED

| Color | Mega Pin | Resistor |
|---|---|---|
| Red | 2 | 220Ω |
| Green | 3 | 220Ω |
| Blue | 4 | 220Ω |
| Common cathode | GND | — |

---

## Test Behavior

### One-shot tests
- Servo sweep.
- LED blink.
- Buzzer beep.
- Bluetooth AT command test.
- DHT11 reading test.
- BMP280 reading test.
- Soil moisture reading.
- Rain sensor reading.
- IR and PIR checks.

### Live tests
- HC-SR04 distance mode.
- Sound sensor live mode.
- Optional threshold-monitor modes for MQ-2 and other analog sensors.

### Auto-run mode
The auto-run mode should:
- test all configured components,
- count passes and failures,
- upload every result,
- and produce a final summary.

---

## Summary Cards for Dashboard

The dashboard should show:
- Total tests run.
- Components tested.
- Passed count.
- Failed count.
- Warning count.
- Pass percentage.
- Failure percentage.
- Last tested component.
- Last test timestamp.

---

## Repository Structure

```text
README.md
docs/
firmware/
wiring/
dashboard/
backend/
images/
```

---

## Version Roadmap

### Version 1
- Local Mega-based testing.
- OLED menu.
- Basic sensor support.
- Pass/fail results.
- Serial output.
- ESP32 communication layer.

### Version 2
- Cloud upload to Supabase.
- Live web dashboard.
- Test counters and history.
- Charts and filters.
- Alerts and search.

### Version 3
- Portable enclosure.
- Custom PCB.
- Rotary encoder navigation.
- OTA updates.
- Battery version.
- Productized finish.

---

## Build Philosophy

This project should be treated as a product:
- every test produces a structured record,
- every component has history,
- every device has counts,
- and the dashboard summarizes reliability over time.

That is what makes the system valuable for real use, not just a demo.

---

## Final Notes

The Arduino Mega is the right local controller, the ESP32 is the right connectivity bridge, and Supabase is the right place to store the history and power the dashboard. The HC-05 should be level shifted on the RX line, and the Mega’s multiple hardware serial ports make the system scalable. [web:12][web:17][web:23][web:75][web:100][web:109]

---
