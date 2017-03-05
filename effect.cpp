#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT		"data/TEXTURE/effect000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#ifdef USE_TEXTURE_EFFECT
#define	NUM_VERTEX_CIRCLE	(4)			// ���_��
#define	NUM_POLYGON_CIRCLE	(2)			// �|���S����
#else
#define	NUM_VERTEX_CIRCLE	(16 + 2)	// ���_��
#define	NUM_POLYGON_CIRCLE	(16)		// �|���S����
#endif	

#define	MAX_EFFECT			(8000)		// �G�t�F�N�g�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posBase;	// ��ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	float fColAlphaValue;	// �F�ω���
	float fAngle;			// �p�x
	float fRadius;			// ���a
	float fRadiusValue;		// ���a�ω���
	D3DXVECTOR2 swingRate;	// �h��W��
	D3DXVECTOR2 swingWidth;	// �h�ꕝ
	D3DXVECTOR2 swingValue;	// �h�ꕝ�ω���
	int nLife;				// ���C�t
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffect(int nEffectID, D3DXVECTOR3 pos);
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade);
void SetRadiusEffect(int nEffectID, float fRadius);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

EFFECT					g_aEffect[MAX_EFFECT];		// �G�t�F�N�g�̃��[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fColAlphaValue = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].fRadius = 40.0f;
		g_aEffect[nCntEffect].fRadiusValue = 0.0f;
		g_aEffect[nCntEffect].swingRate.x = 0.0f;
		g_aEffect[nCntEffect].swingRate.y = 0.0f;
		g_aEffect[nCntEffect].swingWidth.x = 0.0f;
		g_aEffect[nCntEffect].swingWidth.y = 0.0f;
		g_aEffect[nCntEffect].swingValue.x = 0.0f;
		g_aEffect[nCntEffect].swingValue.y = 0.0f;
		g_aEffect[nCntEffect].nType = EFFECTTYPE_NORMAL;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

#ifdef USE_TEXTURE_EFFECT
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_EFFECT,			// �t�@�C���̖��O
								&g_pTextureEffect);		// �ǂݍ��ރ������[
#endif

	// ���_���̍쐬
	MakeVertexEffect(pDevice);

	return S_OK;
}

	//=============================================================================
	// �I������
	//=============================================================================
	void UninitEffect(void)
	{
		if(g_pTextureEffect != NULL)
		{// �e�N�X�`���̊J��
			g_pTextureEffect->Release();
			g_pTextureEffect = NULL;
		}

		if(g_pVtxBuffEffect != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffEffect->Release();
			g_pVtxBuffEffect = NULL;
		}
	}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == true)
		{// �G�t�F�N�g���g�p���Ȃ�`��
			pEffect->nLife--;
			if(pEffect->nLife <= 0)
			{// �G�t�F�N�g�����ł�����
				pEffect->bUse = false;
			}
			else
			{// �G�t�F�N�g�𒲐�
				// �F�̐ݒ�
				pEffect->col.a -= pEffect->fColAlphaValue;
				if(pEffect->col.a <= 0.0f)
				{
					pEffect->col.a = 0.0f;
				}
				SetColorEffect(nCntEffect, pEffect->col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

				// ���a�̐ݒ�
				pEffect->fRadius -= pEffect->fRadiusValue;
				if(pEffect->fRadius <= 0.0f)
				{
					pEffect->fRadius = 0.0f;
				}
				SetRadiusEffect(nCntEffect, pEffect->fRadius);

				// �h��(X����)�̐ݒ�
				pEffect->swingRate.x += D3DX_PI * pEffect->swingValue.x;
				if(pEffect->swingRate.x > D3DX_PI)
				{
					pEffect->swingRate.x -= D3DX_PI * 2.0f;
				}
				pEffect->pos.x = pEffect->posBase.x + sinf(pEffect->swingRate.x) * pEffect->swingWidth.x;

				// �h��(Y����)�̐ݒ�
				pEffect->swingRate.y += D3DX_PI * pEffect->swingValue.y;
				if(pEffect->swingRate.y > D3DX_PI)
				{
					pEffect->swingRate.y -= D3DX_PI * 2.0f;
				}
				pEffect->pos.y = pEffect->posBase.y + sinf(pEffect->swingRate.y) * pEffect->swingWidth.y;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	// �u�����h���Z����
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �|���S���̕`��
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p���Ȃ�`��
#ifdef USE_TEXTURE_EFFECT
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntEffect * NUM_VERTEX_CIRCLE), NUM_POLYGON_CIRCLE);
#else
			pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, (nCntEffect * NUM_VERTEX_CIRCLE), NUM_POLYGON_CIRCLE);
#endif
		}
	}

	// �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX_CIRCLE * MAX_EFFECT,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@
												FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffEffect,								// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))											// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

#ifdef USE_TEXTURE_EFFECT
		for(int cntTarget = 0; cntTarget < MAX_EFFECT; cntTarget++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aEffect[cntTarget].pos.x - cosf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[0].pos.y = g_aEffect[cntTarget].pos.y - sinf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aEffect[cntTarget].pos.x + cosf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[1].pos.y = g_aEffect[cntTarget].pos.y - sinf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aEffect[cntTarget].pos.x - cosf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[2].pos.y = g_aEffect[cntTarget].pos.y + sinf(D3DX_PI * 0.25f - g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aEffect[cntTarget].pos.x + cosf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[3].pos.y = g_aEffect[cntTarget].pos.y + sinf(D3DX_PI * 0.25f + g_aEffect[cntTarget].fAngle) * g_aEffect[cntTarget].fRadius;
			pVtx[3].pos.z = 0.0f;

			// rhw�̐ݒ�
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
#else
		for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
		{
			// ���_���W�̐ݒ�
			pVtx->pos.x = g_aEffect[nCntEffect].pos.x;
			pVtx->pos.y = g_aEffect[nCntEffect].pos.y;
			pVtx->pos.z = 0.0f;

			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
			pVtx->rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �P���_�ڂ̐F

			// �e�N�X�`�����W�̐ݒ�
			pVtx->tex = D3DXVECTOR2(0.0f, 0.0f);		// �P���_�ڂ̃e�N�X�`�����W

			pVtx++;

			for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
			{
				// ���_���W�̐ݒ�
				pVtx->pos.x = g_aEffect[nCntEffect].pos.x - sinf(ANGLE * nCntVtx) * g_aEffect[nCntEffect].fRadius;
				pVtx->pos.y = g_aEffect[nCntEffect].pos.y + cosf(ANGLE * nCntVtx) * g_aEffect[nCntEffect].fRadius;
				pVtx->pos.z = 0.0f;

				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
				pVtx->rhw = 1.0f;

				// ���_�J���[�̐ݒ�
				pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				pVtx->tex.x = 0.0f;
				pVtx->tex.y = 0.0f;
			}
		}
#endif

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect(int nEffectID, D3DXVECTOR3 pos)
{
	g_aEffect[nEffectID].pos = pos;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffectID * NUM_VERTEX_CIRCLE);

		// ���_���W�̐ݒ�
#ifdef USE_TEXTURE_EFFECT
		pVtx[0].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.z = 0.0f;
#else
		pVtx->pos.x = g_aEffect[nEffectID].pos.x;
		pVtx->pos.y = g_aEffect[nEffectID].pos.y;
		pVtx->pos.z = 0.0f;
		pVtx++;

		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			pVtx->pos.x = g_aEffect[nEffectID].pos.x - sinf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.y = g_aEffect[nEffectID].pos.y + cosf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.z = 0.0f;
		}
#endif

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade)
{
	g_aEffect[nEffectID].col = col;
	
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffectID * NUM_VERTEX_CIRCLE);

#ifdef USE_TEXTURE_EFFECT
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;
#else
		pVtx->col = col;
		pVtx++;

		// ���_�J���[�̐ݒ�
		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			pVtx->col = D3DXCOLOR(col.r * colFade.r, col.g * colFade.g, col.b * colFade.b, col.a * colFade.a);
		}
#endif

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// �T�C�Y�ݒ�
//=============================================================================
void SetRadiusEffect(int nEffectID, float fRadius)
{
	g_aEffect[nEffectID].fRadius = fRadius;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nEffectID * NUM_VERTEX_CIRCLE;

		// ���_���W�̐ݒ�
#ifdef USE_TEXTURE_EFFECT
		pVtx[0].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.y = g_aEffect[nEffectID].pos.y - sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aEffect[nEffectID].pos.x - cosf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f - g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aEffect[nEffectID].pos.x + cosf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.y = g_aEffect[nEffectID].pos.y + sinf(D3DX_PI * 0.25f + g_aEffect[nEffectID].fAngle) * g_aEffect[nEffectID].fRadius;
		pVtx[3].pos.z = 0.0f;
#else
		pVtx->pos.x = g_aEffect[nEffectID].pos.x;
		pVtx->pos.y = g_aEffect[nEffectID].pos.y;
		pVtx->pos.z = 0.0f;

		pVtx++;

		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			// ���_���W�̐ݒ�
			pVtx->pos.x = g_aEffect[nEffectID].pos.x - sinf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.y = g_aEffect[nEffectID].pos.y + cosf(ANGLE * nCntVtx) * g_aEffect[nEffectID].fRadius;
			pVtx->pos.z = 0.0f;
		}
#endif

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
int SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nType)
{
	EFFECT *pEffect;
	int nEffectID = -1;

	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == false)
		{
			// ���C�t�̐ݒ�
			pEffect->nLife = nLife;

			// �^�C�v�̐ݒ�
			pEffect->nType = nType;

			// ���_���W�̐ݒ�
			pEffect->posBase = pos;
			SetVertexEffect(nCntEffect, pos);

			// �ړ��ʂ̐ݒ�
			pEffect->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ���ˌ��̐ݒ�
			if(pEffect->nType == EFFECTTYPE_RANDOMCOLOR
			|| pEffect->nType == EFFECTTYPE_RANDOMCOLORSWING)
			{// �����_���J���[�̏ꍇ
#if 0
				int colR,colG,colB,colBase;

				colBase = 98;
				colR = rand() % colBase + 1;
				colBase = 99 - colR;
				colG = rand() % colBase + 1;
				colBase = 100 - (colR + colG);
				colB = colBase + 1;
				col.r = colR / 100.0f;
				col.g = colG / 100.0f;		// [(��)���̐��l��ύX����Ɨ΂̗v�f����������(0�`10)]
				col.b = colB / 100.0f;		// [(��)���̐��l��ύX����Ɛ̗v�f����������(0�`10)]
				col.a = 1.0f;
#else
				col.r = (float)(rand() % 50 + 1) / 100.0f;		// [(��)���̐��l��ύX����ƐԂ̗v�f����������(1�`100)]
				col.g = (float)(rand() % 50 + 1) / 100.0f;		// [(��)���̐��l��ύX����Ɨ΂̗v�f����������(1�`100)]
				col.b = (float)(rand() % 50 + 1) / 100.0f;		// [(��)���̐��l��ύX����Ɛ̗v�f����������(1�`100)]
				col.a = 1.0f;
#endif
			}
			pEffect->fColAlphaValue = 1.0f / nLife;
			SetColorEffect(nCntEffect, col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

			// ���a�̐ݒ�
			pEffect->fRadius = fRadius;
			pEffect->fRadiusValue = (fRadius * 0.55f) / nLife;
			SetRadiusEffect(nCntEffect, fRadius);

			switch(pEffect->nType)
			{
			case EFFECTTYPE_NORMAL:				// �ʏ�G�t�F�N�g
			case EFFECTTYPE_RANDOMCOLOR:		// �����_���J���[�G�t�F�N�g
				pEffect->swingRate.x = 
				pEffect->swingWidth.x = 
				pEffect->swingRate.x = 0.0f;
				pEffect->swingRate.y = 
				pEffect->swingWidth.y = 
				pEffect->swingRate.y = 0.0f;
				break;

			case EFFECTTYPE_SWING:				// �h��G�t�F�N�g
			case EFFECTTYPE_RANDOMCOLORSWING:	// �����_���J���[�h��G�t�F�N�g
				// �h��(X����)�̐ݒ� [(��)�����ŉ������̓����̐ݒ������]
				pEffect->swingRate.x = 0.0f;//(float)(rand() % 314 - 628) / 100.0f;
				pEffect->swingWidth.x = (float)(rand() % 80 + 40) / 10.0f;
				pEffect->swingValue.x = (float)(rand() % 60 + 30) / 1000.0f;

				// �h��(Y����)�̐ݒ� [(��)�����ŏc�����̓����̐ݒ������]
				pEffect->swingRate.y = 0.0f;//(float)(rand() % 314 - 628) / 100.0f;
				pEffect->swingWidth.y = (float)(rand() % 80 + 40) / 10.0f;
				pEffect->swingValue.y = (float)(rand() % 60 + 30) / 1000.0f;
				break;
			}

			pEffect->bUse = true;

			nEffectID = nCntEffect;
			break;
		}
	}

	return nEffectID;
}
