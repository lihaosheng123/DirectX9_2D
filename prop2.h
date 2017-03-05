#ifndef _PROP2_H_
#define _PROP2_H_

typedef struct
{

	D3DXVECTOR3 pos;		//�ꏊ
	D3DXVECTOR3 move;
	float fWidth;		//��
	float fHeight;		//����
	int nCounterState;		//��ԃJ�E���^
} PROP2;
//�}�N����`
#define MAX_PROP2 (5)
//�v���g�^�C�v�錾
HRESULT InitProp2(void);
void UninitProp2(void);
void UpdateProp2(void);
void DrawProp2(void);
extern bool bProp2 ;
#endif