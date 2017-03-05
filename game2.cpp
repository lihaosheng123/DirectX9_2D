#include "main.h"
#include "polygon.h"
#include "bg1.h"
#include "input.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
#include "door.h"
#include "timebg.h"
#include "bulletenemy.h"
#include "avatar.h"
#include "talk.h"
#include "talk1.h"
#include "talk2.h"
#include "explosion.h"
#include "explosionenemy.h"
#include "lifeenemy.h"
#include "life.h"
#include "prop2.h"
#include "key.h"
#include "bg2.h"
#include "enemy2.h"
#include "computer.h"
#include "talk7.h"
#include "talk8.h"
#include "talk9.h"
//=============================================================================
//  関数名　：InitGame
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitGame2 (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg2();
	InitDoor1();
	InitPolygon();/*ポリゴン描画の初期化*/
	InitExplosion();
	InitExplosionenemy();
	InitEnemy2();
	InitComputer();
	InitBulletEnemy();
	InitBullet();
	InitProp2();
	InitLife();
	InitLifeenemy();
	InitScore();
	InitTalk();
	InitTalk7();
	InitTalk8();
	InitTalk9();
	InitAvatar();
	InitTimebg();
}
//=============================================================================
//  関数名　：UninitGame
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitGame2(void)
{
	Uninitbg2();	//終了処理
	UninitDoor1();
	UninitPolygon();	//プリゴンの終了処理
	UninitExplosion();
	UninitExplosionenemy();
	UninitEnemy2();
	UninitComputer();
	UninitLife();
	UninitLifeenemy();
	UnintBullet();
	UnintBulletEnemy();
	UninitProp2();
	UninitScore();
	UninitTalk();
	UninitTalk7();
	UninitTalk8();
	UninitTalk9();
	UninitAvatar();
	UninitTimebg();
}
//=============================================================================
//  関数名　：DrawGame
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawGame2(void)
{
	Drawbg2();//描画処理
	DrawDoor1();
	DrawPolygon();//プリゴンの描画処理
	DrawEnemy2();
	DrawComputer();
	DrawBullet();
	DrawBulletEnemy();
	DrawExplosion();
	DrawExplosionenemy();
	DrawLife();
	DrawLifeenemy();
	DrawScore();
	DrawProp2();
	DrawTalk();
	DrawTalk7();
	DrawTalk8();
	DrawTalk9();
	DrawAvatar();
	DrawTimebg();
}
//=============================================================================
//  関数名　：UpdateGame
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateGame2(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg1();//更新処理
	UpdatePolygon();//プリゴンの更新処理
	UpdateExplosion();
	UpdateExplosionenemy();
	UpdateBullet();
	UpdateBulletEnemy();
	UpdateEnemy2();
	UpdateComputer();
	UpdateProp2();
	UpdateScore();
	UpdateTalk();
	UpdateTalk7();
	UpdateTalk8();
	UpdateTalk9();
	UpdateAvatar();
	UpdateTimebg();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}