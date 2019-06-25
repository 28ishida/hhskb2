#pragma once

// �E��ʏ핶���̔z�u��`
static int RSymbol[ROWMAX][COLMAX] =
{
	{ '7',   '8',  '9',  '0',  '-',  '=', '\\', '`' },
	{ 'y',   'u',  'i',  'o',  'p',  '[',  ']', DELE },
	{ 'h',   'j',  'k',  'l',  ';', '\'', RET_, NASB },
	{ 'b',   'n',  'm',  ',',  '.',  '/', RSFT, Fn   },
	{ RCTL, RALT, SPC_, NASB, RGUI, NASB, NASB, NASB }		// oneshot�p
	//{ SPC_, RALT, SPC_, NASB, RGUI, NASB, NASB, NASB }	// �ʏ�p
};
 
// �E��p�t�@���N�V�����������V���{�� 
// �ʏ푤��Fn���`���Ă���ӏ��͂����ŕύX�o���܂���B
static int RFnSymbol[ROWMAX][COLMAX] =
{
	{ F7__, F8__, F9__, F10_, F11_, F12_, INST, DELE },
	{ NOP_, NOP_, PRTS, NOP_, NOP_, UP__, NOP_, BS__ },
	{ NOP_, NOP_, HOME, PUP_, LEFT, RIGT, NOP_, NASB },
	{ NOP_, NOP_, NOP_, END_, PDWN, DOWN, RSFT, Fn   },
	{ RCTL, RALT, RCTL, NASB, RGUI, NASB, NASB, NASB }
};

// �E��pLayer1�������V���{�� 
static int RLayer1Symbol[ROWMAX][COLMAX] =
{
	{ F7__, F8__, F9__, F10_, F11_, F12_, NOP_, NOP_ },
	{ NOP_,  '_', NOP_, NOP_,  '+', NOP_, NOP_, BS__ },
	{ LEFT, DOWN, UP__, RIGT, NOP_, NOP_, NOP_, NOP_ },
	{ '\\', NOP_,  '-', NOP_, NOP_, NOP_, NOP_, Fn   },
	{ NOP_, NOP_, NOP_, NASB, NOP_, NASB, NASB, NASB }
};

// �E�胏���V���b�g�L�[
// �C���L�[���P�Ƃŉ����ꂽ�Ƃ��ɓ��������V���b�g�L�[�B
// �ʏ�e�[�u�����C���L�[�ɂȂ��Ă��鏊�ɂ�����`�o���܂���B
static int ROSymbol[ROWMAX][COLMAX] =
{
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_ },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_ },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NASB },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_ },
	{ SPC_, NOP_, NOP_, NASB, NOP_, NASB, NASB, NASB },
};

// ����p�V���{��
static int LSymbol[ROWMAX][COLMAX] =
{
	{ ESC_, '1',  '2',  '3',  '4',  '5',  '6',  NASB },
	{ TAB_, 'q',  'w',  'e',  'r',  't',  NASB, NASB },
	{ LY1_, 'a',  's',  'd',  'f',  'g',  NASB, NASB },
	{ LSFT, 'z',  'x',  'c',  'v',  'b',  NASB, NASB },
	{ NASB, NASB, LGUI, NOP_, LALT, LCTL, NASB, NASB }
};

// ����pFn�������V���{��
// �ʏ푤��Fn���`���Ă���ӏ��͂����ŕύX�o���܂���B
static int LFnSymbol[ROWMAX][COLMAX] =
{
	{ ESC_, F1__, F2__, F3__, F4__, F5__, F6__, NASB },
	{ TAB_, NOP_, NOP_, NOP_, NOP_, NOP_, NASB, NASB },
	{ LY1_, NOP_, NOP_, NOP_, NOP_, NOP_, NASB, NASB },
	{ LSFT, NOP_, NOP_, NOP_, NOP_, NOP_, NASB, NASB },
	{ NASB, NASB, LGUI, NOP_, LALT, LCTL, NASB, NASB }
};

// ����pLayer1�������V���{�� 
static int LLayer1Symbol[ROWMAX][COLMAX] =
{
	{ ESC_, F1__, F2__, F3__, F4__, F5__, F6__, NASB },
	{ NOP_, '\'', NOP_,  '=',  '(',  ')', NOP_, NOP_ },
	{ LY1_, NOP_, NOP_,  '"',  '{',  '}', NOP_, NOP_ },
	{ NOP_, NOP_, NOP_, NOP_,  '[',  ']', NOP_, NOP_ },
	{ NASB, NASB, LGUI, NOP_, LALT, LCTL, NASB, NASB }
};

// ���胏���V���b�g�L�[
// �C���L�[���P�Ƃŉ����ꂽ�Ƃ��ɓ��������V���b�g�L�[�B
// �ʏ�e�[�u�����C���L�[�ɂȂ��Ă��鏊�ɂ�����`�o���܂���B
static int LOSymbol[ROWMAX][COLMAX] =
{
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NASB },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NASB, NASB },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NASB, NASB },
	{ NOP_, NOP_, NOP_, NOP_, NOP_, NOP_, NASB, NASB },
	{ NASB, NASB, NOP_, NOP_, NOP_, SPC_, NASB, NASB },
};
