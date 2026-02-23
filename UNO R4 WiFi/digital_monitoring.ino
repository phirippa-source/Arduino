#include <WiFiS3.h>  
#define USER_SW   8   // 스위치 연결 핀 8번

const char* ssid = "Ria2G";
const char* password = "2026gogo";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  while (!Serial) { } 
  pinMode(USER_SW, INPUT_PULLUP);   // INPUT_PULLUP

  while(WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(500);     Serial.print(".");
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
        if ( strMsg.lastIndexOf("\r\n\r\n")>=0 ) {
          Serial.println(strMsg);
          strMsg = "";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("");
       
          if( digitalRead(USER_SW) ) {
            client.println("<html><body> Pressed! </body></html>");
          } else {
            client.println("<html><body> Not pressed!</body></html>");
          }
          break;
        }
      }
    }
    delay(1); 
    client.stop(); //연결 종료
  }
}

