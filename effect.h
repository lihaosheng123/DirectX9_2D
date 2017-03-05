
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*************************************
// �G�t�F�N�g�̎��
//*************************************
enum
{
	EFFECTTYPE_NORMAL = 0,			// �ʏ�G�t�F�N�g
	EFFECTTYPE_SWING,				// �h��G�t�F�N�g
	EFFECTTYPE_RANDOMCOLOR,			// �����_���J���[�G�t�F�N�g
	EFFECTTYPE_RANDOMCOLORSWING,	// �����_���J���[�h��G�t�F�N�g
	EFFECTTYPE_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

int SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nType);

#endif
