#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//�}�N����`
#define MAX_EXPLOSION (256)
//�v���g�^�C�v�錾
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife);
extern bool bUseExplosion ;
#endif