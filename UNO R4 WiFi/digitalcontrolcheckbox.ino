#include <WiFiS3.h>
#define USER_LED  12
#define BUILTIN_LED LED_BUILTIN
const char* ssid = "Ria2G";
const char* password = "2026gogo";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  pinMode(USER_LED, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.println("WiFi connecting...");
  while(WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  while( WiFi.localIP() == IPAddress(0,0,0,0)){
    delay(200);
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void ProcessCheckbox(WiFiClient cl, String msg) { 
  int user_led =  ( msg.indexOf("USER_LED=1") >=0 ) ? HIGH : LOW;
  digitalWrite(USER_LED, user_led);

  if (user_led) {      // LED on
     //cl.println("<input type=\"checkbox\" name=\"USER_LED\" value=\"1\" onclick=\"submit();\" checked>USER LED");
     cl.println("<input type='checkbox' name='USER_LED' value='1' onclick='submit();' checked>USER LED");
  } else {                // LED off
     //cl.println("<input type=\"checkbox\" name=\"USER_LED\" value=\"1\" onclick=\"submit();\">USER LED");
     cl.println("<input type='checkbox' name='USER_LED' value='1' onclick='submit();'>USER LED");
  }

  int builtin_led = ( msg.indexOf("BUILTIN_LED=1") >=0 ) ? HIGH : LOW;
  digitalWrite(BUILTIN_LED, builtin_led);

  if (builtin_led) {    // LED on
     cl.println("<input type=\"checkbox\" name=\"BUILTIN_LED\" value=\"1\" onclick=\"submit();\" checked>BUILTIN LED");
  } else {              // LED off
     cl.println("<input type=\"checkbox\" name=\"BUILTIN_LED\" value=\"1\" onclick=\"submit();\">BUILTIN LED");
  }
}


void loop(void){
  String msg;
  WiFiClient client = server.available();
  if ( client ) { 
    Serial.println("\nNew Client");
    while( client.connected() ) {     
      if ( client.available() ) {
        msg += (char)client.read(); //  수신 메시지의 첫 줄만 고려했음
        if ( msg.lastIndexOf("\r\n") >= 0 ) { 
          Serial.print(msg);
          client.println("HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\n");
          client.println("<!DOCTYPE html><html><head>");
          client.println("<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\"image/x-icon\">");
          client.println("</head><body><h1>LED</h1><p>Click Checkbox to toggle LED.</p>");               
          client.println("<form method=\"get\">");
          ProcessCheckbox(client, msg);
          client.println("</form></body></html>");
          msg = "";
          break;   
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected\n");
  } // if( client ) end
}  // loop() 
