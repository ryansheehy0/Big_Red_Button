#include <WiFi.h>
#include "time.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Setup variables
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
const char* ssid = "ssid";
const char* pass = "pass";
const char* ntpServer = "pool.ntp.org";
const int btnPin = 12;
const int maxRows = 15;

// HTML variables
const char* htmlPageStart = "<!DOCTYPE html><html><head><title>Time Tracking Big Red Button</title><meta charset='UTF-8' /><meta name='viewport' content='width=device-width, initial-scale=1.0' /><style>table, td, th {border: 2px solid #FFF; text-align: left; color: white; font-family: 'Courier New', Courier, monospace;}table {border-collapse: collapse; width: 100%;} th, td {padding: 15px;}</style></head><body style='background-color: black;'><table><tr><th>Day of week:</th><th>Date:</th><th style='display: none;'>Unix time:</th><th>Local time:</th></tr>";
const char* rowStart = "<tr class='row'><td class='day'></td><td class='date'></td><td class='unix' style='display: none;'>";
char unixTimes[maxRows][20];
int timeIndex = 0;
const char* rowEnd = "</td><td class='local'></td></tr>";
const char* htmlPageEnd = "</table><script>const rows = document.querySelectorAll('.row');const unixTimes = document.querySelectorAll('.unix');const dayOfWeeks = document.querySelectorAll('.day');const dates = document.querySelectorAll('.date');const localTimes = document.querySelectorAll('.local');for (const [i, unixTime] of unixTimes.entries()) {if(Number.isNaN(parseInt(unixTime.innerHTML))){rows[i].style.display = 'none';continue;}rows[i].style.display = '';const date = new Date(parseInt(unixTime.innerHTML) * 1000);const daysOfWeek = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];dayOfWeeks[i].innerHTML = daysOfWeek[date.getDay()];const months = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];const monthName = months[date.getMonth()];dates[i].innerHTML = `${monthName} ${date.getDate()}`;const hours = date.getHours();const amOrPm = hours >= 12 ? 'PM' : 'AM';const hours12 = hours % 12 || 12;localTimes[i].innerHTML = `${hours12}:${String(date.getMinutes()).padStart(2, '0')} ${amOrPm}`;}</script></body></html>";

// Unassigned variables
unsigned long currentTime;
char ipAddress[15];

// Setup things
WiFiServer server(80);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup(){
	Serial.begin(115200);
	pinMode(btnPin, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

	WiFi.begin(ssid, pass);
	while(WiFi.status() != WL_CONNECTED){
		delay(500);
		Serial.println(".");
	}

	Serial.println("Connected to Wifi");
	WiFi.localIP().toString().toCharArray(ipAddress, 15);
	configTime(0, 0, ntpServer);
  server.begin();

	delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25, 25);
  display.println(ipAddress);
  display.display();
	delay(2000);
  display.clearDisplay();
  display.display();
}

void loop(){
	if(digitalRead(btnPin) == LOW){
    display.setCursor(25, 25);
    display.println(ipAddress);
		display.display();
		currentTime = getTime();
		if(timeIndex == maxRows){
			timeIndex = 0;
		}
    snprintf(unixTimes[timeIndex], 20, "%lu", currentTime);
		timeIndex++;
		delay(1000);
  	display.clearDisplay();
    display.display();
	}

	WiFiClient client = server.available();
	if(client){
    String currentLine = "";
		while(client.connected()){
			if(client.available()){
        char c = client.read();
        if(c == '\n'){
					if(currentLine.length() == 0){
						client.println("HTTP/1.1 200 OK");
						client.println("Content-type: text/html");
						client.println("Connection: close");
						client.println();
						client.print(htmlPageStart);
						int index = timeIndex - 1;
						for(int i = 0; i < maxRows; i++){
							if(index == maxRows){
								index = 0;
							}else if(index == -1){
								index = maxRows - 1;
							}
							client.print(rowStart);
							client.print(unixTimes[index]);
							client.print(rowEnd);
							index--;
						}
						client.print(htmlPageEnd);
						client.println();
            client.stop();
					}else{
						currentLine = "";
					}
        }else if(c != '\r'){
					currentLine += c;
        }
			}
		}
	}
}

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return(0);
  }
  time(&now);
  return now;
}