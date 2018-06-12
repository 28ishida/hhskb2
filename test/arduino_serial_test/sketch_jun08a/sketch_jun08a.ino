#define LED_PIN 13

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
 
  // シリアルポートを9600 bps[ビット/秒]で初期化 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int inputchar;
 
  // シリアルポートより1文字読み込む
  inputchar = Serial.read();
 
  if(inputchar != -1 ){
    // 読み込んだデータが -1 以外の場合　以下の処理を行う
 
    switch(inputchar){
      case 'o':
        // 読み込みデータが　o の場合
 
        Serial.print("LED ON\n");
        digitalWrite(LED_PIN, HIGH);
        break;
      case 'p':  
        // 読み込みデータが　p の場合
 
        Serial.print("LED OFF\n");
        digitalWrite(LED_PIN, LOW);
        break;
    }
  } else {
    // 読み込むデータが無い場合は何もしない
  }
}
