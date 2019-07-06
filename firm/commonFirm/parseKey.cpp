#include <arduino.h>

// 右手側ピン番号の定義
#define InputPin1 4
#define InputPin2 5
#define InputPin3 6
#define InputPin4 7
#define InputPin5 8
#define InputPin6 9
#define OutpuPin1 A5
#define OutpuPin2 A4
#define OutpuPin3 A3
#define OutpuPin4 A2
#define OutpuPin5 A1

static void digitalWritePortRegister(unsigned int pin, unsigned int hOrl);
static char digitalReadPortRegister(unsigned int pin);

// 右手モジュールの初期化。一度だけ呼び出してください
void InitParseKeyModule()
{
  pinMode(InputPin1, INPUT_PULLUP);
  pinMode(InputPin2, INPUT_PULLUP);
  pinMode(InputPin3, INPUT_PULLUP);
  pinMode(InputPin4, INPUT_PULLUP);
  pinMode(InputPin5, INPUT_PULLUP);
  pinMode(InputPin6, INPUT_PULLUP);
  pinMode(OutpuPin1, OUTPUT);
  pinMode(OutpuPin2, OUTPUT);
  pinMode(OutpuPin3, OUTPUT);
  pinMode(OutpuPin4, OUTPUT);
  pinMode(OutpuPin5, OUTPUT);

  digitalWrite(OutpuPin1, HIGH);
  digitalWrite(OutpuPin2, HIGH);
  digitalWrite(OutpuPin3, HIGH);
  digitalWrite(OutpuPin4, HIGH);
  digitalWrite(OutpuPin5, HIGH);
}

// キーのパース 引数は5x6の行列分の領域を割り当て済である必要があります。
int ParseKey(char ans[][6])
{
  digitalWritePortRegister(OutpuPin1, LOW);
  ans[0][0] = digitalRead(InputPin1);
  ans[0][1] = digitalReadPortRegister(InputPin2);
  ans[0][2] = digitalReadPortRegister(InputPin3);
  ans[0][3] = digitalReadPortRegister(InputPin4);
  ans[0][4] = digitalReadPortRegister(InputPin5);
  ans[0][5] = digitalReadPortRegister(InputPin6);
  digitalWritePortRegister(OutpuPin1, HIGH);

  digitalWritePortRegister(OutpuPin2, LOW);
  ans[1][0] = digitalRead(InputPin1);
  ans[1][1] = digitalReadPortRegister(InputPin2);
  ans[1][2] = digitalReadPortRegister(InputPin3);
  ans[1][3] = digitalReadPortRegister(InputPin4);
  ans[1][4] = digitalReadPortRegister(InputPin5);
  ans[1][5] = digitalReadPortRegister(InputPin6);
  digitalWritePortRegister(OutpuPin2, HIGH);
  
  digitalWritePortRegister(OutpuPin3, LOW);
  ans[2][0] = digitalRead(InputPin1);
  ans[2][1] = digitalReadPortRegister(InputPin2);
  ans[2][2] = digitalReadPortRegister(InputPin3);
  ans[2][3] = digitalReadPortRegister(InputPin4);
  ans[2][4] = digitalReadPortRegister(InputPin5);
  ans[2][5] = digitalReadPortRegister(InputPin6);
  digitalWritePortRegister(OutpuPin3, HIGH);

  digitalWritePortRegister(OutpuPin4, LOW);
  ans[3][0] = digitalRead(InputPin1);
  ans[3][1] = digitalReadPortRegister(InputPin2);
  ans[3][2] = digitalReadPortRegister(InputPin3);
  ans[3][3] = digitalReadPortRegister(InputPin4);
  ans[3][4] = digitalReadPortRegister(InputPin5);
  ans[3][5] = digitalReadPortRegister(InputPin6);
  digitalWritePortRegister(OutpuPin4, HIGH);

  digitalWritePortRegister(OutpuPin5, LOW);
  ans[4][0] = digitalRead(InputPin1);
  ans[4][1] = digitalReadPortRegister(InputPin2);
  ans[4][2] = digitalReadPortRegister(InputPin3);
  ans[4][3] = digitalReadPortRegister(InputPin4);
  ans[4][4] = digitalReadPortRegister(InputPin5);
  ans[4][5] = digitalReadPortRegister(InputPin6);
  digitalWritePortRegister(OutpuPin5, HIGH);
  
  return 0;
}

// ポートレジスタをいじってデジタルライトを実行します
// pinはA1～A5に対応します
static void digitalWritePortRegister(unsigned int pin, unsigned int hOrl)
{
  switch (pin)
  {
  case A1:
    if (hOrl == HIGH) PORTF |= (64);
    else PORTF &= ~(64);
    break;
  case A2:
    if (hOrl == HIGH) PORTF |= (32);
    else PORTF &= ~(32);
    break;
  case A3:
    if (hOrl == HIGH) PORTF |= (16);
    else PORTF &= ~(16);
    break;
  case A4:
    if (hOrl == HIGH) PORTF |= (2);
    else PORTF &= ~(2);
    break;
  case A5:
    if (hOrl == HIGH) PORTF |= (1);
    else PORTF &= ~(1);
    break;
  default:
    break;
  }
}

// ポートレジスタをいじってデジタルリードを実行します
// pin は 4～11に対応します
static char digitalReadPortRegister(unsigned int pin)
{
  char ret = LOW;
  switch (pin)
  {
  case 4:
    if (PIND & _BV(4)) ret = HIGH;
    else ret = LOW;
    break;
  case 5:
    if (PINC & _BV(6)) ret = HIGH;
    else ret = LOW;
    break;
  case 6:
    if (PIND & _BV(7)) ret = HIGH;
    else ret = LOW;
    break;
  case 7:
    if (PINE & _BV(6)) ret = HIGH;
    else ret = LOW;
    break;
  case 8:
    if (PINB & _BV(4)) ret = HIGH;
    else ret = LOW;
    break;
  case 9:
    if (PINB & _BV(5)) ret = HIGH;
    else ret = LOW;
    break;
  default:
    break;
  }
  return ret;
}
