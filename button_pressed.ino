const int btnPin = 12;

void setup(){
	pinMode(btnPin, INPUT_PULLUP);
	Serial.begin(115200);
}

void loop(){
	if(digitalRead(btnPin) == LOW){
		Serial.println("btn pressed");
		delay(2000);
	}else{
		Serial.println("btn not pressed");
	}
}