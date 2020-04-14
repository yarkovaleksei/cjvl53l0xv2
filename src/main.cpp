#include <Arduino.h>
#include <Adafruit_VL53L0X.h>

#define PIN_RELAY 13

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);

  while (!Serial) {
    delay(1);
  }

  if (!sensor.begin()) {
    Serial.println(F("Не загружен VL53L0X"));
    while(1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  sensor.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    Serial.print(F("Расстояние: "));
    Serial.print(measure.RangeMilliMeter);
    Serial.println(F(" мм"));
  } else {
    Serial.println(F("Очень далеко"));
  }

  if (measure.RangeMilliMeter < 450) {
    digitalWrite(PIN_RELAY, HIGH);
  } else {
    digitalWrite(PIN_RELAY, LOW);
  }

  delay(100);
}