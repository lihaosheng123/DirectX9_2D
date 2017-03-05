#ifndef _COMPUTER_H_
#define _COMPUTER_H_

typedef struct
{

	D3DXVECTOR3 pos;		//�ꏊ
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;		//�g�p���Ă��邪�ǂ���
	bool bUpMove;

} COMPUTER;
void SetComputer (D3DXVECTOR3 pos);
COMPUTER *GetCOMPUTER(void);
//�}�N����`
#define MAX_COMPUTER (6)
//�v���g�^�C�v�錾
HRESULT InitComputer(void);
void UninitComputer(void);
void UpdateComputer(void);
void DrawComputer(void);
void ComputerMove (void);
extern bool bUseComputer ;
#endif