#include "main.h"
#include "bg1.h"
//�O���[�o���ϐ�
VERTEX_2D g_bg1[4];
LPDIRECT3DTEXTURE9 g_pTexturebg1 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg1 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitbg1
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT Initbg1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffbg1,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *bg1;
		g_pVtxBuffbg1 ->Lock(0,0,(void **)&bg1,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bg001.png",
		&g_pTexturebg1);
		bUsebg1 = true;
		bg1[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		bg1[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		bg1[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		bg1[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		bg1[0].rhw = 1.0f;
		bg1[1].rhw = 1.0f;
		bg1[2].rhw = 1.0f;
		bg1[3].rhw = 1.0f;
		bg1[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		bg1[1].col=D3DCOLOR_RGBA(200,200,200,255);
		bg1[2].col=D3DCOLOR_RGBA(200,200,200,255);
		bg1[3].col=D3DCOLOR_RGBA(200,200,200,255);

		bg1[0].tex = D3DXVECTOR2(0.0f,0.0f);
		bg1[1].tex = D3DXVECTOR2(1.0f,0.0f);
		bg1[2].tex = D3DXVECTOR2(0.0f,1.0f);
		bg1[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffbg1 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitbg1
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void Uninitbg1(void)
{
	if(g_pTexturebg1!=NULL)
	{
		g_pTexturebg1->Release();
		g_pTexturebg1=NULL;
	}
	if(g_pVtxBuffbg1!=NULL)
	{
		g_pVtxBuffbg1->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffbg1=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawbg1
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void Drawbg1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTexturebg1);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffbg1,
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
//  �֐����@�FUpdatebg11
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void Updatebg1(void)
{

}
