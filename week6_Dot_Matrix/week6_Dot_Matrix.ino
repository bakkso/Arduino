// 실습 6주차 1번
// 도트매트릭스와 스위치4개 구성
// 4개의 스위치 -> 상,하,좌,우
// 초기 시작 지점 (4,4)
// 점은 매트릭스 밖으로 나가지 않는다.
// 도트 매트릭스의 1행과 8행, 1열과 8열은 사용하지 않는다. --> 7x7만 사용
// 빈 디지털핀에 스위치를 연결한다.

int pins[17] = {-1, A2, A5, 11, 10, -1, 8, 7, 6, -1, 4, 3, 2, -1, A3, A4, -1};
// cols : 열, rows : 행
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[6], pins[11], pins[15], pins[16]};
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};
int push_pin[4] = {5, 9, 12, 13}; // 스위치 4개 배열
int rowIdx = 4;
int colIdx = 4;

void setup()
{
  // 초기 dot matrix pinmode 설정
  for (int idx = 1; idx <= 16; idx++)
  {
    pinMode(pins[idx], OUTPUT);
  }
  // 초기에 전체 off
  allOff();
  // 스위치 pinmode 설정
  for (int idx = 0; idx < 4; idx++)
  {
    pinMode(push_pin[idx], INPUT_PULLUP);
  }
  // 초기 시작 지점 설정
  dot(rowIdx, colIdx);
}

void loop()
{
  // 첫번째 스위치( 상 ) 눌렸을 때
  if (digitalRead(push_pin[0]) == LOW)
  {
    // 행과 열의 배열은 0부터 시작 -> 1행 rows[0], 1열 cols[0]
    // 조건에서 매트릭스 밖(7x7)으로 나가지 않아야하므로 점은 2행~7행 & 2열~7열 사이에 존재

    // rowIdx >= 2가 아닌 이유 : rowIdx=2인 경우 즉, rows[1]에서는 up할 수 없게 만들어야하기때문에 2를 포함하지 않아야한다.
    if (rowIdx > 2)
    {
      // 상 - up 에 해당되므로 1개의 행을 빼줘야 dot가 올라감
      rowIdx--;
      // rowIdx는 7x7에 존재해야하기때문에 2이하가 될 때마다 rowIdx를 2로 만들어줘서 그 안에 존재하게 만든다.
      if (rowIdx <= 2)
      {
        rowIdx = 2;
      }
    }
  }
  // 두번째 스위치( 하 ) 눌렸을 때
  if (digitalRead(push_pin[1]) == LOW)
  {
    // rowIdx <= 7가 아닌 이유 : rowIdx=7인 경우 즉, rows[6]에서는 down할 수 없게 만들어야하기때문에 7을 포함하지 않아야한다.
    if (rowIdx < 7)
    {
      // 하 - down 에 해당되므로 1개의 행을 더해줘야 dot가 내려감
      rowIdx++;
      // rowIdx는 7x7에 존재해야하기때문에 7이상이 될 때마다 rowIdx를 7로 만들어줘서 그 안에 존재하게 만든다.
      if (rowIdx >= 7)
      {
        rowIdx = 7;
      }
    }
  }
  // 세번째 스위치( 좌 ) 눌렸을 때
  if (digitalRead(push_pin[2]) == LOW)
  {
    if (colIdx > 2)
    {
      // 좌 - left 에 해당되므로 1개의 열을 빼줘야 dot가 왼쪽으로 움직임
      colIdx--;
      if (colIdx <= 2)
      {
        colIdx = 2;
      }
    }
  }
  // 네번째 스위치( 우 ) 눌렸을 때
  if (digitalRead(push_pin[3]) == LOW)
  {
    if (colIdx < 7)
    {
      // 우 - right 에 해당되므로 1개의 열을 더해줘야 dot가 오른쪽으로 움직임
      colIdx++;
      if (colIdx >= 7)
      {
        colIdx = 7;
      }
    }
  }
  // 위에서 받은 row와 col에 대한 dot를 점등
  dot(rowIdx, colIdx);
  delay(100);
}

void allOn()
{
  for (int idx = 0; idx < 8; idx++)
  {
    digitalWrite(rows[idx], !LOW);
    digitalWrite(cols[idx], !HIGH);
  }
}

void allOff()
{
  for (int idx = 0; idx < 8; idx++)
  {
    digitalWrite(rows[idx], LOW);
    digitalWrite(cols[idx], HIGH);
  }
}

void dot(int rowIdx, int colIdx)
{
  // 이전 dot 초기화 해주기 위해 alloff()
  allOff();
  // 각 인수에 해당되는 led 켜줌
  // dot matrix에서 row-행에 해당되는 led를 켜주는 값은 !LOW
  //               cols-열에 해당되는 led를 켜주는 값은 !HIGH
  // 배열은 0부터 시작하므로 rowIdx, colIdx에 각각 -1을 해줌
  digitalWrite(rows[rowIdx - 1], !LOW);
  digitalWrite(cols[colIdx - 1], !HIGH);
}
