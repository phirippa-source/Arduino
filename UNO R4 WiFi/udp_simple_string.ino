#include <WiFiS3.h>
#include <WiFiUdp.h>

const char* ssid = "Ria2G";
const char* pass = "2026gogo";

IPAddress PC_IP(192, 168, 1, 2);   // <-- PC IPv4로 변경
const uint16_t PC_PORT = 5005;      // <-- PC가 받을 포트

WiFiUDP udp;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }
  // 정상적인 IP 주소를 받아올 때까지 대기
  while( WiFi.localIP() == IPAddress(0,0,0,0)){
    delay(100);
  }
  Serial.print("Arduino IP: ");
  Serial.println(WiFi.localIP());

  // 송신만 해도 되지만, 소스 포트를 고정하고 싶으면 begin() 해두면 좋아.
  udp.begin(12345);
}

void loop() {
  // 테스트용 문자열 (끝에 \n 붙이면 로그 보기 편함)
  String msg = "hello, udp string! " + String( millis()/1000 ) + "[s]\n";

  udp.beginPacket(PC_IP, PC_PORT);
  udp.write((const uint8_t*)msg.c_str(), msg.length());
  udp.endPacket();

  delay(3000);
}

/*
# PC에서 실행할 코드
# Arduino UNO R4 WiFi 보드가 UDP로 '문자열'을 전송할 때
# PC에서 '문자열'을 수신하는 코드

import socket

PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", PORT))

print("Listening UDP on", PORT)

while True:
    data, addr = sock.recvfrom(4096)
    text = data.decode("utf-8", errors="replace")
    print(f"From {addr}: {text}", end="")
*/
