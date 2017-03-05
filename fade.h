#ifndef _FADE_H_
#define _FADE_H_
//フェードの状態
typedef enum
{
	FADE_NONE =0,		//向もしない
	FADE_IN,		//フェードイン
	FADE_OUT,		//フェードアウド
	FADE_MAX
} FADE;
void SetFade(FADE fade,MODE modeNext);
FADE GetFade(void);
//プロトタイプ宣言
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
#endif