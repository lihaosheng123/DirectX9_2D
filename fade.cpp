#include "main.h"
#include "fade.h"
#include "input.h"
//�O���[�o���ϐ�
D3DXCOLOR g_colorFade;		//�t�F�[�h�F
FADE g_fade;		//�t�F�[�h�̏��
MODE g_modeNext;		//���̃��[�h
VERTEX_2D g_pfade[4];
LPDIRECT3DTEXTURE9 g_pTexturefade =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufffade =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitfade
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitFade(void)
{
	g_fade = FADE_IN;
	g_modeNext = MODE_TITLEHONG;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufffade,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *fade;
		g_pVtxBufffade ->Lock(0,0,(void **)&fade,0);		//���_���ւ̃|�C���^���擾

		g_colorFade = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);

		fade[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		fade[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		fade[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		fade[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		fade[0].rhw = 1.0f;
		fade[1].rhw = 1.0f;
		fade[2].rhw = 1.0f;
		fade[3].rhw = 1.0f;
		fade[0].col=g_colorFade;	//���_���i�[���[�N
		fade[1].col=g_colorFade;
		fade[2].col=g_colorFade;
		fade[3].col=g_colorFade;

		fade[0].tex = D3DXVECTOR2(0.0f,0.0f);
		fade[1].tex = D3DXVECTOR2(1.0f,0.0f);
		fade[2].tex = D3DXVECTOR2(0.0f,1.0f);
		fade[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBufffade ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitfade
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitFade(void)
{
	if(g_pTexturefade!=NULL)
	{
		g_pTexturefade->Release();
		g_pTexturefade=NULL;
	}
	if(g_pVtxBufffade!=NULL)
	{
		g_pVtxBufffade->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBufffade=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawfade
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturefade);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBufffade,
								0,
								sizeof(VERTEX_2D)
								);

	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  0,		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);
}
//=============================================================================
//  �֐����@�FUpdatefade
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateFade(void)
{
	if( g_fade == FADE_IN)
	{
		g_colorFade.a -= 0.01f;

		if( g_colorFade.a < 0.0f )
		{
			g_fade = FADE_NONE;
		}

	}
	else if( g_fade == FADE_OUT )
	{
		g_colorFade.a +=0.01f;
		if( g_colorFade.a >= 1.0f )
		{
			g_fade = FADE_IN;
			SetMode( g_modeNext);
		}
	}
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	g_pVtxBufffade -> Lock(0,0,(void**)&pVtx,0);

	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;
	g_pVtxBufffade -> Unlock();
}

//=============================================================================
//  �֐����@�FFADE GetFade(void)
//  �@�\�T�v�F
//  �߂�l�@�Fg_fade
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}
//=============================================================================
//  �֐����@�FSetFade
//  �@�\�T�v�F
//  �߂�l�@�F
//  �����@�FFADE fade,MODE modeNext
//=============================================================================
void SetFade(FADE fade,MODE modeNext)
{
	g_fade = fade;
	g_modeNext = modeNext;
}