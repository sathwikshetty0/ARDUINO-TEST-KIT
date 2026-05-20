# Arduino Mega Multi-Component Test Kit — README

> A comprehensive, all-in-one diagnostic tool for testing 17 common hobby electronics and robotics components using a single Arduino Mega 2560, a menu-driven OLED interface, and four push buttons.

---

## Table of Contents

1. [Project Overview](#1-project-overview)
2. [Why Arduino Mega?](#2-why-arduino-mega)
3. [Features & Test List](#3-features--test-list)
4. [Required Hardware](#4-required-hardware)
5. [Required Libraries](#5-required-libraries)
6. [Wiring & Pinout Reference](#6-wiring--pinout-reference)
7. [Menu Navigation System](#7-menu-navigation-system)
8. [Detailed Test Descriptions](#8-detailed-test-descriptions)
9. [Voltage Divider for HC-05](#9-voltage-divider-for-hc-05)
10. [I2C Bus — Multiple Devices](#10-i2c-bus--multiple-devices)
11. [Power Requirements](#11-power-requirements)
12. [Troubleshooting Guide](#12-troubleshooting-guide)
13. [Library Installation Guide](#13-library-installation-guide)

---

## 1. Project Overview

The Arduino Mega Multi-Component Test Kit turns a single Arduino Mega 2560 into a portable diagnostic station for verifying the most common sensors, modules, and output components used in hobby electronics, IoT builds, and robotics projects.

Instead of writing and uploading a new sketch every time you want to test a new sensor or module, this kit gives you a single, permanent firmware that lives on your Mega. Using a compact OLED display and four push buttons, you can scroll through a menu and run a dedicated test for any component in seconds — without touching a computer.

The project is specifically designed for the **Arduino Mega 2560** because of its large flash memory (256KB), abundant GPIO pins (54 digital, 16 analog), and multiple hardware serial ports — making it possible to run 17 independent test routines coexisting in a single sketch.

---

## 2. Why Arduino Mega?

| Constraint | Arduino Uno | Arduino Mega 2560 |
|---|---|---|
| Flash Memory | 32 KB | **256 KB** |
| SRAM | 2 KB | **8 KB** |
| Digital I/O Pins | 14 | **54** |
| Analog Input Pins | 6 | **16** |
| Hardware Serial Ports | 1 (shared with USB) | **4 (Serial, Serial1, Serial2, Serial3)** |
| PWM Pins | 6 | **15** |
| I2C Pins | A4/A5 | **Pin 20 (SDA) / Pin 21 (SCL)** |

Running 17 tests — including multiple I2C devices, hardware serial for Bluetooth, analog sensors, digital sensors, and servo PWM — would exceed the Uno's memory and pin limits. The Mega handles all of this comfortably within a single sketch.

---

## 3. Features & Test List

The Test Kit performs 17 independent diagnostic tests across 6 menu pages:

| Page | Button | Test | Component |
|---|---|---|---|
| **1** | D30 | Advanced Bluetooth | HC-05 (AT command + device name) |
| **1** | D32 | Servo Motor Sweep | SG90 Servo |
| **1** | D34 | Live Ultrasonic Distance | HC-SR04 |
| **2** | D30 | Temperature & Humidity | DHT11 |
| **2** | D32 | Gas / Smoke Level | MQ-2 |
| **2** | D34 | Light Level | LDR |
| **3** | D30 | Obstacle Detection | IR Sensor (FC-51) |
| **3** | D32 | Motion Detection | PIR Sensor (HC-SR501) |
| **3** | D34 | Rainfall Detection | Rain Sensor (YL-83) |
| **4** | D30 | Pressure & Temperature | BMP280 (I2C) |
| **4** | D32 | Gyro & Accelerometer | MPU-6050 (I2C) |
| **4** | D34 | Soil Moisture Level | Soil Moisture Sensor |
| **5** | D30 | Sound Detection | Sound Sensor (KY-038) |
| **5** | D32 | LED Output | Single LED |
| **5** | D34 | Buzzer Output | Active Buzzer |
| **6** | D30 | RGB LED Colors | RGB LED (Common Cathode) |
| **6** | D32 | Soil + Rain Combined | Moisture + Rain comparison |

> **D36 (Pin 36)** is the dedicated **NEXT PAGE** button across all menus.

---

## 4. Required Hardware

| Component | Specification | Quantity |
|---|---|---|
| **Microcontroller** | Arduino Mega 2560 (or compatible) | 1 |
| **Display** | 128×64 I2C OLED — SH1106 or SSD1306 | 1 |
| **Bluetooth Module** | HC-05 | 1 |
| **Servo Motor** | SG90 or any 5V hobby servo | 1 |
| **Ultrasonic Sensor** | HC-SR04 | 1 |
| **Temperature/Humidity** | DHT11 | 1 |
| **Gas Sensor** | MQ-2 | 1 |
| **Light Sensor** | LDR (any value) | 1 |
| **IR Obstacle Sensor** | FC-51 module | 1 |
| **PIR Motion Sensor** | HC-SR501 | 1 |
| **Rain Sensor** | YL-83 module | 1 |
| **Pressure Sensor** | BMP280 (I2C breakout) | 1 |
| **IMU** | MPU-6050 (I2C breakout) | 1 |
| **Soil Moisture Sensor** | Resistive type (2-pin probe) | 1 |
| **Sound Sensor** | KY-038 module | 1 |
| **LED** | Any color, 5mm | 1 |
| **Active Buzzer** | 5V active buzzer | 1 |
| **RGB LED** | Common Cathode, 5mm | 1 |
| **Push Buttons** | Tactile 4-pin, 6×6mm | 5 |
| **Resistors** | 220Ω × 4 (LED/RGB current limiting) | 4 |
| **Resistors** | 10kΩ × 1 (LDR voltage divider) | 1 |
| **Resistors** | 1kΩ + 2kΩ (HC-05 voltage divider) | 1 each |
| **Breadboard** | Full-size or half-size | 1 |
| **Jumper Wires** | Male-to-male and male-to-female | Assorted |
| **USB Cable** | Type-B (for Arduino Mega) | 1 |

---

## 5. Required Libraries

Install all of the following through **Arduino IDE → Sketch → Include Library → Manage Libraries**:

| Library Name | Author | Used For | Install Name |
|---|---|---|---|
| **U8g2** | oliver | OLED Display | `U8g2` |
| **DHT sensor library** | Adafruit | DHT11 sensor | `DHT sensor library` |
| **Adafruit BMP280** | Adafruit | BMP280 pressure sensor | `Adafruit BMP280 Library` |
| **Adafruit Unified Sensor** | Adafruit | Dependency for BMP280 | `Adafruit Unified Sensor` |
| **MPU6050** | Electronic Cats | MPU-6050 IMU | `MPU6050` |
| **Wire** | Built-in | I2C communication | *(pre-installed)* |
| **Servo** | Built-in | Servo motor control | *(pre-installed)* |

> ⚠️ **Important:** Do NOT install the `Adafruit Motor Shield V1` or V2 libraries — they are not needed and will cause conflicts.

---

## 6. Wiring & Pinout Reference

### Push Buttons
All buttons connect from the listed pin to **GND**. Internal pull-up resistors are used (`INPUT_PULLUP`).

| Button | Arduino Mega Pin | Function |
|---|---|---|
| Button 1 | **Pin 30** | Select / Test Row 1 |
| Button 2 | **Pin 32** | Select / Test Row 2 |
| Button 3 | **Pin 34** | Select / Test Row 3 |
| Button 4 | **Pin 36** | NEXT PAGE (menu navigation) |

---

### OLED Display (I2C)

| OLED Pin | Arduino Mega Pin | Notes |
|---|---|---|
| `SCL` | **Pin 21** | Dedicated I2C SCL on Mega |
| `SDA` | **Pin 20** | Dedicated I2C SDA on Mega |
| `VCC` | `3.3V` or `5V` | Check your module's spec |
| `GND` | `GND` | |

---

### HC-05 Bluetooth Module

| HC-05 Pin | Arduino Mega Pin | Notes |
|---|---|---|
| `TXD` | **Pin 19** (RX1) | Direct connection |
| `RXD` | **Pin 18** (TX1) | ⚠️ **MUST use voltage divider** (see Section 9) |
| `KEY / EN` | **Pin 22** | Controlled by code for AT mode |
| `VCC` | `5V` | |
| `GND` | `GND` | |

---

### SG90 Servo Motor

| Servo Wire | Arduino Mega Pin | Notes |
|---|---|---|
| Signal (Orange) | **Pin 44** | Safe PWM pin, no conflicts |
| Power (Red) | `5V` | |
| Ground (Brown) | `GND` | |

---

### HC-SR04 Ultrasonic Sensor

| HC-SR04 Pin | Arduino Mega Pin |
|---|---|
| `TRIG` | **Pin 40** |
| `ECHO` | **Pin 42** |
| `VCC` | `5V` |
| `GND` | `GND` |

---

### DHT11 Temperature & Humidity Sensor

| DHT11 Pin | Arduino Mega Pin |
|---|---|
| `DATA` | **Pin 46** |
| `VCC` | `5V` |
| `GND` | `GND` |

---

### MQ-2 Gas Sensor

| MQ-2 Pin | Arduino Mega Pin | Notes |
|---|---|---|
| `AOUT` | **A0** | Analog reading |
| `DOUT` | **Pin 48** | Digital threshold output |
| `VCC` | `5V` | |
| `GND` | `GND` | |

> ⚠️ Allow **3-5 minutes** warm-up time before the MQ-2 gives accurate readings.

---

### LDR (Light Dependent Resistor)

Wire as a voltage divider: `5V → LDR → A1 → 10kΩ → GND`

| Connection | Arduino Mega Pin |
|---|---|
| Middle of voltage divider | **A1** |

---

### IR Obstacle Sensor (FC-51)

| IR Sensor Pin | Arduino Mega Pin |
|---|---|
| `OUT` | **Pin 50** |
| `VCC` | `5V` |
| `GND` | `GND` |

---

### PIR Motion Sensor (HC-SR501)

| PIR Pin | Arduino Mega Pin |
|---|---|
| `OUT` | **Pin 52** |
| `VCC` | `5V` |
| `GND` | `GND` |

> ⚠️ Allow **30–60 seconds** warm-up time after powering on before testing. This is normal for PIR sensors.

---

### Rain Sensor (YL-83)

| Rain Sensor Pin | Arduino Mega Pin | Notes |
|---|---|---|
| `AOUT` | **A2** | Analog level reading |
| `DOUT` | **Pin 53** | Digital wet/dry output |
| `VCC` | `5V` | |
| `GND` | `GND` | |

---

### BMP280 (I2C — Pressure & Temperature)

| BMP280 Pin | Arduino Mega Pin | Notes |
|---|---|---|
| `SCL` | **Pin 21** | Shared I2C bus |
| `SDA` | **Pin 20** | Shared I2C bus |
| `VCC` | `3.3V` | Most breakouts are 3.3V |
| `GND` | `GND` | |

> Default I2C address: `0x76`. If unresponsive, try `0x77`.

---

### MPU-6050 (I2C — Gyro & Accelerometer)

| MPU-6050 Pin | Arduino Mega Pin | Notes |
|---|---|---|
| `SCL` | **Pin 21** | Shared I2C bus |
| `SDA` | **Pin 20** | Shared I2C bus |
| `VCC` | `3.3V` or `5V` | Most breakouts accept both |
| `GND` | `GND` | |
| `AD0` | `GND` | Sets I2C address to `0x68` |

---

### Soil Moisture Sensor

| Soil Sensor Pin | Arduino Mega Pin |
|---|---|
| `AOUT` | **A3** |
| `VCC` | `5V` |
| `GND` | `GND` |

---

### Sound Sensor (KY-038)

| KY-038 Pin | Arduino Mega Pin | Notes |
|---|---|---|
| `AOUT` | **A4** | Analog level |
| `DOUT` | **Pin 51** | Digital threshold |
| `VCC` | `5V` | |
| `GND` | `GND` | |

---

### LED (Single)

Connect: `Pin 24 → 220Ω Resistor → LED Anode (+) → LED Cathode (-) → GND`

| Connection | Arduino Mega Pin |
|---|---|
| LED (via 220Ω) | **Pin 24** |

---

### Active Buzzer

| Buzzer Pin | Arduino Mega Pin |
|---|---|
| `+` (positive) | **Pin 26** |
| `-` (negative) | `GND` |

---

### RGB LED (Common Cathode)

| RGB Pin | Arduino Mega Pin | Resistor |
|---|---|---|
| Red anode | **Pin 2** | 220Ω |
| Green anode | **Pin 3** | 220Ω |
| Blue anode | **Pin 4** | 220Ω |
| Common Cathode | `GND` | — |

---

## 7. Menu Navigation System

The OLED displays 3 tests per page. Use the buttons as follows:

```
┌─────────────────────────────┐
│   Page 1 / 6                │
│ > D30: Adv. Bluetooth       │
│ > D32: Servo Motor          │
│ > D34: Ultrasonic Live      │
│   [D36: NEXT PAGE →]        │
└─────────────────────────────┘
```

| Action | Button | Pin |
|---|---|---|
| Run top test | Button 1 | Pin 30 |
| Run middle test | Button 2 | Pin 32 |
| Run bottom test | Button 3 | Pin 34 |
| Go to next page | Button 4 (NEXT) | Pin 36 |
| Wraps back to Page 1 after Page 6 | Button 4 | Pin 36 |

- Press the **same button** again during a **Live Feed** test (e.g., Ultrasonic, Sound) to **exit** back to the menu.
- All other tests run automatically and return to the menu when done.

---

## 8. Detailed Test Descriptions

### Page 1

**D30 — Advanced Bluetooth (HC-05)**
Pulls KEY pin HIGH to enter AT command mode, sends `AT` to verify connection, then queries `AT+NAME?` to retrieve and display the device name on the OLED. Pass condition: receives valid `OK` response within timeout.

**D32 — Servo Motor Sweep (SG90 on Pin 44)**
Attaches servo to Pin 44 and performs a full sweep: `0° → 180° → 0° → 90° → 0°`. Detaches cleanly after test. Pass condition: completes full sweep without jitter.

**D34 — Live Ultrasonic Distance (HC-SR04)**
Enters a live loop firing the TRIG pulse and measuring ECHO duration. Displays real-time distance in centimeters in large font. Handles out-of-range as `> 400 cm`. Exit by pressing D34 again.

---

### Page 2

**D30 — Temperature & Humidity (DHT11)**
Reads temperature (°C) and relative humidity (%) from the DHT11. Displays both values simultaneously on the OLED. Shows `Sensor Error` if the module is disconnected or faulty.

**D32 — Gas / Smoke Level (MQ-2)**
Reads the analog output from the MQ-2 and maps it to a 0–100% concentration scale. Also reads the digital threshold pin to display `GAS DETECTED` or `AIR CLEAR` status.

**D34 — Light Level (LDR)**
Reads analog voltage from the LDR voltage divider and displays a mapped lux approximation and a descriptive label: `DARK`, `DIM`, `BRIGHT`, or `VERY BRIGHT`.

---

### Page 3

**D30 — Obstacle Detection (IR Sensor FC-51)**
Reads the digital output from the FC-51 module. Displays `OBSTACLE` or `CLEAR` on the OLED in large text. Runs as a live feed for 10 seconds then returns to menu.

**D32 — Motion Detection (PIR HC-SR501)**
Monitors the PIR output for 15 seconds. Displays `MOTION!` in large text when triggered, otherwise shows `Waiting...`. Exits automatically after the timeout.

**D34 — Rainfall Detection (YL-83)**
Reads both analog level and digital threshold from the rain sensor. Displays percentage wetness and status: `DRY`, `DRIZZLE`, `RAIN`, or `HEAVY RAIN`.

---

### Page 4

**D30 — Pressure & Temperature (BMP280 I2C)**
Initializes the BMP280 on the I2C bus and reads barometric pressure (hPa) and temperature (°C). Displays both on OLED. Shows `BMP280 NOT FOUND` if not detected.

**D32 — Gyroscope & Accelerometer (MPU-6050 I2C)**
Reads raw accelerometer (X, Y, Z) values from the MPU-6050. Displays all three axes on the OLED. Useful for verifying the sensor is live and responding.

**D34 — Soil Moisture Level**
Reads the analog output from the soil probe and maps it to a 0–100% moisture percentage. Displays percentage and label: `DRY`, `MOIST`, or `WET`.

---

### Page 5

**D30 — Sound Detection (KY-038)**
Enters a live feed monitoring the analog sound level. Displays a live bar graph and dB-approximate value. `LOUD` flashes when the digital threshold is crossed. Press D30 again to exit.

**D32 — LED Output Test**
Blinks the LED on Pin 24 five times with 500ms intervals to confirm digital output is working. Displays `LED BLINKING...` on OLED during test.

**D34 — Buzzer Output Test**
Activates the buzzer on Pin 26 with three short beeps (200ms on / 200ms off). Confirms the buzzer and digital output pin are functional.

---

### Page 6

**D30 — RGB LED Color Test**
Cycles through Red → Green → Blue → Yellow → Cyan → Magenta → White → Off. Each color held for 1 second. Displays the current color name on OLED.

**D32 — Soil + Rain Combined View**
Reads both soil moisture (A3) and rain sensor (A2) simultaneously and displays them side by side on the OLED. Useful for comparing environmental moisture sources.

---

## 9. Voltage Divider for HC-05

The HC-05 module's `RXD` pin is **3.3V logic** only. The Arduino Mega TX1 (Pin 18) outputs 5V logic. Connecting them directly will damage the HC-05 over time. A simple resistor voltage divider must be used:

```
Pin 18 (TX1) ──── 1kΩ ────┬──── HC-05 RXD
                           │
                          2kΩ
                           │
                          GND
```

The junction between the 1kΩ and 2kΩ resistors gives approximately:

> V_out = 5V × (2kΩ / (1kΩ + 2kΩ)) = **3.33V** ✅

This is safe for the HC-05 RXD pin.

> The HC-05 `TXD` → Mega `RX1` direction is fine without a divider because 3.3V HIGH is correctly read as HIGH by the Mega's 5V logic input.

---

## 10. I2C Bus — Multiple Devices

Three I2C devices share the same bus on the Mega (Pin 20 SDA, Pin 21 SCL):

| Device | I2C Address | Notes |
|---|---|---|
| OLED (SH1106) | `0x3C` | Default for most modules |
| BMP280 | `0x76` | Try `0x77` if undetected |
| MPU-6050 | `0x68` | AD0 pin tied to GND |

All three addresses are different, so they coexist on the same two-wire bus without any additional configuration. All four devices (including the display) can run simultaneously.

> If you ever need to find an I2C device address, run the standard **I2C Scanner sketch** from Arduino IDE examples.

---

## 11. Power Requirements

| Source | Powers | Notes |
|---|---|---|
| USB (5V from PC) | Arduino Mega, all sensors, OLED, LEDs, servo (light load) | Sufficient for testing most components individually |
| External 5V adapter (2A+) | Same as above, recommended for full system | Better stability when buzzer, servo, and sensors run simultaneously |

> No external motor supply is needed in this version — the motor shield has been removed.

> ⚠️ If the Mega resets during a servo sweep, the USB port cannot supply enough current. Use a dedicated 5V/2A adapter via the barrel jack.

---

## 12. Troubleshooting Guide

| Symptom | Likely Cause | Fix |
|---|---|---|
| OLED stays blank | Wrong I2C address or loose wire | Check SDA→Pin 20, SCL→Pin 21. Run I2C scanner |
| HC-05 test fails | Not in AT mode / baud rate mismatch | Ensure KEY pin is HIGH before power. Try `AT+NAME` without `?` |
| Servo jitters or resets board | Insufficient current from USB | Use 5V/2A external adapter |
| DHT11 shows `Sensor Error` | Bad connection or missing pull-up | Add 10kΩ pull-up resistor on DATA line to 5V |
| MQ-2 reads always high | No warm-up time | Wait 3–5 minutes after powering on |
| PIR triggers immediately | Warm-up not complete | Wait 60 seconds after power-on |
| BMP280 not found | Wrong I2C address | Change from `0x76` to `0x77` in code |
| MPU-6050 not found | AD0 not grounded | Connect AD0 pin to GND |
| LDR reads 0 always | Missing 10kΩ pull-down resistor | Add 10kΩ from A1 to GND |
| Rain sensor always wet | Probe contaminated or shorted | Clean probe with dry cloth |
| Buttons not responding | Missing GND connection | Ensure button connects pin to GND (not 5V) |
| Compilation error: `AFMotor.h` | Old code version with motor shield | Confirm you are using the updated no-shield sketch |

---

## 13. Library Installation Guide

1. Open **Arduino IDE**
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search and install each library below:

| Search Term | Select This Result |
|---|---|
| `U8g2` | `U8g2` by oliver |
| `DHT sensor` | `DHT sensor library` by Adafruit |
| `BMP280` | `Adafruit BMP280 Library` by Adafruit |
| `Unified Sensor` | `Adafruit Unified Sensor` by Adafruit |
| `MPU6050` | `MPU6050` by Electronic Cats |

> The `Wire` and `Servo` libraries ship with the Arduino IDE and do not need to be installed separately.

---

*Project: Arduino Mega Multi-Component Test Kit | Version 2.0 | Updated May 2026*
