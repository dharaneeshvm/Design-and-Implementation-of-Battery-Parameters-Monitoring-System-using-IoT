#include <LiquidCrystal.h>

#define FLAME_SENSOR_PIN A0  // Flame sensor connected to A0
#define BUZZER_PIN 8         // Buzzer connected to digital pin 8
#define FAN_PIN 9            // Fan connected to digital pin 9

// Define LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 12, 4, 5, 6, 7);

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2); // Initialize 16x2 LCD
    pinMode(FLAME_SENSOR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer pin as output
    pinMode(FAN_PIN, OUTPUT);     // Set fan pin as output

    // Display BMS initializing message on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    delay(2000);  // Display the message for 2 seconds
    lcd.clear();  // Clear the screen after 2 seconds
}

void loop() {
    int flameValue = analogRead(FLAME_SENSOR_PIN);

    // Display on Serial Monitor
    Serial.print("Flame Value: ");
    Serial.println(flameValue);

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Flame Value:");
    lcd.setCursor(0, 1);
    lcd.print(flameValue);

    // Check if flame value is below 300
    if (flameValue < 300) {
        digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
        digitalWrite(FAN_PIN, HIGH);    // Turn on fan
    } else {
        digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
        digitalWrite(FAN_PIN, LOW);     // Turn off fan
    }

    delay(1000); // Adjust as needed
}
