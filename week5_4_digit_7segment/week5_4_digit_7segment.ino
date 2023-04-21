// 5주차 실습 2
// 4-digit 7-segment
// 시리얼 모니터에 1~99 사이의 정수 입력 -> 타이머 동작
// 프로그램 시작되면 세그먼트 0 출력
// 시리얼 모니터에 숫자 입력 -> 0.3초 주기로 증가 -> 해당 숫자에서 정지
// 숫자가 증가하는 중 스위치 누름 -> 부저 짧게 소리 내며 숫자의 증가 정지
// 숫자의 증가 정지된 상태에서 다시 스위치 누름 -> 다시 숫자 증가
// 세그먼트 9번핀과 12번 핀은 사용x -> 4 digit에서 십의자리와 일의자리만 사용
// 해당 자리에 스위치와 부저 연결 -> D5, D2에 스위치와 부저 연결

#include <SevSeg.h>

SevSeg sevseg;
int buttonPin = 5;
int buzzerPin = 2;
int targetNumber = 0;  // 시리얼 모니터에서 입력받는 숫자
int currentNumber = 0; // 현재 세그먼트 디스플레이에 표시되는 숫자
bool isPaused = false; // 숫자 증가의 일시중지 여부를 판단하는 bool 변수
unsigned long timer;   // 경과시간 저장 변수

void setup()
{
  byte numDigits = 2;                           // 두자리만 사용(십의자리, 일의자리)
  byte digitPins[] = {6, 13};                   // 10의 자리에 해당되는 공통단자 핀번호 6, 1의 자리에 해당되는 공통단자 핀번호 13
  byte segmentPins[] = {3, 7, 11, 9, 8, 4, 12}; // 각 세그먼트 핀에 연결된 아두이노 핀 번호 저장하는 배열 A~G까지에 해당되는 핀 번호
  //(공통 애노드 타입, 자릿수, 자릿수 핀, 세그먼트 핀)
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90); // 세그먼트 밝기

  pinMode(buttonPin, INPUT_PULLUP); // 버튼 설정, PULLUP모드 : 누르면 HIGH(1) -> LOW(0)
  pinMode(buzzerPin, OUTPUT);       // 부저 설정, OUTPUT : 출력모드로 설정됨

  Serial.begin(9600); // 시리얼통신 시작, 통신속도 9600 baud 설정
  timer = millis();   // 프로그램 시작 시의 경과 시간 저장
                      // setup()에 설정해두는 이유 : 프로그램 시작 시점의 시간을 초기값을 설정, 이후 경과 시간 계산에 사용하기 위해
}

void loop()
{
  if (Serial.available() > 0) // 시리얼버퍼에 값(데이터)이 들어오면 if문 아래 실행
  {
    int inputValue = Serial.parseInt(); // 시리얼에 입력된 숫자(정수)를 inputValue에 설정해줌
    if (inputValue >= 1 && inputValue <= 99)
    {                            // inputValue는 1~99사이 정수
      targetNumber = inputValue; // 설정된 inputValue를 tagetNumber로 재설정
      currentNumber = 0;         // 현재 숫자 0으로 초기화
      isPaused = false;          // 숫자 증가의 일시중지 X (처음 시작할때는 증가해야하니까 false)
    }
  }

  if (digitalRead(buttonPin) == LOW)
  {                            // 버튼이 눌렸다면
    isPaused = !isPaused;      // 숫자 증가 일시중지 상태 변수 반전시켜주기 (일시중지 -> 다시 시작 or 시작 -> 일시중지)
    tone(buzzerPin, 1000, 50); // 부저핀 울리도록 설정(1000Hz, 50ms지속)
    delay(200);                // 버튼 중복 방지를 위해 적당히 딜레이
  }

  // !isPaused : 숫자 증가 일시중지된 상태가 아닐때
  // currentNumber < targetNumber : 현재 숫자 < 입력한 숫자
  // millis() - timer >= 300 : 0.3(300ms)마다 경과했는지 확인
  // -> [[ millis() - timer = 300이 아닌 이유 :
  //    아두이노의 loop()함수가 빠르게 반복되니까 0.3초를 감지하기 어려울 수 있어서 넉넉하게 범위를 주는 것  ]]
  // 일시중지 상태가 아니고 && 현재 숫자 < 입력한 숫자 && 경과 시간이 0.3초일때
  if (!isPaused && currentNumber < targetNumber && millis() - timer >= 300)
  {
    currentNumber++;  // 현재 숫자 1 증가
    timer = millis(); // 숫자가 증가한 시점의 밀리초단위로 변수 timer에 저장
  }

  // 세그먼트 디스플레이에 현재 숫자 표시하도록 설정, 0의 의미 : 소수점 사용 x
  sevseg.setNumber(currentNumber, 0);
  // 세그먼트 디스플레이 갱신, 현재 숫자 표시되도록 함.
  sevseg.refreshDisplay();
}