int greenLed = 11;
int yellowLed = 13;
int redLed = 9;

void setup()
{
  // Start with green light on
  pinMode(greenLed, OUTPUT);
  digitalWrite(greenLed, HIGH);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  unsigned int lightSensor;
  unsigned int doorSensor;
  lightSensor = analogRead(A0);
  doorSensor = analogRead(A2);
  delay(100);
  // Sensor readings
  Serial.print("Light ");
  Serial.println(lightSensor);
  Serial.print("Door ");
  Serial.println(doorSensor);

  // normalize pressure sensor reading
  int door = analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  door = door / 5;
  Serial.println(door);

  // If the light turns off and the door is locked
  if (lightSensor > 100 && digitalRead(redLed) == LOW && door > 300) {
    // warn yellow
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    delay(5000);
    
    int door2 = analogRead(doorSensor);
    delay(10);
    door2 += analogRead(doorSensor);
    delay(10);
    door2 += analogRead(doorSensor);
    delay(10);
    door2 = door2 / 3;

    // If light is still off and door is still locked, warn red
    if (analogRead(A0) > 100 && door2 > 300) {
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, HIGH);
      delay(5000);
    }
  }

  // normalize sensor reading
  door = analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  delay(10);
  door += analogRead(doorSensor);
  door = door / 5;

  // If lights are on, no warning
  if (analogRead(A0) < 100 || door < 300) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
  }
}
