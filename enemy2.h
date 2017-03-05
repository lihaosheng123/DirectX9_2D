#ifndef _ENEMY2_H_
#define _ENEMY2_H_

typedef struct
{

	D3DXVECTOR3 pos;		//�ꏊ
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;		//�g�p���Ă��邪�ǂ���
	int nLifeenemy2;		//����
	bool bUpMove;

} ENEMY2;
void SetEnemy2 (D3DXVECTOR3 pos);
ENEMY2 *GetEnemy2(void);
//�}�N����`
#define MAX_ENEMY2 (6)
//�v���g�^�C�v�錾
HRESULT InitEnemy2(void);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
void Enemy2Move (void);
extern bool bUseEnemy2 ;
extern bool bUseExplosionenemy ;
#endif