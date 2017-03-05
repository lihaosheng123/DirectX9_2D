#include "main.h"
#include "polygon.h"
#include "bg3.h"
#include "input.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
#include "door.h"
#include "timebg.h"
#include "bulletenemy.h"
#include "avatar.h"
#include "talk.h"
#include "explosion.h"
#include "explosionenemy.h"
#include "lifeenemy.h"
#include "life.h"
#include "key.h"
#include "bg3.h"
#include "enemy3.h"
#include "caiquan.h"
//=============================================================================
//  関数名　：InitGame
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitGame3 (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg3();
	InitDoor1();
	InitPolygon();/*ポリゴン描画の初期化*/
	InitExplosion();
	InitExplosionenemy();
	InitEnemy3();
	InitBulletEnemy();
	InitBullet();
	InitCaiquan();
	InitLife();
	InitLifeenemy();
	InitScore();
	InitAvatar();
	InitTimebg();
}
//=============================================================================
//  関数名　：UninitGame
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitGame3(void)
{
	Uninitbg3();	//終了処理
	UninitDoor1();
	UnintBullet();
	UnintBulletEnemy();
	UninitPolygon();	//プリゴンの終了処理
	UninitExplosion();
	UninitExplosionenemy();
	UninitEnemy3();
	UninitLife();
	UninitCaiquan();
	UninitLifeenemy();
	UninitScore();
	UninitAvatar();
	UninitTimebg();
}
//=============================================================================
//  関数名　：DrawGame
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawGame3(void)
{
	Drawbg3();//描画処理
	DrawDoor1();
	DrawPolygon();//プリゴンの描画処理
	DrawEnemy3();
	DrawBullet();
	DrawBulletEnemy();
	DrawCaiquan();
	DrawExplosion();
	DrawExplosionenemy();
	DrawLife();
	DrawLifeenemy();
	DrawScore();
	DrawAvatar();
	DrawTimebg();
}
//=============================================================================
//  関数名　：UpdateGame
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateGame3(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg3();//更新処理
	UpdatePolygon();//プリゴンの更新処理
	UpdateBullet();
	UpdateBulletEnemy();
	UpdateCaiquan();
	UpdateEnemy3();
	UpdateExplosion();
	UpdateExplosionenemy();
	UpdateScore();
	UpdateAvatar();
	UpdateTimebg();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}