// 13주차 1번
// p3에 맞는 기능 레이아웃 구현
// 3개의 버튼 연결
// 각 스위치를 누르면 앱 상의 text 색깔 변화 ( 검정 <-> 빨강 )
// 아두이노에서 문자열을 시리얼 모니터에 입력 -> 해당 문자열 어플 내에 출력

// p3Activity.java ->  스위치 상태 전송 : private void setResultValue()
//                 ->  아두이노의 스위치에서 출력되는 정보를 읽어서 어플에 전송
//                 ->  전송받은 정보를 바탕으로 어플에 그에 맞는 기능 구현 ( clickFunc 응용 )
//                 ->  텍스트 출력 : private void setResultValue()

// UI를 새로 생성해줬다면 -> private void initUI()에 생성된 UI 추가 ( mLedBTN, mLedBTN2, mLedBTN3 )
// public class p3Activity extends Activity 다시 한 번 점검 필수 ( p3에 맞게 수정 )

// 3번

#include <SoftwareSerial.h>

//- 센서 연결 핀 선언 ----------------------------------------------------------
#define RXD_PIN 2
#define TXD_PIN 3
#define button1 7
#define button2 6
#define button3 5

int state1 = 0;
int state2 = 0;
int state3 = 0;

String inputString;

//- 센서 제어 객체 선언 -------------------------------------------------------
SoftwareSerial bt(RXD_PIN, TXD_PIN);

//- 전역 변수 선언 ------------------------------------------------------------
String rxData = "";

//- 센서 초기화 ---------------------------------------------------------------
void setup()
{
    Serial.begin(9600); // 디버깅 용
    bt.begin(9600);     // BT통신 용
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
}

//- 기능 구현 ------------------------------------------------------------------
void loop()
{
    // 시리얼 모니터로 값이 입력된다면
    if (Serial.available() > 0)
    {
        delay(10);
        inputString = Serial.readString();
        sendStringData("@ULT,", String(inputString));
        delay(100);
    }

    // button1을 눌렀을 때
    if (digitalRead(button1) == LOW && state1 == 0)
    {
        state1 = 1;
        sendStringData("@RED,", "");
        delay(100);
    }
    else if (digitalRead(button1) == LOW && state1 == 1)
    {
        state1 = 0;
        delay(100);
    }
    // button2를 눌렀을 때
    if (digitalRead(button2) == LOW && state2 == 0)
    {
        state2 = 1;
        sendStringData("@BLU,", "");
        delay(100);
    }
    else if (digitalRead(button2) == LOW && state2 == 1)
    {
        state2 = 0;
        delay(100);
    }
    // button3을 눌렀을 때
    if (digitalRead(button3) == LOW && state3 == 0)
    {
        state3 = 1;
        sendStringData("@GRE,", "");
        delay(100);
    }
    else if (digitalRead(button3) == LOW && state3 == 1)
    {
        state3 = 0;
        delay(100);
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