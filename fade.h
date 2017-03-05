#ifndef _FADE_H_
#define _FADE_H_
//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE =0,		//�������Ȃ�
	FADE_IN,		//�t�F�[�h�C��
	FADE_OUT,		//�t�F�[�h�A�E�h
	FADE_MAX
} FADE;
void SetFade(FADE fade,MODE modeNext);
FADE GetFade(void);
//�v���g�^�C�v�錾
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
#endif