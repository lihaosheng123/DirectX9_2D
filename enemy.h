#ifndef _ENEMY_H_
#define _ENEMY_H_
//状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//通常状態
	ENEMYSTATE_DAMAGE ,		//ダメージ状態
	ENEMYSTATE_MAX
} ENEMYSTATE;

//種類
typedef enum
{
	CAT_1 = 0,		//1
	CAT_2,		//2
	CAT_3,		//3
	CAT_4,		//4
	CAT_5,		//5
	CAT_6,		//6
	CAT_7,		//7
	CAT_MAX
} CATTYPE;

//移動
typedef enum
{
	ENEMYMOVE_1 = 0,		//1
	ENEMYMOVE_2,		//2
	ENEMYMOVE_MAX
} ENEMYMOVE;
typedef struct
{

	D3DXVECTOR3 pos;		//場所
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;		//使用しているがどうか
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態カウンタ
	int nLifeenemy;		//寿命
	bool bUpMove;
	CATTYPE type;		//種類
} ENEMY;
void SetEnemy (D3DXVECTOR3 pos);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdxEnemy,int nDamage);
//マクロ定義
#define MAX_ENEMY (6)
//プロトタイプ宣言
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void EnemyMove (void);
extern bool bUseEnemy ;
#endif