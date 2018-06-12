#define LED_PIN 13
char writebuf[100];

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
 
  // シリアルポートを9600 bps[ビット/秒]で初期化 
  //Serial.begin(9600);

  for( int cnt = 0; cnt < 100; cnt++ )
  {
    writebuf[cnt] = (char)cnt;
  }
  
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int inputchar;
 
  // シリアルポートより1文字読み込む
  inputchar = Serial1.read();
  
  if(inputchar != -1 ){
    // 読み込んだデータが -1 以外の場合　以下の処理を行う

    switch(inputchar){
      case 'o':
            
        digitalWrite(LED_PIN, HIGH);
        
        // 読み込みデータが　o の場合
        Serial1.write(writebuf, 100);

        digitalWrite(LED_PIN, LOW);
        break;
    }
  } else {
    // 読み込むデータが無い場合は何もしない
  }
}
