#include <WiFi.h>
#include <time.h>

const char* ssid = "ssid";
const char* pass = "pass";

const char* ntpServer = "ch.pool.ntp.org";
const char* ntpServer2 = "pool.ntp.org";

unsigned long epochTime;

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return(0);
  }
  time(&now);
  return now;
}

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

	configTime(0, 0, ntpServer);
}

void loop(){
  epochTime = getTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  delay(1000);
}