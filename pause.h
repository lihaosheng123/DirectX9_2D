#ifndef _PAUSE_H_
#define _PAUSE_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define PAUSE_CONTINUE_FILE		"data\\TEXTURE\\continue.png"
#define PAUSE_RETRY_FILE		"data\\TEXTURE\\retry.png"
#define PAUSE_QUIT_FILE			"data\\TEXTURE\\quit.png"

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX
}PAUSE_MENU;

//ポーズの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//ポーズの位置
	float fWidth;			//ポーズの幅
	float fHeight;			//ポーズの高
	bool bUse;
}PAUSE;
typedef struct
{
	bool bUse;
}PAUSEUSE;

//プロトタイプの宣言
HRESULT InitPause( void );
void UninitPause( void );
void UpdatePause( void );
void DrawPause( void );
PAUSEUSE *GetPause(void);
#endif