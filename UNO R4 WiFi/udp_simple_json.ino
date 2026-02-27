#include <WiFiS3.h>
#include <WiFiUdp.h>
#define USER_SW 12

const char* ssid = "Ria2G";
const char* pass = "2026gogo";

IPAddress PC_IP(192, 168, 1, 2);   // <-- PC IPv4로 변경
const uint16_t PC_PORT = 5005;      // <-- PC가 받을 포트

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  pinMode(USER_SW, INPUT_PULLUP);

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
  String msg = "{\"A0\":" + String(analogRead(A0));
         msg +=",\"D12\":" + String(digitalRead(USER_SW));
         msg += "}";
  Serial.println(msg);

  udp.beginPacket(PC_IP, PC_PORT);
  udp.write((const uint8_t*)msg.c_str(), msg.length());
  udp.endPacket();

  delay(3000);
}

/*
import socket, json

PORT = 5005  # 아두이노에서 보내는 PC_PORT와 동일하게

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", PORT))

print("Listening UDP on", PORT)

while True:
    data, addr = sock.recvfrom(4096)

    # 1) bytes -> str
    text = data.decode("utf-8", errors="replace").strip()

    # 2) str(JSON) -> dict
    try:
        dict_obj = json.loads(text)   # dict로 변환됨
    except json.JSONDecodeError as e:
        print("JSON parse error:", e)
        print("From", addr, "Raw:", repr(text))
        continue

    # 3) dict로 처리
    A0 = dict_obj.get("A0")  # 없으면 None
    D12 = dict_obj.get("D12")
    print(f"From {addr} dict={dict_obj},\tA0={A0}\tD12={D12}")
*/
