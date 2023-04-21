// 실습 7주차 1번
// 가변저항 이용 전자 하모니카 만들기
// 가변저항 상태값에 따라 장치 7단계로 구분
// 각 단계마다 LED 하나씩 배정 (총 7개)
// 가변저항의 최소 -> 가장 왼쪽 LED 점등 , 가변저항의 최대 -> 가장 오른쪽 LED 점등
// 각 단계마다 음계 하나씩 배정(가장 왼쪽 LED-도, 가장 오른쪽 LED-시, 수동부저 사용)
// 스위치 누르고 있는 동안 부저에서 해당 음계 출력
// LED 스위치의 동작 유무와 상관없이 항상 점등

#define POTEN_PIN A0 // 가변저항
#define LED1 7       // led
#define LED2 8
#define LED3 9
#define LED4 10
#define LED5 11
#define LED6 12
#define LED7 13
#define buz 6
#define button 5
#define DO 256 // 각 음계에 해당 되는 주파수
#define RE 288
#define MI 320
#define FA 341
#define SO 384
#define LA 427
#define TI 480

void setup()
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
    pinMode(LED7, OUTPUT);

    pinMode(buz, OUTPUT);

    pinMode(button, INPUT_PULLUP);

    Serial.begin(9600);
}

void loop()
{
    // 가변저항의 아날로그 신호를 읽어서 readVal에 저장
    int readVal = analogRead(POTEN_PIN);

    // map(value, fromLow, fromHigh, toLow, toHigh)
    /*
    value: 변환하려는 값
    fromLow: 원래 범위의 최솟값
    fromHigh : 원래 범위의 최댓값
    toLow : 목표 범위의 최솟값
    toHigh : 목표 범위의 최댓값
    */
    // 가변저항이 최저일때 음계는 도, led는 가장왼쪽, 최고일때는 그 반대를 해줘야하므로 256 ~ 480사이로 매핑하여 변환
    readVal = map(readVal, 0, 1023, 256, 480);
    // 매핑된 현재 가변저항을 시리얼 모니터에 출력
    Serial.println(readVal);

    // if문에서 각 led 종료해주려고 했는데 오류가 남
    //  -> 초반에 다 꺼버리자
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);

    // 7구간으로 나누어 led 점등
    // 각 구간에서 버튼이 눌러진 상태에서만 부저 울림

    //  도 <= 가변저항 < 레
    if (readVal >= DO && readVal < RE)
    {
        digitalWrite(LED1, HIGH);
        if (digitalRead(button) == LOW)
        {
            tone(buz, DO, 100);
        }
    }
    // 레 <= 가변저항 < 미
    else if (readVal >= RE && readVal < MI)
    {
        digitalWrite(LED2, HIGH);
        if (digitalRead(button) == LOW)
        {
            tone(buz, RE, 100);
        }
    }
    // 미 <= 가변저항 < 파
    else if (readVal >= MI && readVal < FA)
    {
        digitalWrite(LED3, HIGH);
        if (digitalRead(button) == LOW)
        {
            tone(buz, MI, 100);
        }
    }
    // 파 <= 가변저항 < 솔
    else if (readVal >= FA && readVal < SO)
    {
        digitalWrite(LED4, HIGH);
        if (digitalRead(button) == LOW)
        {
            tone(buz, FA, 100);
        }
    }
    // 솔 <= 가변저항 < 라
    else if (readVal >= SO && readVal < LA)
    {
        digitalWrite(LED5, HIGH);
        if (digitalRead(button) == LOW)
        {
            tone(buz, SO, 100);
        }
    }
    // 라 <= 가변저항 < 시
    else if (readVal >= LA && readVal < TI)
    {
        digitalWrite(LED6, HIGH);
        if (digitalRead(button) == LOW)
        {
            tone(buz, LA, 100);
        }
    }
    // 시 <= 가변저항
    else if (readVal >= TI)
    {
        digitalWrite(LED7, HIGH);
        if (digitalRead(button) == LOW)
        {
            tone(buz, TI, 100);
        }
    }
}