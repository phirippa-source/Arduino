#include <WiFiS3.h>  // UNO R4 WiFi 전용 WiFi 라이브러리

void setup() {
  Serial.begin(115200);
  while (!Serial) { } // (필요 시) 시리얼 연결 대기

  Serial.println("... Scan Networks ...");
  int nSSID = WiFi.scanNetworks();
  if ( nSSID == -1 ) {
    Serial.println("Couldn't get a WiFi connection");
    while(1);
  }

  Serial.print("# of available networks: ");
  Serial.println(nSSID);

  for( int i = 0; i < nSSID; i++) {
    Serial.print(i+1); Serial.print(") ");
    Serial.print( WiFi.SSID(i) );
    Serial.print("\t\tSignal: "); 
    Serial.print( WiFi.RSSI(i) );
    Serial.println ("[dBm]");  
  }
  Serial.println("... End ...");
}

void loop() {
  
}
