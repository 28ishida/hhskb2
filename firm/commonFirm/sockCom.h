#pragma once

#include "hhskb_firm.h"

/* 通信を確立させる */
bool InitConnection(bool isServer);

/* 相手のキー状態を取得する */
int GetKeyStatus(char  ans[][COLMAX]);

/* データを書き込む */
int WriteData( char* ans, int size );

/* データを読み込む */
int ReadData( char* ans, int size );
