// 차량 조립 및 구동
// 직진, 후진, 좌회전, 우회전 구동

#include <SoftwareSerial.h>
#define RXD_PIN 13
#define TXD_PIN 12

int leftMotorPin1 = 4;
int leftMotorPin2 = 5;
int rightMotorPin1 = 6;
int rightMotorPin2 = 7;

SoftwareSerial bt(RXD_PIN, TXD_PIN);

void setup()
{
    Serial.begin(9600);
    bt.begin(9600);
}

void loop()
{
    while (bt.available())
    {
        int data = bt.read();
        x = Serial.parseInt();
        y = Serial.parseInt();

        delay(1);
        if (y > 700)
        { // 위로 올렸을 때
            digitalWrite(leftMotorPin1, HIGH);
            digitalWrite(leftMotorPin2, LOW);
            digitalWrite(rightMotorPin1, HIGH);
            digitalWrite(rightMotorPin2, LOW);
        }
        else if (x < 400)
        { // 오른쪽으로 밀었을 때
            digitalWrite(leftMotorPin1, LOW);
            digitalWrite(leftMotorPin2, HIGH);
            digitalWrite(rightMotorPin1, HIGH);
            digitalWrite(rightMotorPin2, LOW);
        }
        else if (x > 700)
        { // 왼쪽으로 밀었을 때
            digitalWrite(leftMotorPin1, HIGH);
            digitalWrite(leftMotorPin2, LOW);
            digitalWrite(rightMotorPin1, LOW);
            digitalWrite(rightMotorPin2, HIGH);
        }
        else if (y < 400)
        { // 아래로 당겼을 때
            digitalWrite(leftMotorPin1, LOW);
            digitalWrite(leftMotorPin2, HIGH);
            digitalWrite(rightMotorPin1, LOW);
            digitalWrite(rightMotorPin2, HIGH);
        }
    }
}
