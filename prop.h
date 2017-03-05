#ifndef _PROP_H_
#define _PROP_H_


typedef struct
{

	D3DXVECTOR3 pos;		//場所
	D3DXVECTOR3 move;
	float fWidth;		//幅
	float fHeight;		//高さ
	int nCounterState;		//状態カウンタ
} PROP;
//マクロ定義
#define MAX_PROP (5)
//プロトタイプ宣言
HRESULT InitProp(void);
void UninitProp(void);
void UpdateProp(void);
void DrawProp(void);
extern bool bProp ;
extern bool bPropUpdate ;
#endif