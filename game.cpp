#include "main.h"
#include "polygon.h"
#include "bg.h"
#include "input.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
//=============================================================================
//  �֐����@�FInitGame
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitGame (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	Initbg();
	InitPolygon();				/*�|���S���`��̏�����*/
	InitScore();
	InitBullet();
}
//=============================================================================
//  �֐����@�FUninitGame
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitGame(void)
{
	Uninitbg();	//�I������
	UninitPolygon();	//�v���S���̏I������
	UninitScore();
	UnintBullet();
}
//=============================================================================
//  �֐����@�FDrawGame
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawGame(void)
{
	Drawbg();//�`�揈��
	DrawPolygon();//�v���S���̕`�揈��
	DrawScore();
	DrawBullet();
}
//=============================================================================
//  �֐����@�FUpdateGame
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateGame(void)
{
	MODE mode;
	mode = GetMode();
	Updatebg();//�X�V����
	UpdatePolygon();//�v���S���̍X�V����
	UpdateScore();
	UpdateBullet();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}