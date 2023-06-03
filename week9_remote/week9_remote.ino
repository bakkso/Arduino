// Using a remote control, control the LED and the 7 - segment display.
// Initially, the LED and segment are turned off.
// (All buttons activate the buzzer briefly when pressed.)
// 0 : Display 0 on the segment and turn off all LEDs.
// 1 : Display 1 on the segment and turn on all LEDs.
// 3 : Display 3 on the segment and turn on the blue LED. If the blue LED is already on, turn it off.
// 4 : Display 4 on the segment and turn on the white LED. If the white LED is already on, turn it off.
// 5 : Display 5 on the segment and turn on the green LED. If the green LED is already on, turn it off.
// 6 : Display 6 on the segment and turn on the yellow LED.If the yellow LED is already on, turn it off.
// 7 : Display 7 on the segment and turn on the red LED.If the red LED is already on, turn it off.

#include <IR.h>
#define IR_PIN 10

// 리모컨 버튼에 따른 HEX 코드를 정의
#define zero 0xFF6897
#define one 0xFF30CF
#define three 0xFF7A85
#define four 0xFF10EF
#define five 0xFF38C7
#define six 0xFF5AA5
#define seven 0xFF48BD

#define LED1 A5
#define LED2 A4
#define LED3 A3
#define LED4 A2
#define LED5 A1

#define BUZ_PIN 11

int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};
int currentNumber = 0;

// IR 핀을 사용하여 IRrecv 객체를 생성
IRrecv irrecv(IR_PIN);
// IR 신호를 디코드하는 데 사용할 decode_results 객체를 생성
// decResult는 디코드된 결과를 저장하기 위한 decode_results 타입의 변수
decode_results decResult;

void setup()
{
    for (int i = 0; i < 7; i++)
    {
        pinMode(segmentPins[i], OUTPUT);
    }
    irrecv.enableIRIn();
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(BUZ_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{

    // irrecv.decode(&decResult)는 적외선 리시버로부터 신호를 받아서 decResult에 저장하고,
    // 이 신호가 유효하면 true를 반환
    // decResult.value는 디코드된 신호의 값이며, 이 값은 리모컨 버튼마다 고유

    // IR 신호를 받았을 경우 처리
    if (irrecv.decode(&decResult))
    {
        Serial.println(decResult.value, HEX); // 디버깅을 위해 받은 IR 신호를 출력, println -> 첫 번째 인자로 전달된 값을 두 번째 인자로 지정된 형식으로 출력하라
        decodeIR();                           // 받은 IR 신호를 처리하는 함수를 호출합니다.
        irrecv.resume();                      // 다음 IR 신호 수신을 준비합니다.
    }
}

void displayNumber(int number)
{
    int digits[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };
    for (int i = 0; i < 7; i++)
    {
        digitalWrite(segmentPins[i], digits[number][i]);
    }
}

void decodeIR()
{
    switch (decResult.value)
    {
    case zero:
        displayNumber(0);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        tone(BUZ_PIN, 256, 300);
        break;

    case one:
        displayNumber(1);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, HIGH);
        tone(BUZ_PIN, 256, 300);
        break;

    case three:
        displayNumber(3);
        if (digitalRead(LED5) == HIGH)
        {
            digitalWrite(LED5, LOW);
        }
        else
            digitalWrite(LED5, HIGH);
        tone(BUZ_PIN, 256, 300);
        break;

    case four:
        displayNumber(4);
        if (digitalRead(LED4) == HIGH)
        {
            digitalWrite(LED4, LOW);
        }
        else
            digitalWrite(LED4, HIGH);
        tone(BUZ_PIN, 256, 300);
        break;
    case five:
        displayNumber(5);
        if (digitalRead(LED3) == HIGH)
        {
            digitalWrite(LED3, LOW);
        }
        else
            digitalWrite(LED3, HIGH);
        tone(BUZ_PIN, 256, 300);
        break;

    case six:
        displayNumber(6);
        if (digitalRead(LED2) == HIGH)
        {
            digitalWrite(LED2, LOW);
        }
        else
            digitalWrite(LED2, HIGH);
        tone(BUZ_PIN, 256, 300);
        break;

    case seven:
        displayNumber(7);
        if (digitalRead(LED1) == HIGH)
        {
            digitalWrite(LED1, LOW);
        }
        else
            digitalWrite(LED1, HIGH);
        tone(BUZ_PIN, 256, 300);
        break;
    }
}
