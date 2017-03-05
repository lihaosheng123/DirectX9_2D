#include "main.h"
#include "talk5.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk5 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk5 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk5;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk5;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk5;		//�|���S���̈ړ���
int g_nCounterAnim_Talk5;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk5;		//�A�����[�V�����p�^�[��NO
float animRow_Talk5 =1.0f;
float maxAnimX_Talk5 = 1.0f;
float maxAnimY_Talk5 = 1.0f;
float Talk5Width = 800.0f;		//�|���S���̕�
float Talk5Height = 150.0f;
float Talk5_X = 160.0f;
float Talk5_Y = 600.0f;
float g_fLengthTalk5;		//�|���S���̑Ίp���̒���
float g_fAngleTalk5;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk5
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk5(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk5,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk5;
		g_pVtxBuffTalk5 ->Lock(0,0,(void **)&Talk5,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk5.png",
		&g_pTextureTalk5);

		bUseTalk5 = false;
		Talk5[0].pos = D3DXVECTOR3(Talk5_X,Talk5_Y,0.0f);
		Talk5[1].pos = D3DXVECTOR3(Talk5_X+Talk5Width,Talk5_Y,0.0f);
		Talk5[2].pos = D3DXVECTOR3(Talk5_X,Talk5_Y+Talk5Height,0.0f);
		Talk5[3].pos = D3DXVECTOR3(Talk5_X+Talk5Width,Talk5_Y+Talk5Height,0.0f);
		Talk5[0].rhw = 1.0f;
		Talk5[1].rhw = 1.0f;
		Talk5[2].rhw = 1.0f;
		Talk5[3].rhw = 1.0f;
		Talk5[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk5[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk5[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk5[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk5[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk5[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk5[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk5[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk5 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk5
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk5(void)
{
	if(g_pTextureTalk5!=NULL)
	{
		g_pTextureTalk5->Release();
		g_pTextureTalk5=NULL;
	}
	if(g_pVtxBuffTalk5!=NULL)
	{
		g_pVtxBuffTalk5->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk5=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk5
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk5(void)
{
	if(bUseTalk5 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk5);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk5,
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
//  �֐����@�FUpdateTalk51
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk5(void)
{
	if(bUseTalk5 == true)
	{
	}
}
