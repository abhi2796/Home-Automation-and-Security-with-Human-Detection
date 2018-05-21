#include <ESP8266WiFi.h>

// PushingBox scenario DeviceId code and API
String deviceId = "vC81C6501F5ABB02";
const char* logServer = "api.pushingbox.com";

const char* ssid = "abhi";
const char* password = "123456789";

void sendNotification(String message){

  Serial.println("- connecting to Home Router SID: " + String(ssid));
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
  
  WiFiClient client;

  Serial.println("- connecting to pushing server: " + String(logServer));
  if (client.connect(logServer, 80)) {
    Serial.println("- succesfully connected");
    
    String postStr = "devid=";
    postStr += String(deviceId);
    postStr += "&message_parameter=";
    postStr += String(message);
    postStr += "\r\n\r\n";
    
    Serial.println("- sending data...");
    
    client.print("POST /pushingbox HTTP/1.1\n");
    client.print("Host: api.pushingbox.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 }
client.stop();
Serial.println("- stopping the client");
}

void setup() {
  Serial.begin(115200);
  sendNotification("Hello World from ESP8266!");
}
void loop()
{
	int data;
	int val_rec = analogRead(A0);
	if(val_rec < 500)
	{
		sendNotification("Hello World from ESP8266!");
	}
	while( Serial.available()){
		data = Serial.read();
	}
	
	if(data == '1')
	{
		sendNotification("Hello World from ESP8266!");
	}
}
