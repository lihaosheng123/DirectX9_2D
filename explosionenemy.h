#ifndef _EXPLOSIONENEMY_H_
#define _EXPLOSIONENEMY_H_
//�}�N����`
#define MAX_EXPLOSIONENEMY (256)
//�v���g�^�C�v�錾
HRESULT InitExplosionenemy(void);
void UninitExplosionenemy(void);
void UpdateExplosionenemy(void);
void DrawExplosionenemy(void);
void SetExplosionenemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife);
extern bool bUseExplosionenemy ;
#endif