#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
const char* ssid     = "Home2G";
const char* password = "730124go";
WiFiUDP udp;

const long utcOffsetSeconds = 9L * 3600L;
const unsigned long updateIntervalMs = 60UL * 1000UL; // 60초
NTPClient timeClient(udp, "kr.pool.ntp.org", utcOffsetSeconds, updateIntervalMs);

void setup() {
  Serial.begin(115200);
  while (!Serial) { } // (필요 시) 시리얼 연결 대기

  Serial.println("WiFi connecting...");
  while(WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  while(WiFi.localIP()==IPAddress(0,0,0,0)){delay(200);}
  timeClient.begin();
}

void loop() {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime()); // "HH:MM:SS"
  delay(1000);
}
