// 12주차 2번
// p2에 맞는 기능 레이아웃 구현
// 주기적으로 아두이노에서 주도센서와 온도센서의 값을 전송
// 왼쪽에는 센서 이름 출력, 오른쪽에는 해당 값 출력

// p2Activity.java ->  텍스트 출력 : private void setResultValue()
//                 ->  2가지의 텍스트 출력해야하므로 그에 맞게 수정 필수
// UI를 새로 생성해줬다면 -> private void initUI()에 생성된 UI 추가 ( mTvUltra, mTvUltra2 )
// public class p1Activity extends Activity 다시 한 번 점검 필수 ( p2에 맞게 수정 )

#include <SoftwareSerial.h>
#include <Thermistor.h>

//- 센서 연결 핀 선언 ----------------------------------------------------------
#define RXD_PIN 2
#define TXD_PIN 3
#define LIGHT_PIN A1
Thermistor temp(A0);

float temperature; // 온도
float lux;

//- 센서 제어 객체 선언 -------------------------------------------------------
SoftwareSerial bt(RXD_PIN, TXD_PIN);

//- 전역 변수 선언 ------------------------------------------------------------
String rxData = "";
unsigned long preMillis = 0;

//- 센서 초기화 ---------------------------------------------------------------
void setup()
{
    Serial.begin(9600); // 디버깅 용
    bt.begin(9600);     // BT통신 용
    temperature = 0;
    lux = 0;
    pinMode(LIGHT_PIN, INPUT);
}

//- 기능 구현 ------------------------------------------------------------------
void loop()
{

    float temperature = temp.getTemp();
    float lux = analogRead(LIGHT_PIN);
    sendStringData("@ULT,", String(temperature));
    sendStringData("@XLT,", String(lux));
    delay(100);
}

void sendStringData(String sztitle, String szMsg)
{
    String szSendData = sztitle;
    szSendData += szMsg;
    szSendData += "#";
    bt.print(szSendData);       //- 블루투스로 전송
    Serial.println(szSendData); //- 데이터 전송 확인을 위한 PC로 전송
}