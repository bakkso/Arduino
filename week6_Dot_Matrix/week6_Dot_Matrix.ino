//실습 6주차 1번
//도트매트릭스와 스위치4개 구성
//4개의 스위치 -> 상,하,좌,우
//초기 시작 지점 (4,4)
//점은 매트릭스 밖으로 나가지 않는다.
//도트 매트릭스의 1행과 8행, 1열과 8열은 사용하지 않는다.
//빈 디지털핀에 스위치를 연결한다.

int pins[17] = {-1, A2, A5, 11, 10, -1, 8, 7, 6, -1, 4, 3, 2, -1, A3, A4, -1};
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[6], pins[11], pins[15], pins[16]};
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};
int push_pin[4] = {5, 9, 12, 13};
int rowIdx = 4;
int colIdx = 4;

void setup() { 
  for (int idx=1; idx<=16; idx++) {
    pinMode(pins[idx], OUTPUT); 
  }
  allOff();
  for (int idx=0; idx<4; idx++) {
    pinMode(push_pin[idx], INPUT_PULLUP);
  }
  dot(rowIdx, colIdx);
}

void loop() {

  if (digitalRead(push_pin[0]) == LOW) {
    if (rowIdx > 2) { //아래에서 배열때문에 -1해줬으니까 여기 조건문도 1이 아니라 2로 해줘야됨
      rowIdx--;
        if (rowIdx <= 2) {
          rowIdx = 2;
        }
    }
  }
  if (digitalRead(push_pin[1]) == LOW) { 
    if (rowIdx < 7) { 
      rowIdx++;
        if (rowIdx >= 7) {
          rowIdx = 7;
        }
    }
  }
  if (digitalRead(push_pin[2]) == LOW) { 
    if (colIdx > 2) { 
      colIdx--;
        if (colIdx <= 2) {
          colIdx = 2;
        }
    }
  }
  if (digitalRead(push_pin[3]) == LOW) {
    if (colIdx < 7) {
      colIdx++;
        if (colIdx >= 7) {
          colIdx = 7;
        }
    }
  }

  dot(rowIdx, colIdx);
  delay(100); 

}

void allOn() { 
  for (int idx=0; idx<8; idx++) { 
    digitalWrite(rows[idx], !LOW); 
    digitalWrite(cols[idx], !HIGH); 
  }
}

void allOff() { 
  for (int idx=0; idx<8; idx++) { 
    digitalWrite(rows[idx], LOW); 
    digitalWrite(cols[idx], HIGH);
  }
}

void dot(int rowIdx, int colIdx) {

  allOff();
  digitalWrite(rows[rowIdx-1], !LOW);
  digitalWrite(cols[colIdx-1], !HIGH);
}

