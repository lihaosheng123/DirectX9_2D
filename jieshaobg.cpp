#include "main.h"
#include "jieshaobg.h"
#include "key.h"
//�O���[�o���ϐ�
VERTEX_2D g_Jieshaobg[4];
LPDIRECT3DTEXTURE9 g_pTextureJieshaobg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffJieshaobg =NULL;	//���_�p�b�t�@�ւ̃|�C���^

//=============================================================================
//  �֐����@�FInitJieshaobg
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitJieshaobg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffJieshaobg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Jieshaobg;
		g_pVtxBuffJieshaobg ->Lock(0,0,(void **)&Jieshaobg,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\jieshao.png",
		&g_pTextureJieshaobg);
		jieshaobUse = true;
		Jieshaobg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Jieshaobg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		Jieshaobg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Jieshaobg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		Jieshaobg[0].rhw = 1.0f;
		Jieshaobg[1].rhw = 1.0f;
		Jieshaobg[2].rhw = 1.0f;
		Jieshaobg[3].rhw = 1.0f;
		Jieshaobg[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Jieshaobg[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Jieshaobg[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Jieshaobg[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Jieshaobg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Jieshaobg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Jieshaobg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Jieshaobg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffJieshaobg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitJieshaobg
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitJieshaobg(void)
{
	if(g_pTextureJieshaobg!=NULL)
	{
		g_pTextureJieshaobg->Release();
		g_pTextureJieshaobg=NULL;
	}
	if(g_pVtxBuffJieshaobg!=NULL)
	{
		g_pVtxBuffJieshaobg->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffJieshaobg=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawJieshaobg
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawJieshaobg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureJieshaobg);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffJieshaobg,
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
//  �֐����@�FUpdateJieshaobg1
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateJieshaobg(void)
{

}
