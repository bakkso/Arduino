// 실습 4주차 2번
// 초음파 센서로 측정한 거리에 따라 능동부저와 LED동작
// 스위치 누르고 있지 않은 상태 -> 출력 x
// 스위치 누르고 있는 상태 -> 시리얼 모니터에 측정 거리 출력
// 1. 20cm 이하 -> 부저 0.1초 간격, 0.1초 동안 울림 / 빨간색 LED동일한 주기로 점등과 소등 반복
// 2. 40cm 이하 -> 부저 0.3초 간격, 0.3초 동안 울림 / 노란색 LED동일한 주기로 점등과 소등 반복
// 3. 60cm 이하 -> 부저 0.5초 간격, 0.5초 동안 울림 / 초록색 LED동일한 주기로 점등과 소등 반복
// 4. 60cm 초과 -> 부저 x / 흰색 LED 지속적으로 점등

const int trigPin = 12; // 초음파
const int echoPin = 13;
const int buzzerPin = 4; // 버저
const int redLedPin = 5; // led 핀 선언
const int yellowLedPin = 6;
const int greenLedPin = 7;
const int whiteLedPin = 8;
const int switchPin = 9; // 버튼

int A = 0;
int switchState = 0;
long duration;
int distance;

void setup()
{
  pinMode(trigPin, OUTPUT); // trig은 OUTPUT, echo는 INPUT 설정
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(whiteLedPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{

  switchState = digitalRead(switchPin);

  if (switchState == 0)
  {
    // 버튼이 눌려진 상태일 때 실행 (한 번 눌렀다고 실행되는 거 x)

    // 측정 거리를 계산
    digitalWrite(trigPin, LOW);  // Trig 핀을 LOW로 설정하여 초기화
    delayMicroseconds(2);        // 2 마이크로초 동안 대기
    digitalWrite(trigPin, HIGH); // Trig 핀을 HIGH로 설정하여 초음파 발사
    delayMicroseconds(10);       // 10 마이크로초 동안 대기
    digitalWrite(trigPin, LOW);  // Trig 핀을 다시 LOW로 설정하여 초음파 발사 완료

    // 초음파 센서에서 받은 반사파를 측정 (Echo 핀에서 HIGH 상태로 유지되는 시간)
    // pulseIn(pin, value)
    duration = pulseIn(echoPin, HIGH);

    // 측정한 duration을 이용하여 거리 distance를 계산 (단위: 센티미터)
    // duration * (음속 340m/s = 0.034cm/us) / 2 (왕복 시간이므로 반으로 나눔)
    distance = duration * 0.034 / 2;

    // 시리얼 모니터에 측정한 거리를 출력
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // 거리에 따라 부저와 LED를 제어
    if (distance <= 20)
    {
      tone(buzzerPin, 300, 100);
      digitalWrite(redLedPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(redLedPin, LOW);
      delay(100);
    }

    else if (distance <= 40)
    {
      tone(buzzerPin, 300, 300);
      digitalWrite(yellowLedPin, HIGH);
      delay(300);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      delay(300);
    }

    else if (distance <= 60)
    {
      tone(buzzerPin, 300, 500);
      digitalWrite(greenLedPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(greenLedPin, LOW);
      delay(500);
    }

    else if (distance > 60 && switchState == 0)
    {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(whiteLedPin, HIGH);
      delay(500);
    }

    digitalWrite(whiteLedPin, LOW);
  }
}