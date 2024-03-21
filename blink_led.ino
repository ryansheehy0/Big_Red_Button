const int ledPin = 5;

void setup(){
	pinMode(ledPin, OUTPUT);
}

void loop(){
	digitalWrite (ledPin, HIGH);
  delay(750);
  digitalWrite (ledPin, LOW);
  delay(750);
}