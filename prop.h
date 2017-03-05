#ifndef _PROP_H_
#define _PROP_H_


typedef struct
{

	D3DXVECTOR3 pos;		//�ꏊ
	D3DXVECTOR3 move;
	float fWidth;		//��
	float fHeight;		//����
	int nCounterState;		//��ԃJ�E���^
} PROP;
//�}�N����`
#define MAX_PROP (5)
//�v���g�^�C�v�錾
HRESULT InitProp(void);
void UninitProp(void);
void UpdateProp(void);
void DrawProp(void);
extern bool bProp ;
extern bool bPropUpdate ;
#endif