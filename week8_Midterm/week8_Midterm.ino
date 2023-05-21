// 중간고사 - 1번
// 사용자가 숫자 입력 (측정하고 싶은 거리)
// 푸시 버튼 누르면 측정 시작
// 측정하고싶으 거리보다 가까우면 LED 불이 들어온다.
// 버튼을 다시 누르면 측정 종료

// 초음파핀
const int trigPin = 12;
const int echoPin = 13;
// LED핀, 스위치핀
const int LedPin = 8;
const int switchPin = 9;
// 스위치 상태
int switchState = 0;
// 측정거리
long duration;
int distance;
int inputValue;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LedPin, OUTPUT);
    pinMode(switchPin, INPUT_PULLUP);
    Serial.begin(9600);

    Serial.print("측정할 거리 입력: ");
    while (Serial.available() == 0)
    {
    }                               // 값이 입력될 때까지 대기
    inputValue = Serial.parseInt(); // parseInt()를 사용하여 숫자를 읽어옴
    Serial.print("inputvalue : ");
    Serial.println(inputValue);
}

void loop()
{
    // 스위치 상태 변경
    if (digitalRead(switchPin) == LOW && switchState == 0)
    {
        switchState = 1;
        delay(200);
    }
    else if (digitalRead(switchPin) == LOW && switchState == 1)
    {
        switchState = 0;
        delay(200);
    }

    // 푸쉬 버튼을 누르면 측정 시작
    if (switchState == 1)
    {
        // 측정 거리를 계산
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        duration = pulseIn(echoPin, HIGH);
        distance = duration * 0.034 / 2;

        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        Serial.print("inputValue in Loop : ");
        Serial.println(inputValue);
        // 측정거리와 inputValue 비교하여 LED 제어
        if (inputValue > distance && switchState == 1)
        {
            digitalWrite(LedPin, HIGH);
            delay(100);
        }
        else
        {
            digitalWrite(LedPin, LOW);
            delay(100);
        }
    }

    else // 버튼을 눌러 측정을 종료 & LED 소등
    {
        digitalWrite(LedPin, LOW);
    }
}

// 오류1 : inputValue 변수에 값이 들어가지 않음 && 초음파 거리측정은 가능
//       -> 스위치값은 제대로 변환은 되지만 inputValue에 변수가 들어가지 않는 이슈때문에 측정거리 비교 불가
//       -> LED 제어 불가능

// 해결방안 : Serial.available에 값이 안 들어갔다는 생각
//          -> Serial.available { 괄호안에 inputValue 연산 }
//          -> 여전히 inputValue 변수안에 값이 안 들어감

// 오류1 원인 : Setup()에서 inputValue를 선언해서 지역변수가 되었다.. 큰 실수를...
//            Setup() - inputValue & loop() - inputValue 는 서로 다른 변수 loop()내에서 새롭게 지역변수로 선언됨.
//            loop()함수에서 Serial.parseInt()로 값을 읽어와서 inputValue에 저장하더라도 이 값은 loop() 함수가 끝나는 즉시 사라짐.

// 오류2 : 위 오류룰 해결해도 아두이노를 업로드하고 시리얼 모니터에 값을 입력하면
//       곧이어 inputValue가 0으로 초기화되는 현상, 초음파 거리측정은 가능

// 해결방안 : 어차피 사용자가 숫자를 입력하는 것을 초기에 한 번 수행하고 끝이니까 setup()에서 inputValue를 설정해주면 어떨까?
//           -> 성공!!!!!!!!!!!! 아주 깔끔하게 수행된다.
