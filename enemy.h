#ifndef _ENEMY_H_
#define _ENEMY_H_
//���
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//�ʏ���
	ENEMYSTATE_DAMAGE ,		//�_���[�W���
	ENEMYSTATE_MAX
} ENEMYSTATE;

//���
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

//�ړ�
typedef enum
{
	ENEMYMOVE_1 = 0,		//1
	ENEMYMOVE_2,		//2
	ENEMYMOVE_MAX
} ENEMYMOVE;
typedef struct
{

	D3DXVECTOR3 pos;		//�ꏊ
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;		//�g�p���Ă��邪�ǂ���
	ENEMYSTATE state;		//���
	int nCounterState;		//��ԃJ�E���^
	int nLifeenemy;		//����
	bool bUpMove;
	CATTYPE type;		//���
} ENEMY;
void SetEnemy (D3DXVECTOR3 pos);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdxEnemy,int nDamage);
//�}�N����`
#define MAX_ENEMY (6)
//�v���g�^�C�v�錾
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void EnemyMove (void);
extern bool bUseEnemy ;
#endif