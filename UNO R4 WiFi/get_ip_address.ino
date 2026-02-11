#include <WiFiS3.h>  // UNO R4 WiFi 전용 WiFi 라이브러리
const char* ssid = "Home2G";
const char* password = "730124go";
void setup() {
  Serial.begin(115200);
  while (!Serial) { } // (필요 시) 시리얼 연결 대기

  Serial.println("WiFi connecting...");
  // WiFi 연결 시도 (DHCP로 IP 자동 할당)
  // 연결될 때까지 지속적으로 접속 시도
  while(WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // 정상적인 IP 주소를 받아올 때까지 대기
  while( WiFi.localIP() == IPAddress(0,0,0,0)){
    delay(200);
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 필요하면 주기적으로 상태 확인
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected!");
    delay(1000);
  }
}
