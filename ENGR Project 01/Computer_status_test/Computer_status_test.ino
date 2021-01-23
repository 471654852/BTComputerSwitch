void setup() {
  pinMode(2, INPUT);
  digitalWrite(2, LOW);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}

void loop() {
  if(digitalRead(2) == HIGH)
  {
    digitalWrite(13, HIGH);
  }
  else 
    digitalWrite(13, LOW);
}
