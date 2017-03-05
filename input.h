#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"
HRESULT InitKeyboard(HINSTANCE hInstance,HWND hWnd);
void UninitKeyboard(void);
void UpadateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger( int nKey );
bool GetKeyboardRelease( int nKey );
//bool GetKeyboardRepeat( int nKey );
#endif
