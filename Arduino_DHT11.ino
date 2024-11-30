#include "DHT.h"
#define DHTPIN 4 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
   Serial.begin(9600);
   dht.begin();
}

void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature(); 
   if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
   }

   Serial.print("Temp: " + String(t, 1) + "\t"); 
   Serial.println("Humi: " + String(h, 1)); 
   delay(1000);
}