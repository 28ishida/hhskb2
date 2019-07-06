#include <arduino.h>
#include "sockCom.h"

static int WaitBuffer(int size);

/* 通信を確立させる */
bool InitConnection(LorR either)
{
  bool ret = false;
  Serial1.begin(9600);

  if ( either == Right )
  {
    Serial1.write('c');
    for ( int cnt = 0; cnt < 300; cnt++ )
    {
      int inputChar = Serial1.read();
      if ( inputChar == 'C' )
      {
        ret = true;
        break;
      }
      delay(10);
    }
  }
  else
  {
    while ( true )
    {
      int inputChar = Serial1.read();
      if ( inputChar == 'c' )
      {
        ret = true;
        break;
      }
      delay(10);
    }
    Serial1.write('C');
  }
  return ret;
}

/* 相手のキー状態を取得する */
int GetKeyStatus(char  ans[][COLMAX])
{
  int ret = -1;
  for ( int cnt = 0; cnt < 100; cnt++ )
  {
    int inputChar = Serial1.read();
    if ( inputChar == -1)
    {
      ret = 0;
      break;
    }
  }
  if ( ret == -1 )
  {
    // 100回読み出してもゴミが読める。今回はパースを諦めます
    return ret;
  }

  Serial1.write('g');
  if ( WaitBuffer(30) != 0)
  {
    // 30バイトデータを受信できなかった
    return -2;
  }

  for ( int cnt = 0; cnt < 5; cnt++ )
  {
    ReadData( ans[cnt], 6 );
  }
}

/* Serial1からデータをsizeバイト読み込む。*/
int ReadData( char* ans, int size )
{
  int ret = 0;
  {
    for ( int cnt = 0; cnt < size; cnt++ )
    {
      ans[cnt] = Serial1.read();
    }
  }
  return ret;
}

/* Serial1にデータを書き込む */
int WriteData( char* ans, int size )
{
  Serial1.write(ans, size);
}

/* バッファが規定バイト数貯まるのを100msec待つ。 */
static int WaitBuffer(int size)
{
  int ret = -1;
  for ( int cnt = 0; cnt < 100; cnt++ )
  {
    if ( Serial1.available() == size )
    {
      ret = 0;
      break;
    }
    if ( Serial1.available() > size )
    {
      ret = -2;
      break;
    }
    delay(1);
  }

  return ret;
}
