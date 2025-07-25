
# Arduino Mega Multi-Component Test Kit

## Overview

This project turns an Arduino Mega into a comprehensive, all-in-one diagnostic tool for testing the most common components used in hobby electronics and robotics projects. Using a simple menu-driven interface on an OLED display and push buttons, you can quickly verify the functionality of various modules without needing to write a new sketch for each part.

This Test Kit was specifically designed for the Arduino Mega to overcome the memory and pin limitations of smaller boards like the Arduino Uno, allowing all test functionalities to coexist in a single, robust program.

## Features

The Test Kit can perform independent tests for the following components:

* **HC-05 Bluetooth Module:** Automatically enters AT command mode and verifies a successful connection.
* **Standard Servo Motor:** Sweeps the servo through its full range of motion on a safe, non-conflicting pin.
* **Adafruit Motor Shield V1:** Drives a DC motor forward and backward to confirm the shield is working.
* **HC-SR04 Ultrasonic Sensor:** Provides a live feed of the measured distance, which you can use to see the sensor working in real-time.
## Required Hardware

* **Microcontroller:** 1 x Arduino Mega 2560 (or compatible)
* **Display:** 1 x 128x64 I2C OLED Display (SH1106 or SSD1306)
* **Motor Driver:** 1 x Adafruit Motor Shield V1 (or compatible L293D-based shield)
* **Bluetooth:** 1 x HC-05 Bluetooth Module
* **Servo:** 1 x SG90 or similar 5V Hobby Servo Motor
* **Sensor:** 1 x HC-SR04 Ultrasonic Distance Sensor
* **Motor:** 1 x Standard DC Hobby Motor
* **Input:** 4 x Tactile Push Buttons
* **Power:**
    * 1 x 5V Power Source for the Arduino Mega (USB cable or wall adapter)
    * 1 x **External 6V-12V Power Supply** (e.g., 4xAA battery pack, 9V battery, or DC adapter) for the motor shield.
* **Misc:**
    * 1 x Breadboard
    * Assorted Jumper Wires
    * 1 x 1kΩ Resistor and 1 x 2kΩ Resistor (for the HC-05 voltage divider)

## Software & Libraries

1.  **Arduino IDE:** The latest version is recommended.
2.  **Libraries:** You will need to install the following libraries through the Arduino IDE's Library Manager (`Sketch > Include Library > Manage Libraries...`):
    * **`U8g2` by oliver:** The library for the OLED display.
    * **`Adafruit Motor Shield V1` by Adafruit:** The library for the motor driver (`AFMotor.h`). *Note: Do not install the V2 library by mistake.*
    * The `<Wire.h>` and `<Servo.h>` libraries are usually included with the Arduino IDE.

## Wiring Instructions (Pinout)

**Step 1:** Gently stack the Motor Shield on top of your Arduino Mega.
**Step 2:** Connect the external 6V-12V power supply to the blue `EXT_PWR` terminals on the shield.
**Step 3:** Connect all other components to the Arduino Mega pins as described below.

| Component | Component Pin | Arduino Mega Pin | Notes |
| :--- | :--- | :--- | :--- |
| **DC Motor** | Wires | Shield **`M1`** Terminals| |
| **OLED Display** | `SCL` / `SDA` | **Pin 21 / Pin 20** | **CRITICAL:** The Mega uses these dedicated I2C pins. |
| | `VCC` / `GND` | `5V` / `GND` | |
| **Buttons (x4)** | One side | **Pin 30** (Bluetooth) | Connect the other side of all four buttons to a common **GND**. |
| | One side | **Pin 32** (Servo) | |
| | One side | **Pin 34** (Motor) | |
| | One side | **Pin 36** (Ultrasonic) | |
| **HC-05 Module** | `TXD` | **Pin 19** (Mega RX1) | Using reliable Hardware `Serial1` port. |
| | **`RXD`** | **Pin 18** (Mega TX1) | **MUST use a voltage divider** between this pin and the HC-05. |
| | `KEY`/`EN` | **Pin 22** | Allows the code to enter AT mode automatically. |
| | `VCC` / `GND` | `5V` / `GND` | |
| **Servo Motor** | Signal | **Pin 44** | This is a "safe" pin that does not conflict with the motor shield. |
| | Power/GND | `5V` / `GND` | Do **not** use the on-shield servo ports. |
| **HC-SR04 Sensor** | **`Trig`** | **Pin 40** | |
| | **`Echo`** | **Pin 42** | |
| | `VCC` / `GND` | `5V` / `GND` | |

## How to Use

1.  Assemble the hardware according to the wiring diagram above.
2.  Upload the final, complete sketch to your Arduino Mega.
3.  Power on the Mega via USB and connect the external power to the motor shield.
4.  The OLED screen will display the main menu with four options.
5.  Press the corresponding button to run the desired test.

### Description of Tests

* **D30: Bluetooth:** This will automatically put the HC-05 into AT mode and display "PASSED" if it gets a valid "OK" response.
* **D32: Servo (Pin 44):** This will sweep the servo connected to Pin 44 from 0 to 180 degrees and back, proving it works.
* **D34: DC Motor:** This will run the DC motor connected to the M1 port forward for 2 seconds, then backward for 2 seconds.
* **D36: Live Distance:** This will enter a "live feed" mode, continuously showing the distance measured by the HC-SR04 sensor. You can move your hand in front of it to see the values change. **Press the same button again to exit the test** and return to the main menu.
