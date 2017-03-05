#ifndef _PAUSE_H_
#define _PAUSE_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define PAUSE_CONTINUE_FILE		"data\\TEXTURE\\continue.png"
#define PAUSE_RETRY_FILE		"data\\TEXTURE\\retry.png"
#define PAUSE_QUIT_FILE			"data\\TEXTURE\\quit.png"

/*******************************************************************************
* �\���̒�`
*******************************************************************************/
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX
}PAUSE_MENU;

//�|�[�Y�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�|�[�Y�̈ʒu
	float fWidth;			//�|�[�Y�̕�
	float fHeight;			//�|�[�Y�̍�
	bool bUse;
}PAUSE;
typedef struct
{
	bool bUse;
}PAUSEUSE;

//�v���g�^�C�v�̐錾
HRESULT InitPause( void );
void UninitPause( void );
void UpdatePause( void );
void DrawPause( void );
PAUSEUSE *GetPause(void);
#endif