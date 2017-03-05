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
//  �֐����@�FInitGame
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitGame2 (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg2();
	InitDoor1();
	InitPolygon();/*�|���S���`��̏�����*/
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
//  �֐����@�FUninitGame
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitGame2(void)
{
	Uninitbg2();	//�I������
	UninitDoor1();
	UninitPolygon();	//�v���S���̏I������
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
//  �֐����@�FDrawGame
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawGame2(void)
{
	Drawbg2();//�`�揈��
	DrawDoor1();
	DrawPolygon();//�v���S���̕`�揈��
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
//  �֐����@�FUpdateGame
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateGame2(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg1();//�X�V����
	UpdatePolygon();//�v���S���̍X�V����
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