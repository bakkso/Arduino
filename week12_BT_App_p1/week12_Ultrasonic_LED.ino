// 12주차 1번
// 블루투스 환경이 구축된 상태에서 실습
// LED 버튼을 누르면 RED LED 점등, 점등되어있다면 소등
// 초음파 오른쪽의 파란색 상자에는 주기적으로 초음파 센서의 값 출력

// p1Activity.java ->  버튼 제어 : public void clickFunc()
//                 ->  텍스트 출력 : private void setResultValue()
// UI를 새로 생성해줬다면 -> private void initUI()에 생성된 UI 추가
// public class p1Activity extends Activity 다시 한 번 점검 필수 ( p1에 맞게 수정 )

#include <SoftwareSerial.h>

//- 센서 연결 핀 선언 ----------------------------------------------------------
#define RXD_PIN 2
#define TXD_PIN 3
#define LED_RED_PIN 7

//- 센서 제어 객체 선언 -------------------------------------------------------
SoftwareSerial bt(RXD_PIN, TXD_PIN);

const int trigPin = 12;
const int echoPin = 13;
long duration;
int distance;

//- 전역 변수 선언 ------------------------------------------------------------
String rxData = "";

//- 센서 초기화 ---------------------------------------------------------------
void setup()
{
    Serial.begin(9600); // 디버깅 용
    bt.begin(9600);     // BT통신 용
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

//- 기능 구현 ------------------------------------------------------------------
void loop()
{
    // 블루투스로 데이터가 들어왔는지 확인
    if (bt.available() > 0)
    {
        // 들어온 데이터 처리
        rxData = bt.readString();
        // 어플에서 LED버튼을 클릭하면 @LED,1# @LED,0# 가 전달되도록 설정
        // 해당 데이터를 분석 -> @ 로 시작 # 로 종료
        // LED 제어
        if (rxData.startsWith("@") && rxData.endsWith("#"))
            controlWiFiData(rxData);
    }

    // 초음파 거리 측정
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    // 앱으로 초음파 데이터 전송
    // p1Activity.java 의 setResultValue에서 ULT로 받은 데이터를 어플 내에 표시하도록 설정
    sendStringData("@ULT,", String(distance));
    delay(100);
}
//- BT로 수신한 데이터 처리 -------------------------------------------------
void controlWiFiData(String rxData)
{
    Serial.print("RX <=== ");
    Serial.println(rxData);
    // 들어온 데이터에 맞게 LED 제어
    if (rxData.indexOf("LED,1") >= 0)
    {
        digitalWrite(LED_RED_PIN, HIGH);
    }
    else if (rxData.indexOf("LED,0") >= 0)
    {
        digitalWrite(LED_RED_PIN, LOW);
    }
}

void sendStringData(String sztitle, String szMsg)
{
    String szSendData = sztitle;
    szSendData += szMsg;
    szSendData += "#";
    bt.print(szSendData);       //- 블루투스로 전송
    Serial.println(szSendData); //- 데이터 전송 확인을 위한 PC로 전송
}
