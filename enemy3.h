#ifndef _ENEMY3_H_
#define _ENEMY3_H_
typedef struct
{

	D3DXVECTOR3 pos;		//�ꏊ
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;		//�g�p���Ă��邪�ǂ���
	int nLifeenemy3;		//����
	bool bUpMove;

} ENEMY3;
void SetEnemy3 (D3DXVECTOR3 pos);
ENEMY3 *GetEnemy3(void);
//�}�N����`
#define MAX_ENEMY3 (6)
//�v���g�^�C�v�錾
HRESULT InitEnemy3(void);
void UninitEnemy3(void);
void UpdateEnemy3(void);
void DrawEnemy3(void);
void Enemy3Move (void);
extern bool bUseEnemy3;
extern bool bUseExplosion;
extern bool bUseExplosionenemy;
#endif