#ifndef _ENEMY2_H_
#define _ENEMY2_H_

typedef struct
{

	D3DXVECTOR3 pos;		//場所
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;		//使用しているがどうか
	int nLifeenemy2;		//寿命
	bool bUpMove;

} ENEMY2;
void SetEnemy2 (D3DXVECTOR3 pos);
ENEMY2 *GetEnemy2(void);
//マクロ定義
#define MAX_ENEMY2 (6)
//プロトタイプ宣言
HRESULT InitEnemy2(void);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
void Enemy2Move (void);
extern bool bUseEnemy2 ;
extern bool bUseExplosionenemy ;
#endif