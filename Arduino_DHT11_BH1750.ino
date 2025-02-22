#include <Wire.h>
#include <BH1750.h>
#include "DHT.h"
#define DHTPIN 4 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

void setup() {
   Serial.begin(9600);
   Wire.begin();
   lightMeter.begin();
   dht.begin();
}

void loop() {
   float lux = lightMeter.readLightLevel();
   float t = dht.readTemperature();
   float h = dht.readHumidity();
   if (isnan(t) || isnan(h)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
   }
   String payload = "{\"Temp\":" + String(t, 1)
                  + ",\"Humi\":" + String(h, 1)
                  + ",\"Lux\":" + String(lux, 1) + "}";
   Serial.println(payload); 
   delay(1000);
}
