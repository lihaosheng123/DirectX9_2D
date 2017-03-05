#include "main.h"
#include "talk9.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk9 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk9 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk9;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk9;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk9;		//�|���S���̈ړ���
int g_nCounterAnim_Talk9;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk9;		//�A�����[�V�����p�^�[��NO
float animRow_Talk9 =1.0f;
float maxAnimX_Talk9 = 1.0f;
float maxAnimY_Talk9 = 1.0f;
float Talk9Width = 500.0f;		//�|���S���̕�
float Talk9Height = 100.0f;
float Talk9_X = 300.0f;
float Talk9_Y = 600.0f;
float g_fLengthTalk9;		//�|���S���̑Ίp���̒���
float g_fAngleTalk9;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk9
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk9(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk9,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk9;
		g_pVtxBuffTalk9 ->Lock(0,0,(void **)&Talk9,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk9.png",
		&g_pTextureTalk9);

		bUseTalk9 = false;
		Talk9[0].pos = D3DXVECTOR3(Talk9_X,Talk9_Y,0.0f);
		Talk9[1].pos = D3DXVECTOR3(Talk9_X+Talk9Width,Talk9_Y,0.0f);
		Talk9[2].pos = D3DXVECTOR3(Talk9_X,Talk9_Y+Talk9Height,0.0f);
		Talk9[3].pos = D3DXVECTOR3(Talk9_X+Talk9Width,Talk9_Y+Talk9Height,0.0f);
		Talk9[0].rhw = 1.0f;
		Talk9[1].rhw = 1.0f;
		Talk9[2].rhw = 1.0f;
		Talk9[3].rhw = 1.0f;
		Talk9[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk9[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk9[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk9[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk9[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk9[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk9[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk9[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk9 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk9
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk9(void)
{
	if(g_pTextureTalk9!=NULL)
	{
		g_pTextureTalk9->Release();
		g_pTextureTalk9=NULL;
	}
	if(g_pVtxBuffTalk9!=NULL)
	{
		g_pVtxBuffTalk9->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk9=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk9
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk9(void)
{
	if(bUseTalk9 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk9);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk9,
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
//  �֐����@�FUpdateTalk91
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk9(void)
{
	if(bUseTalk9 == true)
	{
	}
}
