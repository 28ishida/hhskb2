#include <Keyboard.h>
#include "hhskb_firm.h"
#include "key_definition.h"
#include "key_map.h"                             
#include <libParseKey.h>

#define ONESHOT_DEF
//#undef ONESHOT_DEF

// このターン数だけ連射モードが生きている
// ターン数を少なくすると通常のコントロールとしての挙動が多くなるが連射モードに入りづらくなる
// ターン数が多いと連射モードに入りやすくなるがムダに連射モードに入ってしまってCtrl系の誤動作が増える。
// 連射モードは明示的いキーを叩くので連写モードにギリギリ入れる最小値を探るぐらいがちょうどいい
// 体感的に25以下だとモードに入れない。100程度だとCtrlのミスが増える。
// ターンの時間的な長さはファームの動作速度に依存するのでファームをブラッシュアップする場合は再考すること
#define ROSAC_DEF 28;

// Fnキー状態
static bool IsFnEnable = false;

// Layer1キー状態
static bool IsLayer1Enable = false;

// 現在のキー状態
static char RKey[ROWMAX][COLMAX];
static char LKey[ROWMAX][COLMAX];                          

// ひとつ前のキー状態のバッファ
static char OldRKey[ROWMAX][COLMAX];
static char OldLKey[ROWMAX][COLMAX];                                    

// ワンショットが実行される際に発行されるコードの予約値
static int OneShotReserveCode = 0;

// ワンショットが予約された元キー
static int OneShotBaseCode = 0;

// 一回前に発行されたワンショットキーシンボル
static int PrevOneShotCode = 0;

// PrevOneShotCodeの有効カウント数
static int PrevOneShotActiveCount = 0;

// ワンショットのリピート実行のキーシンボル
static int RepeatOneShotCode = 0;

static int speedCheck = 1000;
static bool isConnected = false;

void setup() {
  // put your setup code here, to run once:
  memset(OldRKey, (char)OFF, SUM);
  memset(OldLKey, (char)OFF, SUM);

  InitParseKeyModule();

  isConnected = InitConnection();

  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  //unsigned long start = micros();
  memset(RKey, (char)OFF, SUM);
  ParseKey(RKey);
  //unsigned long end = micros();

  //delay(1000);
  
  keyboardAction(Right);
  memcpy(OldRKey, RKey, SUM);

  //start = micros();
  //memset(LKey, (char)OFF, SUM);
  //ParseLeftKey(LKey);
  //end = micros();
  
  //keyboardAction(Left);
  memcpy(OldLKey, LKey, SUM);
}

static bool InitConnection()
{
  Serial1.begin(9600);

  Serial1.write('c');
  for ( int cnt = 0; cnt <100; cnt++ )
  {
    int inputChar = Serial1.read();
  }
}

}
// 左右どちらかのモジュールに対してシンボルの検索、キーコードのプレス/リリースの発射を行います。
static void keyboardAction(LorR lr)
{
  for (int row = 0; row < ROWMAX; row++)
  {
    for (int col = 0; col < COLMAX; col++)
    {
      int normSymb = getSymbol(row, col, lr);   // 通常のキーコード
      int osSymb = getOSymbol(row, col, lr);    // ワンショットキーキーコード

      if (isTurnOn(row, col, lr))
      {
        if (normSymb == Fn)
        {
          IsFnEnable = true;
//          TurnOnStatusLed(2);
        }
        else if (normSymb == LY1_)
        {
          IsLayer1Enable = true;
//          TurnOnStatusLed(1);
        }
        else
        {
          // ワンショットリピートモードであれば以後の処理は不要
          if (!repeatOneShotStart(osSymb))
          {
            reserveOneShot(normSymb, osSymb);
            sendKey(normSymb, true);
          }
        }
      }
      else if (isTurnOff(row, col, lr))
      {
        if (normSymb == Fn)
        {
          forceClear();     // IsFnEnableの前に実施する事が大事
          IsFnEnable = false;
//          TurnOffStatusLed(2);
        }
        else if (normSymb == LY1_)
        {
          forceClear();     // IsFnEnableの前に実施する事が大事
          IsLayer1Enable = false;
//          TurnOffStatusLed(1);
        }
        else
        {
          if (!repeatOneShotEnd(osSymb))
          {
            sendKey(normSymb, false);
            actionOneShot(normSymb, osSymb);
          }                                                           
        }
      }
    }
  }
  checkPrevOneShotCode();
}

// ワンショットリピートの開始処理
//  ワンショットキーを連打された処理。
//  戻り値 : true  リピート処理を実施。以後の処理は省略してください
//           false リピートは発生せず。以後は通常の処理を続けます
static bool repeatOneShotStart(int otgt)
{
  bool ret = false;
#ifdef ONESHOT_DEF
  if (isPrevOneShotCodeActive())
  {
    if (getPrevOneShotCode() == otgt)
    {
      clearPrevOneShotCode();   // 自動連射モードに入るので記録はクリアしてOK
      RepeatOneShotCode = otgt;
      sendKey(otgt, true);    // ワンショットキーを押しっぱなし ワンショット 
      ret = true;
    }
    else
    {
      clearPrevOneShotCode();
    }
  }
#endif
  return ret;
}

// ワンショットリピートの終了処理
//  戻り値 : true  リピート処理を終了。以後の処理は省略してください
//           false リピート終了処理は発生せず。以後は通常の処理を続けます
static bool repeatOneShotEnd(int osSymb)
{
  bool ret = false;
#ifdef ONESHOT_DEF
  if (RepeatOneShotCode != 0)
  {
    if (RepeatOneShotCode == osSymb)
    {
      RepeatOneShotCode = 0;
      sendKey(osSymb, false);   // ワンショットキーを押しっぱなしを解除
      ret = true;
    }
  }
#endif
  return ret;
}

// ワンショットの実行
static void actionOneShot(int normSymb, int osSymb)
{
#ifdef ONESHOT_DEF 
  if ((OneShotReserveCode == osSymb) && (OneShotBaseCode == normSymb))
  {
    sendKey(OneShotReserveCode, true);
    sendKey(OneShotReserveCode, false);
    // 発行したワンショットキーは連射に備えて保存しておきます
    registPrevOneShotCode(OneShotReserveCode);
    clearOneShotReserve();
  }
#endif
}

// ワンショットの記録値が生きているか
static bool isPrevOneShotCodeActive()
{
  return PrevOneShotCode != 0;
}

// ワンショットの記録値を取得する
static int getPrevOneShotCode()
{
  return PrevOneShotCode;
}

// 実行したワンショットを登録する
static void registPrevOneShotCode(int prevCode)
{
  PrevOneShotCode = prevCode;
  PrevOneShotActiveCount = ROSAC_DEF;
}

// 実行したワンショットの記録をクリアする
static void clearPrevOneShotCode()
{
  PrevOneShotCode = 0;
  PrevOneShotActiveCount = 0;
}

// ワンショットの記録の有効期限チェック
static void  checkPrevOneShotCode()
{
  if (PrevOneShotActiveCount-- == 0)
  {
    PrevOneShotCode = 0;
  }
}

// ワンショットの予約  
static void reserveOneShot(int normSymb, int osSymb)
{
#ifdef ONESHOT_DEF
  if (osSymb != NOP_ || osSymb != NASB)
  {
    OneShotReserveCode = osSymb;
    OneShotBaseCode = normSymb;
  }
  else
  {
    // 次のキーが打たれたので予約はキャンセル
    clearOneShotReserve();
  }
#endif // ONESHOT_DEF
}

// ワンショットの予約をクリア
static void clearOneShotReserve()
{
  OneShotReserveCode = 0;
  OneShotBaseCode = 0;
}

// 発射
static void sendKey(int code, bool isOn)
{
  if (isOn)
  {
    Keyboard.press(code);
  }
  else
  {
    Keyboard.release(code);
  }
}

// 左右すべての押下中のキーをすべてクリアします
static void forceClear()
{
  for (int row = 0; row < ROWMAX; row++)
  {
    for (int col = 0; col < COLMAX; col++)
    {
      if (OldRKey[row][col] == ON)
      {
        Keyboard.release(getSymbol(row, col, Right));
      }
      if (OldLKey[row][col] == ON)
      {
        Keyboard.release(getSymbol(row, col, Left));
      }
    }
  }
}

// キーが今越されたかを判定する
static bool isTurnOn(int row, int col, LorR lr)
{
  bool ret = false;
  if (lr == Left)
  {
    ret = (OldLKey[row][col] == OFF) && (LKey[row][col] == ON);
  }
  else
  {
    ret = (OldRKey[row][col] == OFF) && (RKey[row][col] == ON);
  }
  return ret;
}

// キーが今離されたかを判定する
static bool isTurnOff(int row, int col, LorR lr)
{
  bool ret = false;
  if (lr == Left)
  {
    ret = (OldLKey[row][col] == ON) && (LKey[row][col] == OFF);
  }
  else
  {
    ret = (OldRKey[row][col] == ON) && (RKey[row][col] == OFF);
  }
  return ret;
}

// キーシンボルを取得
static int getSymbol(int row, int col, LorR lr)
{
  int ret = 0;
  if (lr == Left)
  {
    if (IsFnEnable)
    {
      ret = LFnSymbol[row][col];
    }
    else if (IsLayer1Enable)
    {
      ret = LLayer1Symbol[row][col];
    }
    else
    {
      ret = LSymbol[row][col];
    }
  }
  else
  {
    if (IsFnEnable)
    {
      ret = RFnSymbol[row][col];
    }
    else if (IsLayer1Enable)
    {
      ret = RLayer1Symbol[row][col];
    }
    else
    {
      ret = RSymbol[row][col];
    }
  }
  return ret;
}

// ワンショットシンボル取得
static int getOSymbol(int row, int col, LorR lr)
{
  int ret = 0;
  if (lr == Left)
  {
    ret = LOSymbol[row][col];
  }
  else
  {
    ret = ROSymbol[row][col];
  }
  return ret;
}
