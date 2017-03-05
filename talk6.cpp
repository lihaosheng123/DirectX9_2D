#include "main.h"
#include "talk6.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk6 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk6 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk6;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk6;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk6;		//�|���S���̈ړ���
int g_nCounterAnim_Talk6;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk6;		//�A�����[�V�����p�^�[��NO
float animRow_Talk6 =1.0f;
float maxAnimX_Talk6 = 1.0f;
float maxAnimY_Talk6 = 1.0f;
float Talk6Width = 800.0f;		//�|���S���̕�
float Talk6Height = 150.0f;
float Talk6_X = 160.0f;
float Talk6_Y = 600.0f;
float g_fLengthTalk6;		//�|���S���̑Ίp���̒���
float g_fAngleTalk6;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk6
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk6(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk6,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk6;
		g_pVtxBuffTalk6 ->Lock(0,0,(void **)&Talk6,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk6.png",
		&g_pTextureTalk6);

		bUseTalk6 = false;
		Talk6[0].pos = D3DXVECTOR3(Talk6_X,Talk6_Y,0.0f);
		Talk6[1].pos = D3DXVECTOR3(Talk6_X+Talk6Width,Talk6_Y,0.0f);
		Talk6[2].pos = D3DXVECTOR3(Talk6_X,Talk6_Y+Talk6Height,0.0f);
		Talk6[3].pos = D3DXVECTOR3(Talk6_X+Talk6Width,Talk6_Y+Talk6Height,0.0f);
		Talk6[0].rhw = 1.0f;
		Talk6[1].rhw = 1.0f;
		Talk6[2].rhw = 1.0f;
		Talk6[3].rhw = 1.0f;
		Talk6[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk6[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk6[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk6[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk6[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk6[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk6[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk6[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk6 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk6
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk6(void)
{
	if(g_pTextureTalk6!=NULL)
	{
		g_pTextureTalk6->Release();
		g_pTextureTalk6=NULL;
	}
	if(g_pVtxBuffTalk6!=NULL)
	{
		g_pVtxBuffTalk6->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk6=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk6
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk6(void)
{
	if(bUseTalk6 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk6);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk6,
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
	
}
//=============================================================================
//  �֐����@�FUpdateTalk61
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk6(void)
{
	if(bUseTalk6 == true)
	{
	}
}
