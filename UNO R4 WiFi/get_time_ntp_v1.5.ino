#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const char* ssid     = "Home2G";
const char* password = "730124go";

// UDP + NTPClient
WiFiUDP ntpUDP;

// 한국(KST) = UTC + 9시간 => 9*3600
const long utcOffsetSeconds = 9L * 3600L;

// 업데이트 주기(밀리초) - 너무 자주 갱신하지 않는 게 좋습니다.
const unsigned long updateIntervalMs = 60UL * 1000UL; // 60초
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetSeconds, updateIntervalMs);

void setup() {
  Serial.begin(115200);
  while (!Serial) { } // (필요 시) 시리얼 연결 대기

  Serial.println("WiFi connecting...");
  while(WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  
  while( WiFi.localIP() == IPAddress(0,0,0,0)){
    delay(200);
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // NTP 시작
  timeClient.begin();

  // 처음엔 강제로 1회 동기화 시도
  Serial.println("Syncing NTP...");
  if (!timeClient.forceUpdate()) {
    Serial.println("NTP sync failed (try again / check network).");
  }
}

void loop() {
  timeClient.update();  // updateIntervalMs에 따라 필요 시 동기화

  Serial.print("KST Time: ");
  Serial.println(timeClient.getFormattedTime()); // "HH:MM:SS"

  delay(1000);
}


