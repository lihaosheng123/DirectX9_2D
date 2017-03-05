#include "main.h"
#include "talk7.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk7 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk7 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk7;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk7;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk7;		//�|���S���̈ړ���
int g_nCounterAnim_Talk7;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk7;		//�A�����[�V�����p�^�[��NO
float animRow_Talk7 =1.0f;
float maxAnimX_Talk7 = 1.0f;
float maxAnimY_Talk7 = 1.0f;
float Talk7Width = 800.0f;		//�|���S���̕�
float Talk7Height = 150.0f;
float Talk7_X = 160.0f;
float Talk7_Y = 600.0f;
float g_fLengthTalk7;		//�|���S���̑Ίp���̒���
float g_fAngleTalk7;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk7
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk7(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk7,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk7;
		g_pVtxBuffTalk7 ->Lock(0,0,(void **)&Talk7,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\Talk7.png",
		&g_pTextureTalk7);

		bUseTalk7 = false;
		Talk7[0].pos = D3DXVECTOR3(Talk7_X,Talk7_Y,0.0f);
		Talk7[1].pos = D3DXVECTOR3(Talk7_X+Talk7Width,Talk7_Y,0.0f);
		Talk7[2].pos = D3DXVECTOR3(Talk7_X,Talk7_Y+Talk7Height,0.0f);
		Talk7[3].pos = D3DXVECTOR3(Talk7_X+Talk7Width,Talk7_Y+Talk7Height,0.0f);
		Talk7[0].rhw = 1.0f;
		Talk7[1].rhw = 1.0f;
		Talk7[2].rhw = 1.0f;
		Talk7[3].rhw = 1.0f;
		Talk7[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk7[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk7[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk7[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk7[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk7[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk7[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk7[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk7 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk7
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk7(void)
{
	if(g_pTextureTalk7!=NULL)
	{
		g_pTextureTalk7->Release();
		g_pTextureTalk7=NULL;
	}
	if(g_pVtxBuffTalk7!=NULL)
	{
		g_pVtxBuffTalk7->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk7=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk7
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk7(void)
{
	if(bUseTalk7 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk7);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk7,
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
//  �֐����@�FUpdateTalk71
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk7(void)
{
	if(bUseTalk7 == true)
	{
	}
}
