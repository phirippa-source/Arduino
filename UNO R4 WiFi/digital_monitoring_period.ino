#include <WiFiS3.h>  
#define USER_SW   8   // 스위치 연결 핀 8번

const char* ssid = "Ria2G";
const char* password = "2026gogo";
WiFiServer server(80);

void GetSwitchState( WiFiClient cl ) {
    if ( digitalRead(USER_SW) == LOW ) { 
      cl.println("<font color = red>Pressed!</font>"); 
    } else { 
      cl.println("<font color = blue>Not pressed!</font>");
    }
}

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
          strMsg = "";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("");
       
          client.println("<!DOCTYPE html>");
          client.println("<html><head><title>Digital Value Monitoring</title>");
          client.println("<meta http-equiv=\"refresh\" content=\"1\">");
          client.println("</head><body>");
          GetSwitchState( client );
          client.println("</body></html>");  
          break;
        }
      }
    }
    delay(1); client.stop(); //연결 종료
  }
}

