#ifndef _EXPLOSIONENEMY_H_
#define _EXPLOSIONENEMY_H_
//マクロ定義
#define MAX_EXPLOSIONENEMY (256)
//プロトタイプ宣言
HRESULT InitExplosionenemy(void);
void UninitExplosionenemy(void);
void UpdateExplosionenemy(void);
void DrawExplosionenemy(void);
void SetExplosionenemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife);
extern bool bUseExplosionenemy ;
#endif