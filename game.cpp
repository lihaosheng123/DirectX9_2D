#include "main.h"
#include "polygon.h"
#include "bg.h"
#include "input.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
//=============================================================================
//  関数名　：InitGame
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitGame (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg();
	InitPolygon();				/*ポリゴン描画の初期化*/
	InitScore();
	InitBullet();
}
//=============================================================================
//  関数名　：UninitGame
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitGame(void)
{
	Uninitbg();	//終了処理
	UninitPolygon();	//プリゴンの終了処理
	UninitScore();
	UnintBullet();
}
//=============================================================================
//  関数名　：DrawGame
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawGame(void)
{
	Drawbg();//描画処理
	DrawPolygon();//プリゴンの描画処理
	DrawScore();
	DrawBullet();
}
//=============================================================================
//  関数名　：UpdateGame
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateGame(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg();//更新処理
	UpdatePolygon();//プリゴンの更新処理
	UpdateScore();
	UpdateBullet();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}