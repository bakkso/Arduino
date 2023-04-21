// 실습 3주차 3번
// 실습 3주차 2번과 동일한 회로 사용
// 입력 : 16이하의 양의 정수 2개
// 출력 : 입력 받은 정수들(10진수)과 정수들의 합을 2진수로 출력
// 5자리의 2진수에 맞게 LED 점등

int num1;
int num2;
int sum;
int i;
int list[5] = {0};             // 2진법 숫자를 넣어줄 빈 배열 선언
int light[] = {2, 3, 4, 5, 6}; // led 연결 포트

void setup()
{
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  if (Serial.available() >= 2)
  { // 시리얼 버퍼에 2바이트 이상의 데이터가 있는 경우에만 실행

    num1 = Serial.parseInt(); // 처음 값을 num1에 저장
    num2 = Serial.parseInt(); // 두번째 값을 num2에 저장
    sum = num1 + num2;        // 입력받은 정수들의 합

    Serial.print("First number = ");
    Serial.println(num1);
    Serial.print("Second number = ");
    Serial.println(num2);
    Serial.print("Result = (bin) ");
    Serial.println(sum, BIN); // BIN : 2진법 으로 변환해줌

    for (i = 0; i < 5; i++)
    { // led가 5개 이므로 5까지 반복하는 for문 선언

      list[i] = sum % 2; // 2진법은 2로 나눠서 생긴 나머지이므로 나눈 나머지를 list 배열 0번째부터 차례대로 넣어줌
      sum = sum / 2;     // 위에는 나머지만 구한 것이고 sum/2을 안 해주면 초기 숫자에서 또 한 번의 나머지만 구하는 것이므로 다음 단계로 나가기 위한 절차
      Serial.print(list[i]);

      if (list[i] == 1)
      { // 각 배열에서 1이면 점등 0이면 소등
        digitalWrite(light[i], HIGH);
      }
      else
      {
        digitalWrite(light[i], LOW);
      }
    }
    Serial.print("\n"); // 이걸 안 붙여줬더니 10011first~ 이런식으로 출력되어서 붙여줌
  }
}
/*

    1. 내가 한 실습은 for문의 반복 차례대로 하나씩 켜지고 하나씩 꺼졌다.
      그 이유가 digitalWrite를 for문안에 넣어줘서 그런것같다. 이것도 수정해서 다시 회로도구성해서 실습해봐야겠음.
    2. sum과 Serial.print의 순서를 바꿔서 실습해보기
    for (i = 0; i < 5; i++)
    {// led가 5개 이므로 5까지 반복하는 for문 선언

      list[i] = sum % 2;
      Serial.print(list[i]);
      sum = sum / 2;
      sum과 Serial.print의 순서를 바꿔주면 어떻게 되나...?
      -> ////
    }
    // list[]에 저장된 2진법 그 자체를 on&off로 넣어줌
    // PULLUP에서는 HIGH - 1, LOW - 0
    digitalWirte(light[0], list[0]);
    digitalWirte(light[1], list[1]);
    digitalWirte(light[2], list[2]);
    digitalWirte(light[3], list[3]);
    digitalWirte(light[4], list[4]);

    }
    Serial.print("\n"); // 이걸 안 붙여줬더니 10011first~ 이런식으로 출력되어서 붙여줌
----------------------------------------
    gpt가 작성해준 코드
    void loop()
    {
        if (Serial.available() >= 2)
        {
    num1 = Serial.parseInt();
    num2 = Serial.parseInt();
    sum = num1 + num2;

    Serial.print("First number = ");
    Serial.println(num1);
    Serial.print("Second number = ");
    Serial.println(num2);
    Serial.print("Result = (bin) ");
    Serial.println(sum, BIN);

    list[0] = (sum >> 4) & 1; //sum을 오른쪽으로 4비트 이동한 후, 1과 비트 AND 연산을 수행합니다. 10011 >> 4는 1이고, 1 & 1은 1이므로, list[0]에 1이 저장
    list[1] = (sum >> 3) & 1; //sum을 오른쪽으로 3비트 이동한 후, 1과 비트 AND 연산을 수행합니다. 10011 >> 3는 10이고, 10 & 1은 0이므로, list[1]에 0이 저장
    list[2] = (sum >> 2) & 1; //sum을 오른쪽으로 2비트 이동한 후, 1과 비트 AND 연산을 수행합니다. 10011 >> 2는 100이고, 100 & 1은 0이므로, list[2]에 0이 저장
    list[3] = (sum >> 1) & 1; //sum을 오른쪽으로 1비트 이동한 후, 1과 비트 AND 연산을 수행합니다. 10011 >> 1는 1001이고, 1001 & 1은 1이므로, list[3]에 1이 저장
    list[4] = sum & 1; //sum과 1을 비트 AND 연산합니다. 10011 & 1은 1이므로, list[4]에 1이 저장
    // -> 만약 2진수가 10011이라면 list 배열에는 sum의 2진수 표현인 [1, 0, 0, 1, 1]이 저장
    for (i = 0; i < 5; i++)
    {
      digitalWrite(light[i], list[i]);
    }
    Serial.print("\n");
        }
    }
*/