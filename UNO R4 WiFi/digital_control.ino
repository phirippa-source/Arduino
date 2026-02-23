#include <WiFiS3.h>  
const char* ssid = "Ria2G";
const char* password = "2026gogo";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  while (!Serial) { } // (필요 시) 시리얼 연결 대기
  pinMode(LED_BUILTIN, OUTPUT);
  while(WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  while( WiFi.localIP() == IPAddress(0,0,0,0)){
    delay(200);
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  String strMsg;
  if (client) {

    while (client.connected()) {
      if (client.available() > 0) {
        strMsg += (char)client.read();
        if ( strMsg.lastIndexOf("\r\n")>=0 ) {
          Serial.println(strMsg);

          if( strMsg.indexOf("\On") >= 0 ) { 
            digitalWrite(LED_BUILTIN, HIGH); }
          else if( strMsg.indexOf("\Off") >= 0 ) { 
            digitalWrite(LED_BUILTIN, LOW); }
          strMsg = "";

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          //client.println("<!DOCTYPE html>");
          //client.println("<html><head><link rel=\"shortcut icon\" href=\"data:image/x-icon;,\"image/x-icon\"></head>");
          //client.println("<body></body></html>");

          break;
        }
      }
    }
    delay(1); // 응답 전송 안정화
    client.stop(); //연결 종료
  }
}
