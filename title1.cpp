#include "main.h"
#include "title1.h"
#include "title.h"
#include "press.h"
#include "sound.h"
#include "fade.h"
//=============================================================================
//  関数名　：InitTitle1
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitTitle1 (void)
{
	PlaySound(SOUND_LABEL_BGM000);
	StopSound(SOUND_LABEL_BGM002);
	InitTitle();
	InitPress();
}
//=============================================================================
//  関数名　：UninitTitle1
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTitle1(void)
{
	UninitTitle();
	UninitPress();

}
//=============================================================================
//  関数名　：DrawTitle1
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTitle1(void)
{
	DrawTitle();
	DrawPress();
}
//=============================================================================
//  関数名　：UpdateTitle1
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTitle1(void)
{
	MODE mode;
	mode = GetMode();
	UpdateTitle();
	UpdatePress();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}