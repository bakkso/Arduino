// 13주차 2번
// p4에 맞는 기능 레이아웃 구현 ( 앱 상에 10개의 버튼 구현 )
// 각 버튼, 도-레-미-파-솔-라-시-끝-산토끼-작은별
// 버튼 도~시 누르면 부저에서 짧게 해당 음계 출력
// 산토끼, 작은별 누르면 해당 동요 연주
// 끝을 누르면 산토끼와 작은별이 연주되는 도중 중단

// p4Activity.java ->  텍스트 출력 : private void setResultValue()
//                 ->  2가지의 텍스트 출력해야하므로 그에 맞게 수정 필수
// UI를 새로 생성해줬다면 -> private void initUI()에 생성된 UI 추가 ( mTvUltra, mTvUltra2 )
// public class p1Activity extends Activity 다시 한 번 점검 필수 ( p2에 맞게 수정 )

#include <SoftwareSerial.h>

//- 센서 연결 핀 선언 ----------------------------------------------------------
#define RXD_PIN 2
#define TXD_PIN 3
#define BUZ 8

#define DO2 512
#define DO 256 // 각 음계에 해당 되는 주파수
#define RE 288
#define MI 320
#define FA 341
#define SO 384
#define RA 427
#define TI 480

bool isPlaying = false;

int san[] = {SO, MI, MI, SO, MI, DO, RE, MI, RE, DO, MI, SO,
             DO2, SO, DO2, SO, DO2, SO, MI, SO, RE, FA, MI, RE, DO};
int star[] = {DO, DO, SO, SO, RA, RA, SO, FA, FA, MI, MI, RE, RE, DO,
              SO, SO, FA, FA, MI, MI, RE, SO, SO, FA, FA, MI, MI, RE,
              DO, DO, SO, SO, RA, RA, SO, FA, FA, MI, MI, RE, RE, DO};

//- 센서 제어 객체 선언 -------------------------------------------------------
SoftwareSerial bt(RXD_PIN, TXD_PIN);

//- 전역 변수 선언 ------------------------------------------------------------
String rxData = "";

//- 센서 초기화 ---------------------------------------------------------------
void setup()
{
    Serial.begin(9600); // 디버깅 용
    bt.begin(9600);     // BT통신 용
}

//- 기능 구현 ------------------------------------------------------------------
void loop()
{
    // 블루투스에 값이 들어온다면
    if (bt.available() > 0)
    {
        rxData = bt.readString();
        if (rxData.startsWith("@") && rxData.endsWith("#"))
        {
            controlWiFiData(rxData);
        }
    }
}

//- BT로 수신한 데이터 처리 -------------------------------------------------
void controlWiFiData(String rxData)
{
    Serial.print("RX <=== ");
    Serial.println(rxData);

    // 도 ~ 시에 해당되는 음계 출력
    if (rxData.indexOf("A,1") >= 0)
    {
        tone(BUZ, DO, 300);
    }

    if (rxData.indexOf("B,1") >= 0)
    {
        tone(BUZ, RE, 300);
    }

    if (rxData.indexOf("C,1") >= 0)
    {
        tone(BUZ, MI, 300);
    }
    if (rxData.indexOf("D,1") >= 0)
    {
        tone(BUZ, FA, 300);
    }
    if (rxData.indexOf("E,1") >= 0)
    {
        tone(BUZ, SO, 300);
    }
    if (rxData.indexOf("F,1") >= 0)
    {
        tone(BUZ, RA, 300);
    }
    if (rxData.indexOf("G,1") >= 0)
    {
        tone(BUZ, TI, 300);
    }

    // 노래 중단을 부울함수를 이용함
    if (rxData.indexOf("H,1") >= 0)
    {
        isPlaying = false;
    }

    // 산토끼
    if (rxData.indexOf("SAN,1") >= 0)
    {
        // 현재 연주 가능하도록
        isPlaying = true;
        // 산토끼 음계 출력
        for (int i = 0; i < 25; i++)
        {
            // 만약 isPlaying이 false라면 멈춤
            if (!isPlaying)
                break;
            // 산토끼 음계 배열 for문으로 출력, delay가 없다면 너무 빠르게 for문을 돌아 정상적으로 음계출력 x
            tone(BUZ, san[i], 300);
            delay(200);
            noTone(BUZ);
            // 끝 버튼 눌렸는지 확인
            checkForNewCommands();
        }
    }

    // 작은 별
    if (rxData.indexOf("STAR,1") >= 0)
    {
        // 현재 연주 가능하도록
        isPlaying = true;
        for (int i = 0; i < 42; i++)
        {
            // 만약 isPlaying이 false라면 멈춤
            if (!isPlaying)
                break;
            // 작은별 음계 배열 for문으로 출력, delay가 없다면 너무 빠르게 for문을 돌아 정상적으로 음계출력 x
            tone(BUZ, star[i], 300);
            delay(200);
            noTone(BUZ);
            // 끝 버튼 눌렸는지 확인
            checkForNewCommands();
        }
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

// 끝 버튼이 눌렸는지 확인하는 함수
void checkForNewCommands()
{
    if (bt.available() > 0)
    {
        rxData = bt.readString();
        if (rxData.startsWith("@") && rxData.endsWith("#"))
        {
            controlWiFiData(rxData);
        }
    }
}