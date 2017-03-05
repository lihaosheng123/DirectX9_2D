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
//  �֐����@�FInitGame
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitJieshao (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	InitJieshaobg();
	InitDoor1();
	InitPolygon();/*�|���S���`��̏�����*/
	InitLife();
	InitLifeenemy();
	InitScore();
	InitTimebg();
}
//=============================================================================
//  �֐����@�FUninitGame
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitJieshao(void)
{
	UninitJieshaobg();	//�I������
	UninitDoor1();
	UninitPolygon();	//�v���S���̏I������
	UninitLife();
	UninitLifeenemy();
	UninitScore();
	UninitTimebg();
}
//=============================================================================
//  �֐����@�FDrawGame
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawJieshao(void)
{
	DrawJieshaobg();//�`�揈��
	DrawDoor1();
	DrawPolygon();//�v���S���̕`�揈��
	DrawLife();
	DrawLifeenemy();
	DrawScore();
	DrawTimebg();
}
//=============================================================================
//  �֐����@�FUpdateGame
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateJieshao(void)
{
	MODE mode;
	mode = GetMode();
	UpdateJieshaobg();//�X�V����
	UpdatePolygon();//�v���S���̍X�V����
	UpdateScore();
	UpdateTimebg();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}