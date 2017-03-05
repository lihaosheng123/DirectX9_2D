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
//  �֐����@�FInitGame
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitGame3 (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg3();
	InitDoor1();
	InitPolygon();/*�|���S���`��̏�����*/
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
//  �֐����@�FUninitGame
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitGame3(void)
{
	Uninitbg3();	//�I������
	UninitDoor1();
	UnintBullet();
	UnintBulletEnemy();
	UninitPolygon();	//�v���S���̏I������
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
//  �֐����@�FDrawGame
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawGame3(void)
{
	Drawbg3();//�`�揈��
	DrawDoor1();
	DrawPolygon();//�v���S���̕`�揈��
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
//  �֐����@�FUpdateGame
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateGame3(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg3();//�X�V����
	UpdatePolygon();//�v���S���̍X�V����
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