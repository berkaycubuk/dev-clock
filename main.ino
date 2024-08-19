#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHT_PIN 2
#define DHT_TYPE DHT11
#define HC_SR501_PIN 4

int HC_SR501_value = 0;

DHT dht11(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  dht11.begin();

  pinMode(HC_SR501_PIN, INPUT);
}

void loop() {
  float temp = dht11.readTemperature();
  float hum = dht11.readHumidity();

  // Enable backlight if motion detected
  HC_SR501_value = digitalRead(HC_SR501_PIN);
  if (HC_SR501_value == HIGH) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }

  // Temperature
  lcd.setCursor(0,0);
  lcd.print("Sicaklik:");
  lcd.print(temp);

  // Humidity
  lcd.setCursor(0,1);
  lcd.print("Nem:");
  lcd.print(hum);

  delay(5000);
  lcd.clear();
}
