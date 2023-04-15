#define RED_BUTTON 12
#define BUZ_BUTTON 7
#define BLUE_BUTTON 3
#define RED_LED1 11
#define RED_LED2 10
#define RED_LED3 9
#define BLUE_LED1 6
#define BLUE_LED2 5
#define BLUE_LED3 4
#define BUZ_PIN 13
#define DO 256
#define RE 288
#define MI 320


int dore[] = { DO, RE, MI };
int RED_STATE=0;
int BUZ_STATE=0;
int BLUE_STATE=0;

void setup() { 

  pinMode( RED_BUTTON, INPUT_PULLUP );
  pinMode( RED_LED1, OUTPUT );
  pinMode( RED_LED2, OUTPUT );
  pinMode( RED_LED3, OUTPUT );

  pinMode( BUZ_BUTTON, INPUT_PULLUP );
  pinMode( BUZ_PIN, OUTPUT );
  
  pinMode( BLUE_BUTTON, INPUT_PULLUP );
  pinMode( BLUE_LED1, OUTPUT );
  pinMode( BLUE_LED2, OUTPUT );
  pinMode( BLUE_LED3, OUTPUT ); 

  Serial.begin(9600);
}

void loop() {
  
  if (digitalRead(RED_BUTTON) == 0 && RED_STATE == 0) {
    RED_STATE = 1;
    delay(200);
  }
  else if (digitalRead(RED_BUTTON) == 0 && RED_STATE == 1 ) {
    RED_STATE = 0;
    delay(200);
  }

  if (digitalRead(BUZ_BUTTON) == 0 && BUZ_STATE == 0) {
    BUZ_STATE = 1;
    delay(200);
  }
  else if (digitalRead(BUZ_BUTTON) == 0 && BUZ_STATE == 1 ) {
    BUZ_STATE = 0;
    delay(200);
  }

  if (digitalRead(BLUE_BUTTON) == 0 && BLUE_STATE == 0) {
    BLUE_STATE = 1;
    delay(200);
  }
   
  else if (digitalRead(BLUE_BUTTON) == 0 && BLUE_STATE == 1 ) {
    BLUE_STATE = 0;
    delay(200);
  }
    
    if ( RED_STATE == 1 || BLUE_STATE == 1 || BUZ_STATE == 1 ) {
    
    
    /*Serial.println("IF in");
    delay(1000); */
     
    digitalWrite(RED_LED1, RED_STATE);
    digitalWrite(BLUE_LED1, BLUE_STATE);
    if ( BUZ_STATE == 1 ) {
      tone(BUZ_PIN,dore[0],300);
    }
    delay(300);
    digitalWrite(RED_LED1, LOW);
    digitalWrite(BLUE_LED1, LOW);
    delay(300);
    
    digitalWrite(RED_LED2, RED_STATE);
    digitalWrite(BLUE_LED2, BLUE_STATE);
    if ( BUZ_STATE == 1) {
      tone(BUZ_PIN,dore[1],300);
    }
    delay(300);
    digitalWrite(RED_LED2, LOW);
    digitalWrite(BLUE_LED2, LOW);
    delay(300);
     
    digitalWrite(RED_LED3, RED_STATE);
    digitalWrite(BLUE_LED3, BLUE_STATE);
    if ( BUZ_STATE == 1) {
      tone(BUZ_PIN,dore[2],300);
    }
    delay(300);
    digitalWrite(RED_LED3, LOW);
    digitalWrite(BLUE_LED3, LOW);
    delay(300);
  }
    
  /*Serial.println(BUZ_STATE);

  Serial.println(BLUE_STATE);

  Serial.println(RED_STATE);

  Serial.println("IF out");

  delay(1000); */
  
}