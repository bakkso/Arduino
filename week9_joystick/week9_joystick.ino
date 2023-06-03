// 2가지의 기능, 조이스틱의 z축을 누르면 기능 변경, RGB LED 사용
// 초기 LED 소등, 서보 모터 90도로 설정
// 기능 1)
// : 조이스틱 UP, 서보모터 각도 증가, 서보모터가 해당 각도로 이동
// : 조이스틱 DOWN, 서보모터 각도 감소, 서보모터가 해당 각도로 이동
// : 서보모터는 0 ~ 180도 사이의 값
// 기능 2)
// : 조이스틱 값에 따라 기능 변경
// : 조이스틱 UP, 서보모터의 각도가 90도 이상 -> LED의 BLUE 값 증가, 90도 미만 -> LED의 BLUE 값 감소
// : 조이스틱 RIGHT, 서보모터의 각도가 90도 이상 -> LED의 RED 값 증가, 90도 미만 -> LED의 RED 값 감소
// 조이스틱을 LEFT, 서보모터의 각도가 90도 이상 -> LED의 GREEN 값 증가, 90도 미만 -> LED의 GREEN 값 감소
// 조이스틱을 DOWN, 서보모터의 각도가 90도 이상 -> 모든 LED의 값 증가, 90도 미만 -> 모든 LED의 값 감소
// LED의 값은 0에서 255사이에서만 변동한다.

#include <Servo.h>
#define SERVO_PIN 9

#define X_PIN A0
#define Y_PIN A1
#define SW_PIN 7

#define R_PIN 3
#define G_PIN 5
#define B_PIN 6

// 서보 객체 선언
Servo myservo;
// 서보 모터의 초기 위치
int pos = 0;

// 상태
int z_state = 0;
int x_state = 0;
int y_state = 0;

// LED 상태
int blue_state = 0;
int red_state = 0;
int green_state = 0;

int A = 0;

void setup()
{
    // 서보 모터의 초기 각도 설정
    myservo.write(90);
    pinMode(SW_PIN, INPUT_PULLUP);
    pinMode(X_PIN, INPUT);
    pinMode(Y_PIN, INPUT);

    // 서보 모터 핀 지정
    myservo.attach(SERVO_PIN);

    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);

    // LED 소등
    setColor(0, 0, 0);

    Serial.begin(9600);
}

void loop()
{

    // 각 축 읽어오기, x,y축은 analog / z축은 스위치니까 digital
    int x = analogRead(X_PIN);
    int y = analogRead(Y_PIN);
    int z = digitalRead(SW_PIN);

    // 아날로그 값인 x,y축을 서보 모터의 각도(0 ~ 180도)로 매핑
    x_state = map(x, 0, 1023, 0, 180);
    y_state = map(y, 0, 1023, 0, 180);

    // 현재 상태 시리얼로 출력
    Serial.print(z); // 스위치
    Serial.print(", ");
    Serial.print(pos); // 서보 모터 각도
    Serial.print(", ");
    Serial.print(red_state); // red 값
    Serial.print(", ");
    Serial.print(green_state); // green 값
    Serial.print(", ");
    Serial.print(blue_state); // blue 값
    Serial.print(", ");
    Serial.print(z_state)
        Serial.print(", ");
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);

    // 기능 1)
    if (z_state == 0)
    {
        pos = y_state;
        myservo.write(pos);
        delay(15);
    }

    // 기능 2)
    else if (z_state == 1)
    {
        // 아래 x,y축의 상하좌우를 나누는 값의 기준은 조이스틱 마다 다름
        // 가진 조이스틱의 범위를 직접 구해서 아래 코드에 대입해야함
        // 또한 아날로그 값인 조이스틱의 x축, y축의 값이 조이스틱의 움직임에 따라 급변하므로
        // 상하좌우의 범위를 크게 나눠줬음

        // UP
        if (y < 400)
        {
            if (pos >= 90)
            {
                blue_state += 5;
                delay(10);
            }
            else
            {
                blue_state -= 5;
                delay(10);
            }
        }

        // RIGHT
        else if (x > 700)
        {
            if (pos >= 90)
            {
                red_state += 5;
                delay(10);
            }
            else
            {
                red_state -= 5;
                delay(10);
            }
        }

        // LEFT
        else if (x > 0 && x < 400)
        {
            if (pos >= 90)
            {
                green_state += 5;
                delay(10);
            }
            else
            {
                green_state -= 5;
                delay(10);
            }
        }

        // DOWN
        else if (y > 700)
        {
            if (pos >= 90)
            {
                blue_state += 5;
                red_state += 5;
                green_state += 5;
                delay(10);
            }
            else
            {
                blue_state -= 5;
                red_state -= 5;
                green_state -= 5;
                delay(10);
            }
        }

        // 위에서 입력받은 RGB값을 대입하여 LED 점등
        setColor(red_state, green_state, blue_state);
        delay(200);
    }

    // 스위치 상태 변경
    if (digitalRead(SW_PIN) == 0 && z_state == 0)
    {
        z_state = 1;
        delay(200);
    }
    else if (digitalRead(SW_PIN) == 0 && z_state == 1)
    {
        z_state = 0;
        delay(200);
    }
}

// RGB
void setColor(int red, int green, int blue)
{
    // R,G,B 값을 0과 255 사이로 제한
    red = constrain(red, 0, 255);
    green = constrain(green, 0, 255);
    blue = constrain(blue, 0, 255);

    analogWrite(R_PIN, red);
    analogWrite(G_PIN, green);
    analogWrite(B_PIN, blue);
}