//실습 5주차 1번
//스위치를 눌렀을 때, 1-digit 7 segment 숫자 증가
//프로그램이 실행되면 세그먼트의 숫자는 0
//버튼을 누를 때마다 숫자 1 증가, 10에 도달하면 다시 0


int buttonPin = 11; // 스위치 핀 번호
int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8}; // 7개의 세그먼트 디스플레이 핀 번호
int currentNumber = 0; // 현재 숫자

void setup() {
pinMode(buttonPin, INPUT);
for (int i = 0; i < 7; i++) {
pinMode(segmentPins[i], OUTPUT);
}
displayNumber(currentNumber);
Serial.begin(9600);
}

void loop() {
Serial.println(digitalRead(buttonPin));
delay(100);
if (digitalRead(buttonPin) == HIGH) {
currentNumber++;
if (currentNumber >= 10) {
currentNumber = 0;
}
displayNumber(currentNumber);
delay(200);
}
}

void displayNumber(int number) {
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
{1, 1, 1, 1, 0, 1, 1} // 9
};
for (int i = 0; i < 7; i++) {
digitalWrite(segmentPins[i], digits[number][i]);
}
}