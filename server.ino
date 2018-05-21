#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial NodeMCU(D2,D3);

// IoT platform Credentials
/*String deviceId = "vC81C6501F5ABB02";
const char* logServer = "api.pushingbox.com*/

// Internet router credentials
const char* ssid = "abhi";
const char* password = "123456789";

String t;
String h;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(74880);
  WiFi.mode(WIFI_AP_STA);
  setupAccessPoint();
  NodeMCU.begin(4800);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
}
// Handling the / root web page from my server
void handle_index() {
  server.send(200, "text/plain", "Get the f**k out from my server!");
}

// Handling the /feed page from my server
void handle_feed() {
   t = server.arg("temp");
   h = server.arg("hum");
  server.send(200, "text/plain", "This is response to client");
 // setupStMode(t, h);
}

void setupAccessPoint(){
  Serial.println("** SETUP ACCESS POINT **");
  Serial.println("- disconnect from any other modes");
  WiFi.disconnect();
  Serial.println("- start ap with SID: "+ String(ssid));
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("- AP IP address is :");
  Serial.print(myIP);
  setupServer();
}

void setupServer(){
  Serial.println("** SETUP SERVER **");
  Serial.println("- starting server :");
  server.on("/", handle_index);
  server.on("/feed", handle_feed);
  server.begin();
};


int flag = 0;

void loop() {
  server.handleClient();
  
  if(t[0] == '1')
  {
    Serial.println("lights on");
  NodeMCU.print(10);
  NodeMCU.println("\n");
  }
  else
  {
    Serial.println("lights off");
  NodeMCU.print(0);
  NodeMCU.println("\n");
  }
}
