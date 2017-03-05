#include "main.h"
#include "polygon.h"
#include "bg3.h"
#include "input.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
#include "door.h"
#include "timebg.h"
#include "lifeenemy.h"
#include "life.h"
#include "bg3.h"
#include "jieshao.h"
#include "jieshaobg.h"
//=============================================================================
//  関数名　：InitGame
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitJieshao (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	InitJieshaobg();
	InitDoor1();
	InitPolygon();/*ポリゴン描画の初期化*/
	InitLife();
	InitLifeenemy();
	InitScore();
	InitTimebg();
}
//=============================================================================
//  関数名　：UninitGame
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitJieshao(void)
{
	UninitJieshaobg();	//終了処理
	UninitDoor1();
	UninitPolygon();	//プリゴンの終了処理
	UninitLife();
	UninitLifeenemy();
	UninitScore();
	UninitTimebg();
}
//=============================================================================
//  関数名　：DrawGame
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawJieshao(void)
{
	DrawJieshaobg();//描画処理
	DrawDoor1();
	DrawPolygon();//プリゴンの描画処理
	DrawLife();
	DrawLifeenemy();
	DrawScore();
	DrawTimebg();
}
//=============================================================================
//  関数名　：UpdateGame
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateJieshao(void)
{
	MODE mode;
	mode = GetMode();
	UpdateJieshaobg();//更新処理
	UpdatePolygon();//プリゴンの更新処理
	UpdateScore();
	UpdateTimebg();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}