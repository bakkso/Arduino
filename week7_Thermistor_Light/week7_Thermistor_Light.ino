// 실습7주차 2번
// 조도센서와 온도센서 이용하여 led와 모터 제어
// 1초 간격 온도센서의 값, 조도센서의 값, 온도&조도의 기준값 시리얼모니터에 출력
// 초기 기준 값 각각 0, 버튼을 누르면 온도와 조도의 기준값 저장
// 온도센서 동작 조건 :
//      * 현재 온도센서의 값이 기준 값보다 10% 증가 -> 모터 1단게 회전
//      *                          20% 증가 -> 모터 2단계 회전
//      * 그 외에는 모터 동작 x
// 조도센서 동작 조건 :
//      * 현재 조도센서의 값이 기준 값보다 30% 하락 -> 파란색 LED 점등
//      *                          50% 하락 -> 빨간색 LED 점등
//      * 그 외에 LED 점등 x

#include <Thermistor.h> // 써미스터 헤더파일
#define EN_PIN 7        // 모터
#define IN1_PIN 6       // 모터
#define IN2_PIN 5       // 모터
bool bReverse = false;  // 모터의 on off 부울함수
#define LIGHT_PIN A2    // 조도센서
Thermistor temp(A0);    // 써미스터( 내 보드에서는 10k저항 사용해야 정상 동작 )
#define button 11
#define red_led 13
#define blue_led 12

float temperature; // 온도
float lux;         // 밝기
float std_tem;     // 온도 기준값
float std_lux;     // 밝기 기준값

void setup()
{

    Serial.begin(9600);

    temperature = 0;
    lux = 0;
    std_tem = 0;
    std_lux = 0;

    pinMode(EN_PIN, OUTPUT);
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);

    pinMode(LIGHT_PIN, INPUT);

    pinMode(button, INPUT_PULLUP);
    pinMode(red_led, OUTPUT);
    pinMode(blue_led, OUTPUT);
}

void loop()
{
    //--------------------------------------------모터 & 온도

    // temp.getTemp() 함수는 temp 객체에서 온도를 가져오는 함수
    float temperature = temp.getTemp();
    // 온도 기준값 시리얼 모니터에 출력
    Serial.print("Std: ");
    Serial.print(std_tem);
    Serial.print("°C  ");
    // 온도 시리얼 모니터에 출력
    Serial.print("Tem: ");
    Serial.print(temperature);
    Serial.println("°C ");

    // 측정한 온도를 current_tem 변수에 저장해줌
    float current_tem = temperature;
    // 모터 초기화
    setMotor(0, bReverse);
    // 현재 온도가 기준값보다 10% 증가하면 모터 1단계 회전
    if (std_tem * 1.1 <= current_tem && current_tem > std_tem * 1.2)
    {
        setMotor(170, bReverse);
    }
    // 현재 온도가 기준값보다 20% 증가하면 모터 2단계 회전
    else if (std_tem * 1.2 <= current_tem)
    {
        setMotor(250, bReverse);
    }

    //--------------------------------------------led & 조도

    // 조도센서의 아날로그 값을 lux 변수에 저장
    float lux = analogRead(LIGHT_PIN);
    // 밝기 기준값 시리얼 모니터에 출력
    Serial.print("Std: ");
    Serial.print(std_lux);
    Serial.print("lux  ");
    // 밝기 시리얼 모니터에 출력
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println("lux ");

    // 측정한 밝기를 current_lux 변수에 저장해줌
    float current_lux = lux;
    delay(1000);
    // led 초기화
    digitalWrite(red_led, LOW);
    digitalWrite(blue_led, LOW);
    // 현재 밝기가 기준 값보다 30% 줄어들면 파란색 led 점등
    if (current_lux <= std_lux * 0.7 && current_lux > std_lux * 0.5)
    {
        digitalWrite(blue_led, HIGH);
    }
    // 현재 밝기가 기준 값보다 50% 줄어들면 빨간색 led 점등
    else if (current_lux <= std_lux * 0.5)
    {
        digitalWrite(red_led, HIGH);
    }
    //--------------------------------------------기준값 저장
    if (digitalRead(button) == LOW)
    {
        std_tem = temperature;
        std_lux = lux;
        delay(200);
    }
}

void setMotor(int nSpeed, bool bReverse)
{
    analogWrite(EN_PIN, nSpeed);
    digitalWrite(IN1_PIN, !bReverse);
    digitalWrite(IN2_PIN, bReverse);
}