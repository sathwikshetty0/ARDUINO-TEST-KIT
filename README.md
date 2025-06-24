# ARDUINO-TEST-KIT
TESTING SENSORS AND COMPONENTS



### **Final Pin Connections with HC-SR04**

This is the complete and final pinout for your fully-featured test kit.

| Component | Component Pin | Arduino Mega Pin | Notes |
| :--- | :--- | :--- | :--- |
| **L293D Shield** | --- | Stacks on Mega | |
| **DC Motor** | Wires | Shield **`M1`** Terminals| |
| **External Power** | +/- | Shield **`EXT_PWR`** | **CRITICAL:** 6-12V required. |
| **OLED Display** | SCL / SDA | **Pin 21 / Pin 20** | **MEGA I2C PINS** |
| | VCC / GND | 5V / GND | |
| **Buttons (x4)** | One Side | **30, 32, 34, 36** | Other side of buttons to **GND**. |
| **HC-05 Module** | TXD | **Pin 19** (Mega RX1) | |
| | **RXD** | **Pin 18** (Mega TX1) | **Use a voltage divider.** |
| | KEY/EN | **Pin 22** | |
| | VCC / GND | 5V / GND | |
| **"Safe" Servo** | Signal | **Pin 44** | For the "Safe Servo Test". |
| | Power/GND | 5V / GND | |
| **"Shield" Servo**| Plug | Shield **`SERVO 2`** Header | For the "Shield M1+Servo" test. |
| **HC-SR04 Sensor** | **`Trig`** | **Pin 40** | **NEW COMPONENT** |
| | **`Echo`** | **Pin 42** | |
| | `VCC` / `GND` | `5V` / `GND` | |
