#include "main.h"
#include "talk8.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk8 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk8 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk8;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk8;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk8;		//�|���S���̈ړ���
int g_nCounterAnim_Talk8;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk8;		//�A�����[�V�����p�^�[��NO
float animRow_Talk8 =1.0f;
float maxAnimX_Talk8 = 1.0f;
float maxAnimY_Talk8 = 1.0f;
float Talk8Width = 800.0f;		//�|���S���̕�
float Talk8Height = 150.0f;
float Talk8_X = 160.0f;
float Talk8_Y = 600.0f;
float g_fLengthTalk8;		//�|���S���̑Ίp���̒���
float g_fAngleTalk8;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk8
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk8(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk8,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk8;
		g_pVtxBuffTalk8 ->Lock(0,0,(void **)&Talk8,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk8.png",
		&g_pTextureTalk8);

		bUseTalk8 = false;
		Talk8[0].pos = D3DXVECTOR3(Talk8_X,Talk8_Y,0.0f);
		Talk8[1].pos = D3DXVECTOR3(Talk8_X+Talk8Width,Talk8_Y,0.0f);
		Talk8[2].pos = D3DXVECTOR3(Talk8_X,Talk8_Y+Talk8Height,0.0f);
		Talk8[3].pos = D3DXVECTOR3(Talk8_X+Talk8Width,Talk8_Y+Talk8Height,0.0f);
		Talk8[0].rhw = 1.0f;
		Talk8[1].rhw = 1.0f;
		Talk8[2].rhw = 1.0f;
		Talk8[3].rhw = 1.0f;
		Talk8[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk8[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk8[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk8[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk8[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk8[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk8[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk8[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk8 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk8
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk8(void)
{
	if(g_pTextureTalk8!=NULL)
	{
		g_pTextureTalk8->Release();
		g_pTextureTalk8=NULL;
	}
	if(g_pVtxBuffTalk8!=NULL)
	{
		g_pVtxBuffTalk8->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk8=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk8
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk8(void)
{
	if(bUseTalk8 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk8);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk8,
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
//  �֐����@�FUpdateTalk81
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk8(void)
{
	if(bUseTalk8 == true)
	{
	}
}
