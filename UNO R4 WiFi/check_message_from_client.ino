#include <WiFiS3.h>  // UNO R4 WiFi 전용 WiFi 라이브러리
const char* ssid = "Ria2G";
const char* password = "2026gogo";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  while (!Serial) { } // (필요 시) 시리얼 연결 대기

  //Serial.println("WiFi connecting...");
  while(WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Serial.println("\nWiFi connected!");

  while( WiFi.localIP() == IPAddress(0,0,0,0)){
    delay(200);
  }
  //Serial.print("IP Address: ");
  //Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    //Serial.println("클라이언트 접속");
    while (client.connected()) {
      if (client.available() > 0) {
        Serial.write( client.read() );
      }
    }
    delay(1); // 응답 전송 안정화
    client.stop(); //연결 종료
   // Serial.println("클라이언트 종료");
  }
}
