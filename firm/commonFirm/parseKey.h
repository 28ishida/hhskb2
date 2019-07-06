#pragma once
#include "hhskb_firm.h"

// 実装されたキースイッチを読み取るモジュール

// 初期化
void InitParseKeyModule();

// 読み取り
int ParseKey(char ans[][COLMAX]);
