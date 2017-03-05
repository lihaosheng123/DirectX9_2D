#ifndef _KEY_H_
#define _KEY_H_
//マクロ定義
#define MAX_KEY (3)
typedef struct
{

	D3DXVECTOR3 pos;		//場所
	D3DXVECTOR3 move;
	float fWidth;		//幅
	float fHeight;		//高さ
} KEY;
//プロトタイプ宣言
HRESULT InitKey(void);
void UninitKey(void);
void UpdateKey(void);
void DrawKey(void);
extern bool bKey ;
#endif