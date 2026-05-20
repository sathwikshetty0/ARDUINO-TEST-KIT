
# Arduino Mega Multi-Component Test Kit
A comprehensive diagnostic platform for testing common hobby electronics, sensors, and output modules using a single Arduino Mega 2560, an OLED menu, and push-button navigation. The project is designed to reduce repetitive sketch uploading by keeping multiple component tests in one firmware image.
## Project Overview
The Arduino Mega Multi-Component Test Kit is a reusable bench tool for embedded systems, robotics, and IoT prototyping. It lets you verify modules one by one from a screen-based menu instead of wiring a separate tester for each part. The project is intentionally built around the Mega because it has enough I/O, memory, and serial interfaces to host many tests in a single sketch. [docs.arduino](https://docs.arduino.cc/hardware/mega-2560/)

This kit started with Bluetooth, servo, and ultrasonic testing, then expanded into a broader system with basic sensors, I2C modules, output devices, logging, and future Wi-Fi integration. The long-term goal is to turn the Mega into a compact electronics validation station that can later grow into SD logging, cloud sync, and dashboard monitoring.
## What This Kit Does
- Tests input sensors.
- Tests output devices.
- Runs live-read modes for selected modules.
- Gives clear pass/fail feedback.
- Supports menu navigation with buttons.
- Prepares the platform for data logging and dashboards.
- Provides a path from simple local testing to connected IoT monitoring.
## System Architecture
```text
                    +----------------------+
                    |   Arduino Mega 2560  |
                    |----------------------|
USB Debug --------->| Serial               |
HC-05 Bluetooth ----| Serial1              |
ESP32 Bridge ------>| Serial2 (future)     |
OLED + I2C Devices ->| SDA 20 / SCL 21     |
SD Card Module ----->| SPI 50/51/52/53     |
Buttons ------------>| Digital Inputs      |
Servo/Sensors ------>| Digital/Analog Pins |
                    +----------------------+
```

The Mega’s hardware serial ports and dedicated I2C pins are especially useful here because they let the project keep debugging, Bluetooth, and future Wi-Fi expansion separate from the sensor bus. [docs.arduino](https://docs.arduino.cc/hardware/mega-2560)
## Feature Set
### Current core features
- OLED-based menu interface.
- Push-button test selection.
- Bluetooth AT-mode test.
- Servo sweep test.
- Ultrasonic live distance test.
- Basic sensor support expansion.
- Serial monitor mirror for diagnostics.
- Designed for multi-page menu navigation.
### Planned features
- SD card logging.
- RTC timestamps.
- Auto-run all tests mode.
- Threshold warnings.
- Rolling average smoothing.
- JSON serial output.
- Flask dashboard.
- ESP32 bridge to cloud services.
- Portable battery version.
- PCB shield version.
## Supported Components
### Core test modules
- HC-05 Bluetooth module.
- SG90 servo motor.
- HC-SR04 ultrasonic sensor.
### Basic sensors
- DHT11 temperature and humidity.
- MQ-2 gas sensor.
- LDR light sensor.
- IR obstacle sensor.
- PIR motion sensor.
- Rain sensor.
- Soil moisture sensor.
- Sound sensor.
### Output devices
- LED.
- Buzzer.
- RGB LED.
### I2C modules
- OLED display.
- BMP280 pressure and temperature sensor.
- DS3231 RTC.
- Optional MPU-6050 in future revisions.
## Hardware Improvements Roadmap
| ID | Improvement | Benefit |
|---|---|---|
| H1 | Reset button on Mega RESET pin | Restart without unplugging USB |
| H2 | Capacitive soil sensor | Better durability than resistive probes |
| H3 | Logic level shifter for HC-05 | Cleaner serial protection |
| H4 | 100µF decoupling capacitors | Reduces resets from current spikes |
| H5 | 1.3" OLED | Easier to read |
| H6 | 5th button for auto-run | Batch diagnostics in one press |
| H7 | Hardware debounce capacitors | Fewer false button presses |
| H8 | ESP32 via Serial2 | Adds Wi-Fi support later |

The HC-05 RX line should be level shifted because the Arduino Mega TX side is 5V logic while the HC-05 logic side is typically 3.3V logic. A divider works, but a level shifter is the cleaner permanent choice. [forum.arduino](https://forum.arduino.cc/t/hc-05-rx-tx-divider-rule/656017)
## Firmware Roadmap
| ID | Improvement | Benefit |
|---|---|---|
| F1 | Save last menu page in EEPROM | Resume where the user left off |
| F2 | Auto-run all tests | Full batch diagnostics |
| F3 | 30-second auto-exit on live feeds | Prevents lock-in |
| F4 | Serial mirror for all readings | Logging and calibration |
| F5 | Split code into tabs | Easier maintenance |
| F6 | Version string on boot screen | Firmware traceability |
| F7 | Calibration mode | Better sensor accuracy |
| F8 | Threshold alerts | OLED flash + buzzer warning |
| F9 | Rolling average smoothing | Cleaner analog values |
| F10 | JSON serial output | Dashboard-ready format |
## Display Roadmap
| ID | Improvement | Benefit |
|---|---|---|
| D1 | Progress bar for timed tests | Clear time feedback |
| D2 | Boot splash with version | Professional startup |
| D3 | Consistent units | Cleaner display text |
| D4 | PASS / FAIL badge | Easy result reading |
| D5 | Battery indicator | Needed for portable version |
## Dashboard Roadmap
| ID | Improvement | Benefit |
|---|---|---|
| W1 | Flask + Serial dashboard | Fastest working web UI |
| W2 | Live Chart.js graphs | Sensor trend visualization |
| W3 | Alert panel | Immediate warnings |
| W4 | CSV download button | Simple export |
| W5 | Dark mode | Better readability |
| W6 | Mobile responsive layout | Phone-friendly UI |
## Data Logging Options
### SD Card logging
Use an SD module on SPI pins 50, 51, 52, and 53 to write sensor readings to CSV files. This is the best offline solution if you want to store sessions without relying on internet access.

**Benefits**
- Offline.
- Cheap.
- Reliable for field use.
- Easy to open on a PC.

**Limits**
- Manual card retrieval.
- No live remote view.
### Cloud logging
If the kit later gains an ESP32 bridge, sensor data can be sent to:
- Supabase.
- Firebase Realtime Database.
- MQTT + InfluxDB + Grafana.

This makes the kit evolve from a standalone tester into a network-connected IoT diagnostics station.
## Communication Design
### Serial buses
| Interface | Use |
|---|---|
| Serial | USB debugging |
| Serial1 | HC-05 Bluetooth |
| Serial2 | ESP32 bridge in future |
| Serial3 | Reserved |
| I2C | OLED, BMP280, RTC, etc. |
| SPI | SD card logging |

The Mega supports multiple serial ports, which makes it ideal for a design that needs separate connections for Bluetooth, debugging, and future networking. [docs.arduino](https://docs.arduino.cc/hardware/mega-2560)
### I2C notes
The Mega’s I2C bus uses SDA on Pin 20 and SCL on Pin 21, and multiple devices can share those lines as long as each device has a unique address. [forum.arduino](https://forum.arduino.cc/t/multiple-devices-on-mega-i2c-bus/1067796)

Typical addresses used in this project:
- OLED: often 0x3C.
- BMP280: 0x76 or 0x77.
- DS3231: commonly 0x68.
- MPU-6050: commonly 0x68.

If DS3231 and MPU-6050 are both used, the address plan must be checked carefully to avoid conflict. [robotsforfun](https://www.robotsforfun.com/webpages/rtc.html)
## Pinout Reference
### Buttons
| Button | Mega Pin | Function |
|---|---|---|
| Button 1 | D30 | Select top item |
| Button 2 | D32 | Select middle item |
| Button 3 | D34 | Select bottom item |
| Button 4 | D36 | Next page |
| Optional Button 5 | D38 | Auto-run all tests |
### OLED
| OLED Pin | Mega Pin |
|---|---|
| SDA | 20 |
| SCL | 21 |
| VCC | 5V or 3.3V depending on module |
| GND | GND |
### HC-05 Bluetooth
| HC-05 Pin | Mega Pin | Notes |
|---|---|---|
| TXD | 19 (RX1) | Direct input |
| RXD | 18 (TX1) | Level shift required |
| KEY | 22 | AT mode control |
| VCC | 5V | Check module spec |
| GND | GND | Shared ground |
### Servo
| Servo Wire | Mega Pin |
|---|---|
| Signal | 44 |
| VCC | 5V |
| GND | GND |
### HC-SR04
| HC-SR04 Pin | Mega Pin |
|---|---|
| TRIG | 40 |
| ECHO | 42 |
| VCC | 5V |
| GND | GND |
### DHT11
| DHT11 Pin | Mega Pin |
|---|---|
| DATA | 46 |
| VCC | 5V |
| GND | GND |
### MQ-2
| MQ-2 Pin | Mega Pin |
|---|---|
| AOUT | A0 |
| DOUT | 48 |
| VCC | 5V |
| GND | GND |
### LDR
| LDR Wiring | Mega Pin |
|---|---|
| Divider output | A1 |

Use a 10kΩ resistor as the fixed side of the divider.
### IR Sensor
| IR Sensor Pin | Mega Pin |
|---|---|
| OUT | 50 |
| VCC | 5V |
| GND | GND |
### PIR Sensor
| PIR Sensor Pin | Mega Pin |
|---|---|
| OUT | 52 |
| VCC | 5V |
| GND | GND |
### Rain Sensor
| Rain Sensor Pin | Mega Pin |
|---|---|
| AOUT | A2 |
| DOUT | 53 |
| VCC | 5V |
| GND | GND |
### Soil Moisture
| Soil Sensor Pin | Mega Pin |
|---|---|
| AOUT | A3 |
| VCC | 5V |
| GND | GND |
### Sound Sensor
| Sound Sensor Pin | Mega Pin |
|---|---|
| AOUT | A4 |
| DOUT | 51 |
| VCC | 5V |
| GND | GND |
### LED
| LED Connection | Mega Pin |
|---|---|
| Anode through 220Ω | 24 |
| Cathode | GND |
### Buzzer
| Buzzer Pin | Mega Pin |
|---|---|
| + | 26 |
| - | GND |
### RGB LED
| RGB Pin | Mega Pin | Resistor |
|---|---|---|
| Red | 2 | 220Ω |
| Green | 3 | 220Ω |
| Blue | 4 | 220Ω |
| Common Cathode | GND | — |
### I2C modules
| Module | Mega Pins |
|---|---|
| BMP280 | SDA 20, SCL 21 |
| DS3231 | SDA 20, SCL 21 |
| MPU-6050 | SDA 20, SCL 21 |
## Wiring Diagram Text View
```text
Arduino Mega 2560
├── OLED I2C
│   ├── SDA -> 20
│   └── SCL -> 21
├── HC-05
│   ├── TXD -> 19
│   ├── RXD -> 18 through level shift
│   ├── KEY -> 22
│   └── VCC/GND
├── Buttons
│   ├── D30 -> Button 1
│   ├── D32 -> Button 2
│   ├── D34 -> Button 3
│   ├── D36 -> NEXT
│   └── D38 -> Auto-run
├── Servo
│   └── Signal -> 44
├── HC-SR04
│   ├── TRIG -> 40
│   └── ECHO -> 42
├── Sensors
│   ├── DHT11 -> 46
│   ├── MQ-2 -> A0 + 48
│   ├── LDR -> A1
│   ├── IR -> 50
│   ├── PIR -> 52
│   ├── Rain -> A2 + 53
│   ├── Soil -> A3
│   └── Sound -> A4 + 51
├── Outputs
│   ├── LED -> 24
│   ├── Buzzer -> 26
│   └── RGB LED -> 2, 3, 4
└── Future
    ├── SD card -> 50/51/52/53 shared SPI
    └── ESP32 -> Serial2
```
## Working logic
### Menu navigation
- The screen shows three test items per page.
- The first three buttons select the test in the visible row.
- The fourth button switches to the next menu page.
- The optional fifth button can trigger auto-run mode.
### Live feed tests
- Ultrasonic distance.
- Sound level.
- Some threshold sensors can run in live mode.
- Press the live-feed button again or wait for auto-exit.
### One-shot tests
- Servo sweep.
- LED blink.
- Buzzer beep.
- Bluetooth AT check.
- DHT, BMP, soil, rain, IR, PIR, MQ-2 checks.
## Power recommendations
- Use USB for coding and small tests.
- Use a regulated 5V supply for full assembly.
- Keep sensor GNDs common.
- Put decoupling capacitors near servo and buzzer branches.
- Do not power a noisy servo directly from a weak USB port if the board resets.
## Suggested libraries
- U8g2 for OLED.
- DHT sensor library.
- Adafruit BMP280.
- Adafruit Unified Sensor.
- Servo.
- Wire.
- SD.
- RTC library for DS3231.
- Optional MPU-6050 library if used later.
## Repository structure
```text
README.md
docs/
firmware/
wiring/
dashboard/
logs/
images/
```
## Version roadmap
### Version 1
- Fully local test kit.
- Stable menu.
- Current pinout.
- Basic sensors.
- Output tests.
- Serial mirror.
- Clean pass/fail behavior.
### Version 2
- SD logging.
- RTC timestamps.
- Calibration.
- JSON output.
- Web dashboard.
- ESP32 bridge.
### Version 3
- Portable battery power.
- Custom PCB.
- Rotary encoder.
- OTA updates.
- Alerts.
- Voice output.
## Project summary
This kit is intended to become a reusable electronics test station that starts simple and grows into a professional-feeling diagnostics platform. It is particularly well suited to student projects, embedded learning, and robotics debugging because it combines sensing, actuation, display, and future logging in one framework.

