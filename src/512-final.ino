#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_VEML7700.h"

Adafruit_BME280 bme;
Adafruit_SSD1306 display(0x78);
Adafruit_VEML7700 veml;

float pressure;
float temp;
float lux;

int buzzerPin = 3; // 将蜂鸣器连接到数字引脚 D2

void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("Serial communication initialized.");

  // Assuming BME280 is connected and functional
  if (!bme.begin()) {
    Serial.println("BME280 sensor not found. Check wiring!");
    while (1);
  } else {
    Serial.println("BME280 sensor found!");
  }

  // Initialize VEML7700
  Serial.println("Initializing VEML7700...");
  if (!veml.begin()) {
    Serial.println("VEML7700 sensor not found. Check wiring!");
    while (1);
  } else {
    Serial.println("VEML7700 sensor found!");
  }

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);

  // Initialize display
  Serial.println("Initializing display...");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 initialization failed!");
    while (1);
  } else {
    Serial.println("SSD1306 initialized successfully!");
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  Serial.println("Setup completed.");
}

void loop() {
  // Read BME280 data
  temp = bme.readTemperature();      // Read temperature from BME280
  pressure = bme.readPressure() / 100.0F; // Read pressure from BME280
  lux = veml.readLux();
  Serial.print("Lux: ");
  Serial.println(lux);

  // Display data on the screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Pressure: ");
  display.print(pressure);
  display.println(" hPa");
  display.print("Temperature: ");
  display.print(temp);
  display.println(" C");
  display.print("Lux: ");
  display.print(lux);
  display.println(" lux");
  display.display();

  // Output sensor data to the serial monitor
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.println(" lux");

  // If lux is greater than 50, trigger the buzzer
  if (lux > 50.0) {
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    Serial.println("Buzzer should be ON");
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    Serial.println("Buzzer should be OFF");
  }

  delay(1000);
}
