#ifndef _PROP2_H_
#define _PROP2_H_

typedef struct
{

	D3DXVECTOR3 pos;		//場所
	D3DXVECTOR3 move;
	float fWidth;		//幅
	float fHeight;		//高さ
	int nCounterState;		//状態カウンタ
} PROP2;
//マクロ定義
#define MAX_PROP2 (5)
//プロトタイプ宣言
HRESULT InitProp2(void);
void UninitProp2(void);
void UpdateProp2(void);
void DrawProp2(void);
extern bool bProp2 ;
#endif