#include <WiFi.h>
#include <time.h>

const char* ssid = "ssid";
const char* pass = "pass";

const char* NTP_SERVER = "ch.pool.ntp.org";
const char* TZ_INFO    = "PST8PDT";  // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)

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

	configTime(0, 0, NTP_SERVER);
  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
  setenv("PST8PDT,M3.2.0,M11.1.0", TZ_INFO, 1);

}

void loop(){

}