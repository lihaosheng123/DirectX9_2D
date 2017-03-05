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
//  �֐����@�FInitGame
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitGame1 (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg1();
	InitDoor1();
	InitPolygon();/*�|���S���`��̏�����*/
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
//  �֐����@�FUninitGame
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitGame1(void)
{
	Uninitbg1();	//�I������
	UninitDoor1();
	UninitPolygon();	//�v���S���̏I������
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
//  �֐����@�FDrawGame
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawGame1(void)
{
	Drawbg1();//�`�揈��
	DrawDoor1();
	DrawPolygon();//�v���S���̕`�揈��
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
//  �֐����@�FUpdateGame
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateGame1(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg1();//�X�V����
	UpdatePolygon();//�v���S���̍X�V����
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