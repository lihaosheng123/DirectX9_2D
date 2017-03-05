#include "main.h"
#include "talk3.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk3 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk3 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk3;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk3;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk3;		//�|���S���̈ړ���
int g_nCounterAnim_Talk3;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk3;		//�A�����[�V�����p�^�[��NO
float animRow_Talk3 =1.0f;
float maxAnimX_Talk3 = 1.0f;
float maxAnimY_Talk3 = 1.0f;
float Talk3Width = 800.0f;		//�|���S���̕�
float Talk3Height = 150.0f;
float Talk3_X = 160.0f;
float Talk3_Y = 600.0f;
float g_fLengthTalk3;		//�|���S���̑Ίp���̒���
float g_fAngleTalk3;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk3
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk3(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk3,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk3;
		g_pVtxBuffTalk3 ->Lock(0,0,(void **)&Talk3,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk3.png",
		&g_pTextureTalk3);

		bUseTalk3 = false;
		Talk3[0].pos = D3DXVECTOR3(Talk3_X,Talk3_Y,0.0f);
		Talk3[1].pos = D3DXVECTOR3(Talk3_X+Talk3Width,Talk3_Y,0.0f);
		Talk3[2].pos = D3DXVECTOR3(Talk3_X,Talk3_Y+Talk3Height,0.0f);
		Talk3[3].pos = D3DXVECTOR3(Talk3_X+Talk3Width,Talk3_Y+Talk3Height,0.0f);
		Talk3[0].rhw = 1.0f;
		Talk3[1].rhw = 1.0f;
		Talk3[2].rhw = 1.0f;
		Talk3[3].rhw = 1.0f;
		Talk3[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk3[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk3[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk3[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk3[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk3[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk3[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk3[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk3 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk3
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk3(void)
{
	if(g_pTextureTalk3!=NULL)
	{
		g_pTextureTalk3->Release();
		g_pTextureTalk3=NULL;
	}
	if(g_pVtxBuffTalk3!=NULL)
	{
		g_pVtxBuffTalk3->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk3=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk3
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk3(void)
{
	if(bUseTalk3 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk3);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk3,
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
//  �֐����@�FUpdateTalk31
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk3(void)
{
	if(bUseTalk3 == true)
	{
	}
}
