#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//マクロ定義
#define MAX_EXPLOSION (256)
//プロトタイプ宣言
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife);
extern bool bUseExplosion ;
#endif