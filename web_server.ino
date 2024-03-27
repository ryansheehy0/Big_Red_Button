#include <WiFi.h>

const char* ssid = "ssid";
const char* pass = "pass";

const char* htmlPage = "<!DOCTYPE html><html><head><meta charset='UTF-8' /><meta name='viewport' content='width=device-width, initial-scale=1.0' /></head><body><div>Test</div></body></html>";

WiFiServer server(80);

void setup(){
	Serial.begin(115200);

	Serial.println("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, pass);
	while(WiFi.status() != WL_CONNECTED){
		delay(500);
		Serial.println(".");
	}

  Serial.println("");
  Serial.println("WiFi connected. ");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
	WiFiClient client = server.available();

	if(client){
		if(client.connected() && client.available()){
			client.println("HTTP/1.1 200 OK");
			client.println("Content-type: text/html");
			client.println("Connection: close");
			client.println();
			client.println(htmlPage);
			client.println();
			client.stop();
		}
	}
}