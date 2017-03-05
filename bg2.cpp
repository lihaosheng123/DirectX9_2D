#include "main.h"
#include "bg2.h"
#include "enemy.h"
//�O���[�o���ϐ�
VERTEX_2D g_bg2[4];
LPDIRECT3DTEXTURE9 g_pTexturebg2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg2 =NULL;	//���_�p�b�t�@�ւ̃|�C���^

//=============================================================================
//  �֐����@�FInitbg2
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT Initbg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffbg2,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *bg2;
		g_pVtxBuffbg2 ->Lock(0,0,(void **)&bg2,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bg002.png",
		&g_pTexturebg2);
		bUseEnemy2 = true;
		bUsebg2 = true;
		bg2[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		bg2[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		bg2[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		bg2[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		bg2[0].rhw = 1.0f;
		bg2[1].rhw = 1.0f;
		bg2[2].rhw = 1.0f;
		bg2[3].rhw = 1.0f;
		bg2[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		bg2[1].col=D3DCOLOR_RGBA(200,200,200,255);
		bg2[2].col=D3DCOLOR_RGBA(200,200,200,255);
		bg2[3].col=D3DCOLOR_RGBA(200,200,200,255);

		bg2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		bg2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		bg2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		bg2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffbg2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitbg2
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void Uninitbg2(void)
{
	if(g_pTexturebg2!=NULL)
	{
		g_pTexturebg2->Release();
		g_pTexturebg2=NULL;
	}
	if(g_pVtxBuffbg2!=NULL)
	{
		g_pVtxBuffbg2->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffbg2=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawbg2
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void Drawbg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturebg2);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffbg2,
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
//  �֐����@�FUpdatebg21
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void Updatebg2(void)
{
}
