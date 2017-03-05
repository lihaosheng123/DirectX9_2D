#ifndef _BULLET_H_
#define _BULLET_H_
//É}ÉNÉçíËã`
#define BULLET_MAX (256)
HRESULT InitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void UnintBullet(void);
void SetBullet (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife);
extern bool bUsebg3 ;
#endif