//실습 3주차 1번
//부저 리모컨 만들기
//시리얼 모니터에 숫자 입력 해당 동작을 한다. Serial.parseInt()사용
//1 - 도 출력, 시리얼 모니터에 "BUZZER ON" 출력, 1을 다시 입력 "BUZZER OFF"만 출력
//2 - 한 음을 높여 한 번 출력.
//3 - 한 음을 낮춰 한 번 출력.
//4 - 박자를 2배 증가 후 한번 출력. (최댓값 800)
//5 - 박자를 2배 감소 후 한번 출력. (최솟값 200)
//1을 제외한 동작은 부저가 "ON"상태일 때만 작동


#define BUZ_PIN 11  //- 부저 연결 핀 선언
#define DO 256     //- 4옥타브 기준의 피아노 음계
#define RE 288
#define MI 320
#define FA 341
#define SO 384
#define LA 427
#define TI 480
#define DELAY 300
int num = 0;
int level=0;
int c=200;
int dore[] = { DO, RE, MI, FA, SO, LA, TI }; // 음계 배열
                
void setup() {
  Serial.begin(9600); // 아두이노 9600으로 시작
  pinMode(9,OUTPUT);  pinMode(8,OUTPUT);  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);  pinMode(4,OUTPUT); 
} // pinMode(pinNum, mode) : 해당 핀을 입력으로 사용할지 출력으로 사용할지 설정
void loop() {
  if (Serial.available()) { // 데이터 존재 여부 확인
    int val = Serial.parseInt(); // 입력받은 값중 "정수값"만 읽어오기
    if (val == 1 && num == 0) { // num == 0을 받는 이유 : 1을 다시 입력했을때 종료조건을 만들어주기위해
      Serial.print("BUZZER ON\n");
      tone(BUZ_PIN, DO, 100);
      delay(100);
      num++; // 1을 처음에 입력하고 끝날때 num에 값을 1 더해주면서 num != 0 으로 만들어주기
    } 
		else if (val == 1 && num == 1) { 
      Serial.print("BUZZER OFF\n");
      num--; // num에 1을 빼주면서 시작조건으로 만들어주기
    }
  if (num == 1) { // 마지막 조건인 "1을 제외한 동작은 부저가 "ON" 상태일때만 작동한다를 만족시켜주기 위해
	  if (val == 2) { 
	      level++; // tone앞에 쓴 이유 : 2번 조건인 이전음보다 한 음 높여 출력하기 위해 배열안에 들어가는 level의 값을 1증가 시켜줌
	      tone(BUZ_PIN, dore[level], 100); // tone(pinNo, frequency(진동수), duration)
	      delay(100);
	  }
	  if (val == 3) { 
	    level--; // 3번 조건인 이전 음 보다 한 음 낮춰 출력하기 위해 배열안에 들어가는 level의 값을 1 감소시킴
	    tone(BUZ_PIN, dore[level], 100);
	    delay(100);
	  }
	  if (val == 4) {
	    if ( c <= 800 ) { // 박자 = 출력시간, 즉 출력시간을 조절 시켜주면 됨. 조건 : 최댓값 800으로 설정
	      c = c*2; // 박자 2배 증가하기 위해 출력시간*2
	      tone(BUZ_PIN,dore[level], c);
	    }
	   }
	  if (val == 5) {
	    if ( c >= 200 ) { // 조건 : 최솟값은 200으로 설정
	      c = c/2; // 박자 2배 감소하기 위해 출력시간/2
	      tone(BUZ_PIN,dore[level], c);
	      delay(100);
	    }
	  }
	}
}