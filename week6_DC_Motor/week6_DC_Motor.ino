//실습 6주차 2번
//버튼을 누를때마다 회전 세기 강해짐
//세기는 3단계
//각 세기별 white led 점등
//초기상태 : 정지, red led 점등
//3단 세기 이후 버튼 다시 누르면 초기 상태

#define EN_PIN 11
#define IN1_PIN 10
#define IN2_PIN 9

#define push_pin 2
#define red_led 3
#define white_led1 4
#define white_led2 5
#define white_led3 6
boolean bReverse = false;

int push_level = 0;

void setup()
{ pinMode(EN_PIN, OUTPUT); 
  pinMode(IN1_PIN, OUTPUT); 
  pinMode(IN2_PIN, OUTPUT);
  pinMode(push_pin, INPUT_PULLUP);
  pinMode(red_led, OUTPUT);
  pinMode(white_led1, OUTPUT);
  pinMode(white_led2, OUTPUT);
  pinMode(white_led3, OUTPUT);
}

void loop()
{ 

if (digitalRead(push_pin) == LOW) {
    
    push_level++;

    delay(200);

  }
  if (push_level == 0) {
    digitalWrite(red_led, HIGH);
    digitalWrite(white_led3, LOW);
    setMotor(0, bReverse);
  }

  if (push_level == 1) {
    digitalWrite(red_led, LOW);
    setMotor(200, bReverse);
    digitalWrite(white_led1, HIGH);
  }

  else if (push_level == 2) {
    digitalWrite(white_led1, LOW);
    setMotor(215, bReverse);
    digitalWrite(white_led2, HIGH);
  }

  else if (push_level == 3) {
    digitalWrite(white_led2, LOW);
    setMotor(250, bReverse); //analog 바람의세기는 최대 250까지
    digitalWrite(white_led3, HIGH);
  }

  if (push_level >= 4) {
    push_level = 0;
  }

}
void setMotor(int nSpeed, boolean bReverse)
{ 
  analogWrite(EN_PIN, nSpeed);
  digitalWrite(IN1_PIN, !bReverse); 
  digitalWrite(IN2_PIN, bReverse); 
}