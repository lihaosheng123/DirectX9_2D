#include "main.h"
#include "bg.h"
//�O���[�o���ϐ�
VERTEX_2D g_bg[4];
LPDIRECT3DTEXTURE9 g_pTexturebg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitbg
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT Initbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffbg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *bg;
		g_pVtxBuffbg ->Lock(0,0,(void **)&bg,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\001.png",
		&g_pTexturebg);
		bg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		bg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		bg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		bg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		bg[0].rhw = 1.0f;
		bg[1].rhw = 1.0f;
		bg[2].rhw = 1.0f;
		bg[3].rhw = 1.0f;
		bg[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		bg[1].col=D3DCOLOR_RGBA(200,200,200,255);
		bg[2].col=D3DCOLOR_RGBA(200,200,200,255);
		bg[3].col=D3DCOLOR_RGBA(200,200,200,255);

		bg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		bg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		bg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		bg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffbg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitbg
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void Uninitbg(void)
{
	if(g_pTexturebg!=NULL)
	{
		g_pTexturebg->Release();
		g_pTexturebg=NULL;
	}
	if(g_pVtxBuffbg!=NULL)
	{
		g_pVtxBuffbg->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffbg=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawbg
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void Drawbg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturebg);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffbg,
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
//  �֐����@�FUpdatebg
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void Updatebg(void)
{

}
