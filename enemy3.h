#ifndef _ENEMY3_H_
#define _ENEMY3_H_
typedef struct
{

	D3DXVECTOR3 pos;		//場所
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;		//使用しているがどうか
	int nLifeenemy3;		//寿命
	bool bUpMove;

} ENEMY3;
void SetEnemy3 (D3DXVECTOR3 pos);
ENEMY3 *GetEnemy3(void);
//マクロ定義
#define MAX_ENEMY3 (6)
//プロトタイプ宣言
HRESULT InitEnemy3(void);
void UninitEnemy3(void);
void UpdateEnemy3(void);
void DrawEnemy3(void);
void Enemy3Move (void);
extern bool bUseEnemy3;
extern bool bUseExplosion;
extern bool bUseExplosionenemy;
#endif