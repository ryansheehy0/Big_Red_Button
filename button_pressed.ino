/*
- Make sure to connect to GIOP12 and not pin 12
- Connect the other side of the button to ground
- Should be a normally open button
*/

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