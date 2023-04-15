const int trigPin = 12;
const int echoPin = 13;
const int buzzerPin = 4;
const int redLedPin = 5;
const int yellowLedPin = 6;
const int greenLedPin = 7;
const int whiteLedPin = 8;
const int switchPin = 9;

int A = 0;
int switchState = 0;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(whiteLedPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
  switchState = digitalRead(switchPin);

  if (switchState ==  0) {
    // 측정 거리를 계산
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // 거리에 따라 부저와 LED를 제어
    if (distance <= 20) {
      tone(buzzerPin,300,100);
      digitalWrite(redLedPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(redLedPin, LOW);
      delay(100);
    } else if (distance <= 40) {
      tone(buzzerPin,300,300);
      digitalWrite(yellowLedPin, HIGH);
      delay(300);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      delay(300);
    } else if (distance <= 60) {
      tone(buzzerPin,300,500);
      digitalWrite(greenLedPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(greenLedPin, LOW);
      delay(500);
    } else if( distance > 60 && switchState == 0 ){
      digitalWrite(buzzerPin, LOW);
      digitalWrite(whiteLedPin, HIGH);
      delay(500);
    }
    digitalWrite(whiteLedPin,LOW);
  }
}