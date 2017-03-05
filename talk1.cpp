#include "main.h"
#include "talk1.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk1 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk1 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk1;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk1;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk1;		//�|���S���̈ړ���
int g_nCounterAnim_Talk1;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk1;		//�A�����[�V�����p�^�[��NO
float animRow_Talk1 =1.0f;
float maxAnimX_Talk1 = 1.0f;
float maxAnimY_Talk1 = 1.0f;
float Talk1Width = 800.0f;		//�|���S���̕�
float Talk1Height = 150.0f;
float Talk1_X = 160.0f;
float Talk1_Y = 600.0f;
float g_fLengthTalk1;		//�|���S���̑Ίp���̒���
float g_fAngleTalk1;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk1
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk1,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk1;
		g_pVtxBuffTalk1 ->Lock(0,0,(void **)&Talk1,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk1.png",
		&g_pTextureTalk1);

		bUseTalk1 = false;
		Talk1[0].pos = D3DXVECTOR3(Talk1_X,Talk1_Y,0.0f);
		Talk1[1].pos = D3DXVECTOR3(Talk1_X+Talk1Width,Talk1_Y,0.0f);
		Talk1[2].pos = D3DXVECTOR3(Talk1_X,Talk1_Y+Talk1Height,0.0f);
		Talk1[3].pos = D3DXVECTOR3(Talk1_X+Talk1Width,Talk1_Y+Talk1Height,0.0f);
		Talk1[0].rhw = 1.0f;
		Talk1[1].rhw = 1.0f;
		Talk1[2].rhw = 1.0f;
		Talk1[3].rhw = 1.0f;
		Talk1[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk1[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk1[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk1[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk1[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk1[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk1[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk1[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk1 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk1
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk1(void)
{
	if(g_pTextureTalk1!=NULL)
	{
		g_pTextureTalk1->Release();
		g_pTextureTalk1=NULL;
	}
	if(g_pVtxBuffTalk1!=NULL)
	{
		g_pVtxBuffTalk1->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk1=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk1
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk1(void)
{
	if(bUseTalk1 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk1);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk1,
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
//  �֐����@�FUpdateTalk11
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk1(void)
{
	if(bUseTalk1 == true)
	{
	}
}
