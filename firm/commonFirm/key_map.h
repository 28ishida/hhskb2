#pragma once

// 右手通常文字の配置定義
static int RSymbol[ROWMAX][COLMAX] =
{
	{ '6',   '7',  '8',  '9',  '0',  DELE },
	{ 'y',   'u',  'i',  'o',  'p',  '\\' },
	{ 'h',   'j',  'k',  'l',  ';',  RET_ },
	{ 'n',   'm',  ',',  '.',  '/',  RSFT },
	{ RCTL,  RALT, LY2, NASB, NASB, NASB }		// oneshot用
	// SPC_,   Fn,  RGUI, NASB, NASB, NASB },	// 通常用
};
 
// 右手用Raise押下時シンボル 
static int RLayer1Symbol[ROWMAX][COLMAX] =
{
  { F6__, F7__, F8__, F9__, F10_,  BS__ },
  { 'y',   '_',  PRTS, '-',  '+',  '\\' },
  { LEFT, DOWN, UP__, RIGT, 'l',  RET_ },
  { INST,  '-',  ',',  '.',  '/',  RSFT },
  { RCTL, RALT, LY2, NASB, NASB, NASB }    // oneshot用
};

// 右手用Lower押下時シンボル 
static int RLayer2Symbol[ROWMAX][COLMAX] =
{
  { '6',   '7',  '8',  '9',  '0',  DELE },
  { '6',   '7',  '8',  '9',  '0',  DELE },
  { 'h',   'j',  'k',  'l',  ';',  RET_ },
  { 'n',   'm',  ',',  '.',  '/',  RSFT },
  { RCTL,  RALT, LY2, NASB, NASB, NASB }    // oneshot用
};

// 右手ワンショットキー
// 修飾キーが単独で押されたときに動くワンショットキー。
// 通常テーブルが修飾キーになっている所にしか定義出来ません。
static int ROSymbol[ROWMAX][COLMAX] =
{
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_ },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_ },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_ },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_ },
	{ SPC_, NOP_, NOP_, NASB, NOP_, NASB },
};

// 左手用シンボル
static int LSymbol[ROWMAX][COLMAX] =
{
	{ ESC_, '1',  '2',  '3',  '4',  '5' },
	{ TAB_, 'q',  'w',  'e',  'r',  't' },
	{ LY1_, 'a',  's',  'd',  'f',  'g' },
	{ LSFT, 'z',  'x',  'c',  'v',  'b' },
	{ NASB, NASB, LGUI, NASB, LALT, LCTL },
};

// 左手用Raise押下時シンボル 
static int LLayer1Symbol[ROWMAX][COLMAX] =
{
	{ '`',  F1__, F2__, F3__, F4__, F5__ },
	{ NOP_, '\'', NOP_,  '=',  '(',  ')' },
	{ LY1_, '`', '\'',  '"',  '{',  '}'  },
	{ NOP_, NOP_, NOP_, NOP_,  '[',  ']' },
	{ NASB, NASB, LGUI, NOP_, LALT, LCTL },
};

static int LLayer2Symbol[ROWMAX][COLMAX]
{
  { ESC_, '1',  '2',  '3',  '4',  '5' },
  { TAB_, '1',  '2',  '3',  '4',  '5' },
  { LY1_, 'a',  's',  'd',  'f',  'g' },
  { LSFT, 'z',  'x',  'c',  'v',  'b' },
  { NASB, NASB, LGUI, NASB, LALT, LCTL },
};

// 左手ワンショットキー
// 修飾キーが単独で押されたときに動くワンショットキー。
// 通常テーブルが修飾キーになっている所にしか定義出来ません。
static int LOSymbol[ROWMAX][COLMAX] =
{
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_},
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_},
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_},
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_},
	{ NASB, NASB, NOP_, NOP_, NOP_, SPC_}
};
