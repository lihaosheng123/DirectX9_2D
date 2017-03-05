#include "main.h"
#include "title1.h"
#include "title.h"
#include "press.h"
#include "sound.h"
#include "fade.h"
//=============================================================================
//  �֐����@�FInitTitle1
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitTitle1 (void)
{
	PlaySound(SOUND_LABEL_BGM000);
	StopSound(SOUND_LABEL_BGM002);
	InitTitle();
	InitPress();
}
//=============================================================================
//  �֐����@�FUninitTitle1
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTitle1(void)
{
	UninitTitle();
	UninitPress();

}
//=============================================================================
//  �֐����@�FDrawTitle1
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTitle1(void)
{
	DrawTitle();
	DrawPress();
}
//=============================================================================
//  �֐����@�FUpdateTitle1
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTitle1(void)
{
	MODE mode;
	mode = GetMode();
	UpdateTitle();
	UpdatePress();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	mode = MODE_RESULT;
	//	SetMode(mode);
	//}

}