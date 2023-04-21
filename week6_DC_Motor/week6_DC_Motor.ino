// 실습 6주차 2번
// 버튼을 누를때마다 회전 세기 강해짐
// 세기는 3단계
// 각 세기별 white led 점등
// 초기상태 : 정지, red led 점등
// 3단 세기 이후 버튼 다시 누르면 초기 상태

#define EN_PIN 11 // 모터
#define IN1_PIN 10
#define IN2_PIN 9

#define button 2  // 버튼
#define red_led 3 // LED
#define white_led1 4
#define white_led2 5
#define white_led3 6
bool bReverse = false; // bool대신 boolean(초기버전)을 사용해도 됨

int button_level = 0;

void setup()
{
  pinMode(EN_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

  pinMode(button, INPUT_PULLUP);

  pinMode(red_led, OUTPUT);
  pinMode(white_led1, OUTPUT);
  pinMode(white_led2, OUTPUT);
  pinMode(white_led3, OUTPUT);
}

void loop()
{

  if (digitalRead(button) == LOW)
  {

    // 버튼 눌렸을 때, 레벨 1씩 증가
    push_level++;
    delay(200);
  }
  // 초기상태
  if (push_level == 0)
  {
    // 이전 레벨에서 켜져있던 white led과 모터 off
    digitalWrite(white_led3, LOW);
    setMotor(0, bReverse);
    // 초기상태 조건인 red LED 켜줌
    digitalWrite(red_led, HIGH);
  }

  // 1단계
  if (push_level == 1)
  {
    // 이전 레벨에서 켜져있던 led 꺼줌
    digitalWrite(red_led, LOW);
    setMotor(200, bReverse);
    digitalWrite(white_led1, HIGH);
  }
  // 2단계
  else if (push_level == 2)
  {
    // 이전 레벨에서 켜져있던 led 꺼줌
    digitalWrite(white_led1, LOW);
    setMotor(215, bReverse);
    digitalWrite(white_led2, HIGH);
  }
  // 3단계
  else if (push_level == 3)
  {
    // 이전 레벨에서 켜져있던 led 꺼줌
    digitalWrite(white_led2, LOW);
    setMotor(250, bReverse); // analog 바람의세기는 최대 250까지
    digitalWrite(white_led3, HIGH);
  }
  // 3단계에서 초기상태로 돌아감
  if (push_level >= 4)
  {
    push_level = 0;
  }
}
// 모터 함수
void setMotor(int nSpeed, bool bReverse)
{
  analogWrite(EN_PIN, nSpeed);
  digitalWrite(IN1_PIN, !bReverse);
  digitalWrite(IN2_PIN, bReverse);
}