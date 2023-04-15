//실습 2주차 1번
//시리얼 모니터에 문자 "ON"을 입력 -> 부저 1초 동작
//값이 들어오면 양의 값
//Serial.read()함수는 버퍼에 저장된 첫번째 값 읽어옴 -> Serial.readStringUntill()사용
//조건문 활용

#define BUZ_PIN 9

void setup( ) { 
  Serial.begin(9600);
  pinMode(BUZ_PIN, OUTPUT);
}

void loop( ) { 
  if(Serial.available()>0) //pc로부터 도착한 바이트의 수 (pc로 부터 데이터가 온 게 있는지 확인할 때 사용) 
  {
    String data = Serial.readStringUntil('\n');
    if (data == "ON") {   // data가 ON을 입력받으면
      digitalWrite(BUZ_PIN, HIGH);   // 9번 핀에 연결된 부저가 울린다.
      delay(1000);   // 1초 동안 유지
      digitalWrite(BUZ_PIN, LOW);   // 9번 핀에 연결된 부저가 멈춘다.
      delay(1000);   // 1초 동안 유지
    }
  }
}