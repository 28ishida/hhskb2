#define LED_PIN 13
char readbuf[100];

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
 
  // シリアルポートを9600 bps[ビット/秒]で初期化 
  Serial.begin(9600);

  memset( readbuf, 0, 100 );
    
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int inputchar;

  Serial1.write('o');
  
  // シリアルポートより100文字読み込む
  int ret = Serial1.readBytes(readbuf, 100);

  if(ret == 100)
  {
    digitalWrite(LED_PIN, HIGH);
       
    Serial.print(readbuf[0], DEC);
    Serial.print(readbuf[10], DEC);
    Serial.print(readbuf[50], DEC);
    digitalWrite(LED_PIN, LOW);

  } else {
    // 読み込むデータが無い場合は何もしない
  }
}
