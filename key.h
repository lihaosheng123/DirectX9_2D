#ifndef _KEY_H_
#define _KEY_H_
//�}�N����`
#define MAX_KEY (3)
typedef struct
{

	D3DXVECTOR3 pos;		//�ꏊ
	D3DXVECTOR3 move;
	float fWidth;		//��
	float fHeight;		//����
} KEY;
//�v���g�^�C�v�錾
HRESULT InitKey(void);
void UninitKey(void);
void UpdateKey(void);
void DrawKey(void);
extern bool bKey ;
#endif