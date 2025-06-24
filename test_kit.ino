// --- FINAL COMPLETE TEST KIT FOR ARDUINO MEGA ---
// Includes: Your preferred Bluetooth, Servo, and Motor tests, plus the new HC-SR04 test.

#include <Wire.h>
#include <U8g2lib.h>
#include <Servo.h>
#include <AFMotor.h> 
#include <string.h>

// --- OLED DISPLAY CONFIGURATION ---
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// --- PIN DEFINITIONS FOR ARDUINO MEGA ---
const int BTN_BLUETOOTH_TEST = 30;
const int BTN_SAFE_SERVO_TEST = 32;
const int BTN_SHIELD_TEST = 34;
const int BTN_ULTRASONIC_TEST = 36; // NEW: Button for Ultrasonic Test

// Using Mega's Hardware Serial1 port (Pins 18, 19) for reliable Bluetooth communication
const int HC05_KEY_PIN = 22;

const int SAFE_SERVO_PIN = 44;      // Safe pin for the normal servo test
const int SHIELD_SERVO_PIN = 9;       // Pin for the on-shield SERVO 2 port

// NEW: Pins for the HC-SR04 Sensor
const int ULTRASONIC_TRIG_PIN = 40;
const int ULTRASONIC_ECHO_PIN = 42;

// --- GLOBAL OBJECTS ---
Servo testServo;
AF_DCMotor motor1(1); 
long lastButtonPressTime = 0;
const long DEBOUNCE_DELAY = 150;

// --- FUNCTION PROTOTYPES ---
void displayMainMenu();
void displayMessage(const char *title, const char *message, int delayMs = 2000);
void testBluetooth_GetName();
void testSafeServo();
void testMotorShield();
void testUltrasonicSensor(); // NEW


// --- MAIN SETUP ---
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println(F("\n--- Final Test Kit (All Functions) ---"));

  u8g2.begin();
  
  pinMode(BTN_BLUETOOTH_TEST, INPUT_PULLUP);
  pinMode(BTN_SAFE_SERVO_TEST, INPUT_PULLUP);
  pinMode(BTN_SHIELD_TEST, INPUT_PULLUP);
  pinMode(BTN_ULTRASONIC_TEST, INPUT_PULLUP); // NEW

  pinMode(HC05_KEY_PIN, OUTPUT);
  digitalWrite(HC05_KEY_PIN, LOW);
  
  // NEW: Setup pins for HC-SR04
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  
  motor1.setSpeed(0);
  motor1.run(RELEASE);

  displayMainMenu();
}

// --- MAIN LOOP ---
void loop() {
  if (millis() - lastButtonPressTime > DEBOUNCE_DELAY) {
    if (digitalRead(BTN_BLUETOOTH_TEST) == LOW) {
      lastButtonPressTime = millis();
      testBluetooth_GetName();
      displayMainMenu();
    } 
    else if (digitalRead(BTN_SAFE_SERVO_TEST) == LOW) {
      lastButtonPressTime = millis();
      testSafeServo();
      displayMainMenu();
    }
    else if (digitalRead(BTN_SHIELD_TEST) == LOW) {
      lastButtonPressTime = millis();
      testMotorShield();
      displayMainMenu();
    }
    else if (digitalRead(BTN_ULTRASONIC_TEST) == LOW) { // NEW
      lastButtonPressTime = millis();
      testUltrasonicSensor();
      displayMainMenu();
    }
  }
}

// --- TEST FUNCTIONS ---

// Test 1: Your preferred Bluetooth Test
void testBluetooth_GetName() {
  if(testServo.attached()) { testServo.detach(); }
  displayMessage("Testing:", "HC-05 Module...", 1000);
  digitalWrite(HC05_KEY_PIN, HIGH);
  delay(500);
  Serial1.begin(38400);
  delay(500);
  while(Serial1.available()) { Serial1.read(); }
  Serial.println(F("Sending: AT"));
  Serial1.print("AT\r\n");
  String response = Serial1.readStringUntil('\n');
  response.trim();
  Serial.print(F("Received: ")); Serial.println(response);
  if (response.indexOf("OK") != -1) {
    displayMessage("Connection OK!", "Getting name...", 1000);
    while(Serial1.available()) { Serial1.read(); }
    Serial.println(F("Sending: AT+NAME?"));
    Serial1.print("AT+NAME?\r\n");
    response = Serial1.readStringUntil('\n');
    response.trim();
    Serial.print(F("Received: ")); Serial.println(response);
    if (response.startsWith("+NAME:")) {
      String deviceName = response.substring(response.indexOf(':') + 1);
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_ncenB08_tr); u8g2.drawStr(0, 12, "BT Name Found:");
        u8g2.setFont(u8g2_font_logisoso16_tr); u8g2.drawStr(0, 40, deviceName.c_str());
      } while (u8g2.nextPage());
      delay(4000);
    } else {
      displayMessage("Error:", "Could not get name", 3000);
    }
  } else {
    displayMessage("Result: FAILED", "No 'OK' response", 3000);
  }
  digitalWrite(HC05_KEY_PIN, LOW);
  Serial1.begin(9600);
}

// Test 2: Your preferred Normal Servo Test
void testSafeServo() {
  motor1.run(RELEASE);
  displayMessage("Testing:", "Servo on Pin 44...", 1000);
  testServo.attach(SAFE_SERVO_PIN);
  delay(50);
  testServo.write(0);   delay(1000);
  testServo.write(180); delay(1000);
  testServo.write(0);  delay(1000);
  testServo.write(90); delay(1000);
  testServo.write(0);  delay(1000);
  testServo.detach();
  displayMessage("Result: PASSED", "Servo Test Complete!", 2000);
}

// Test 3: Your preferred Motor Shield Test (Motor + On-Shield Servo)
void testMotorShield() {
  displayMessage("Shield Exp.:", "Motor then Servo", 2000);
  displayMessage("Motor Test:", "Running Motor...", 2000);
  motor1.setSpeed(200);
  motor1.run(FORWARD);
  delay(2000);
  motor1.run(RELEASE);
  displayMessage("Motor Test:", "Running BACKWARDS", 2000);
  delay(1000);
  motor1.run(BACKWARD);
  delay(2000);
  motor1.run(RELEASE);
  displayMessage("Result: PASSED", "Motor Test Complete!", 2000);
  displayMessage("Servo Test:", "On Shield Pin 9", 1500);
  testServo.attach(SHIELD_SERVO_PIN);
  delay(500);
  testServo.write(0);   delay(1500);
  testServo.write(180); delay(1500);
  testServo.write(0);   delay(1500);
  testServo.write(90);  delay(1500);
  testServo.detach();
  displayMessage("Result:", "Experiment Complete", 2000);
}

// Test 4: NEW Ultrasonic Sensor Test
void testUltrasonicSensor() {
  // Display initial instructions
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_7x13_tr);
    u8g2.drawStr(5, 30, "Live Distance Test");
    u8g2.drawStr(5, 50, "Press button again to exit");
  } while(u8g2.nextPage());
  
  delay(2000); // Wait for user to read instructions
  
  // Wait for the button to be released before starting the loop
  while(digitalRead(BTN_ULTRASONIC_TEST) == LOW) { }
  delay(100);

  // Loop continuously until the button is pressed again
  while(digitalRead(BTN_ULTRASONIC_TEST) == HIGH) {
    // Send the trigger pulse
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    // Read the echo pulse duration
    long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, 25000); // 25ms timeout

    // Calculate the distance in centimeters
    int distance = duration * 0.034 / 2;

    // Prepare the result string
    char buffer[15];
    if (distance == 0) {
      sprintf(buffer, "> 400 cm"); // Out of range
    } else {
      sprintf(buffer, "%d cm", distance);
    }

    // Display the real-time distance on the OLED
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB10_tr);
      u8g2.drawStr(0, 15, "Distance:");
      u8g2.setFont(u8g2_font_logisoso24_tr); // Use a large font
      u8g2.drawStr(10, 55, buffer);
    } while (u8g2.nextPage());
    
    Serial.println(buffer); // Also print to Serial Monitor for debugging
    delay(100); // Small delay between readings
  }
  
  // A final debounce after exiting the loop
  delay(200);
}

// --- DISPLAY UTILITY FUNCTIONS ---
void displayMainMenu() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr); 
    u8g2.drawStr(0, 10, "Final Test Kit Menu");
    u8g2.drawStr(0, 25, "D30: Adv. Bluetooth");
    u8g2.drawStr(0, 37, "D32: Safe Servo (P44)");
    u8g2.drawStr(0, 49, "D34: Shield M1+Servo");
    u8g2.drawStr(0, 61, "D36: Ultrasonic Test"); // NEW
  } while (u8g2.nextPage());
}

void displayMessage(const char *title, const char *message, int delayMs) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(2, 12, title);
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(2, 35, message);
  } while (u8g2.nextPage());
  delay(delayMs);
}