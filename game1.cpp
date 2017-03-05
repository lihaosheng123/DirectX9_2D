#include "main.h"
#include "polygon.h"
#include "bg1.h"
#include "input.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
#include "door.h"
#include "enemy.h"
#include "timebg.h"
#include "bulletenemy.h"
#include "avatar.h"
#include "talk.h"
#include "talk1.h"
#include "talk2.h"
#include "talk3.h"
#include "talk4.h"
#include "talk5.h"
#include "talk6.h"
#include "explosion.h"
#include "explosionenemy.h"
#include "lifeenemy.h"
#include "life.h"
#include "prop.h"
#include "key.h"
#include "effect.h"
//=============================================================================
//  関数名　：InitGame
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitGame1 (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg1();
	InitDoor1();
	InitPolygon();/*ポリゴン描画の初期化*/
	InitExplosion();
	InitExplosionenemy();
	InitEnemy();
	InitBulletEnemy();
	InitBullet();
	InitProp();
	InitLife();
	InitLifeenemy();
	InitScore();
	InitTalk();
	InitTalk1();
	InitTalk3();
	InitTalk2();
	InitTalk4();
	InitTalk5();
	InitTalk6();
	InitAvatar();
	InitTimebg();
	InitKey();

}
//=============================================================================
//  関数名　：UninitGame
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitGame1(void)
{
	Uninitbg1();	//終了処理
	UninitDoor1();
	UninitPolygon();	//プリゴンの終了処理
	UninitExplosion();
	UninitExplosionenemy();
	UninitEnemy();
	UninitLife();
	UninitLifeenemy();
	UnintBullet();
	UnintBulletEnemy();
		UninitProp();
	UninitScore();
	UninitTalk();
	UninitTalk1();
	UninitTalk2();
	UninitTalk3();
	UninitTalk4();
	UninitTalk5();
	UninitTalk6();
	UninitAvatar();
	UninitTimebg();
	UninitKey();

}
//=============================================================================
//  関数名　：DrawGame
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawGame1(void)
{
	Drawbg1();//描画処理
	DrawDoor1();
	DrawPolygon();//プリゴンの描画処理
	DrawEnemy();
	DrawBullet();
	DrawBulletEnemy();
	DrawExplosion();
	DrawExplosionenemy();
	DrawKey();
	DrawLife();
	DrawLifeenemy();
	DrawScore();
	DrawProp();
	DrawTalk();
	DrawTalk1();
	DrawTalk2();
	DrawTalk3();
	DrawTalk4();
	DrawTalk5();
	DrawTalk6();
	DrawAvatar();
	DrawTimebg();

}
//=============================================================================
//  関数名　：UpdateGame
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateGame1(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg1();//更新処理
	UpdatePolygon();//プリゴンの更新処理
	UpdateExplosion();
	UpdateExplosionenemy();
	UpdateBullet();
	UpdateBulletEnemy();
	UpdateKey();
	UpdateEnemy();
	UpdateProp();
	UpdateScore();
	UpdateTalk();
	UpdateTalk1();
	UpdateTalk2();
	UpdateTalk3();
	UpdateTalk4();
	UpdateTalk5();
	UpdateTalk6();
	UpdateAvatar();
	UpdateTimebg();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}