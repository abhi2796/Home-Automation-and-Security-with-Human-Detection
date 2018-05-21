#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define DHTPIN 2

// AP Wi-Fi credentials
const char* ssid = "abhi";
const char* password = "123456789";

// Local ESP web-server address
String serverHost = "http://192.168.4.1/feed";
String data;
// DEEP_SLEEP Timeout interval
int sleepInterval = 5;
// DEEP_SLEEP Timeout interval when connecting to AP fails
int failConnectRetryInterval = 2;
int counter = 0;

int x_rec = 1024;
int flag = 0;

void buildDataStream(int t, int h);
// Static network configuration
IPAddress ip(192, 168, 4, 4);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiClient client;

void setup() {
  ESP.eraseConfig();
  WiFi.persistent(false);
  Serial.begin(74880);
}

void sendee(int t, int h)
{
  Serial.println();
  Serial.println("**************************");
  Serial.println("**************************");
  Serial.println("******** BEGIN ***********");
  Serial.println("- set ESP STA mode");
  WiFi.mode(WIFI_STA);
  Serial.println("- connecting to wifi");
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  Serial.println("");
  int c = 0;
  while ((WiFi.status() != WL_CONNECTED) && (c != 9)) {
    delay(500);
    c++;
    Serial.print(".");
  }
  
  Serial.println("- wifi connected");
  Serial.println("- build DATA stream string");
  buildDataStream(t,h);
  Serial.println("- send GET request");
  sendHttpRequest();
  Serial.println();
  Serial.println("- got back to sleep");
  Serial.println("*********************M*****");
  Serial.println("**************************");
  buildDataStream(t,h);
}

void sendHttpRequest() {
  HTTPClient http;
  http.begin(serverHost);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST(data);
  http.writeToStream(&Serial);
  http.end();
}

void buildDataStream(int t, int h) 
{
  data = "temp=";
  data += String(t);
  data += "&hum=";
  data += String(h);
  Serial.println("- data stream: "+data);
}

int xim = 0;
void loop() {
  x_rec = analogRead(A0);
  Serial.println(x_rec);
  if(x_rec < 500)
  {
    flag = 1;
    xim++;
  }
  //ESP.eraseConfig();
  Serial.println(xim);
  if(xim == 2)
  {
    flag = 0;
    xim = 0;
  }
  if(flag == 1)
  {
    Serial.println("Sender");
  sendee(1,0);
  }
  else if(flag == 0)
  {
    Serial.println("Reciever");
    sendee(0,1);
    flag = 0;
  }
  delay(1000);
  }
