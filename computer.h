#ifndef _COMPUTER_H_
#define _COMPUTER_H_

typedef struct
{

	D3DXVECTOR3 pos;		//場所
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;		//使用しているがどうか
	bool bUpMove;

} COMPUTER;
void SetComputer (D3DXVECTOR3 pos);
COMPUTER *GetCOMPUTER(void);
//マクロ定義
#define MAX_COMPUTER (6)
//プロトタイプ宣言
HRESULT InitComputer(void);
void UninitComputer(void);
void UpdateComputer(void);
void DrawComputer(void);
void ComputerMove (void);
extern bool bUseComputer ;
#endif