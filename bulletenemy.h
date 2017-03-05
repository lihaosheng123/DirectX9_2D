#ifndef _BULLETENEMY_H_
#define _BULLETENEMY_H_
//É}ÉNÉçíËã`
#define BULLETENEMY_MAX (256)
HRESULT InitBulletEnemy(void);
void UpdateBulletEnemy(void);
void DrawBulletEnemy(void);
void UnintBulletEnemy(void);
void SetBulletEnemy (D3DXVECTOR3 posEnemy,D3DXVECTOR3 vecMoveEnemy,int nLifeEnemy);
extern bool bUseTalk ;
#endif