#include "main.h"
#include "talk4.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk4 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk4 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk4;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk4;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk4;		//�|���S���̈ړ���
int g_nCounterAnim_Talk4;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk4;		//�A�����[�V�����p�^�[��NO
float animRow_Talk4 =1.0f;
float maxAnimX_Talk4 = 1.0f;
float maxAnimY_Talk4 = 1.0f;
float Talk4Width = 800.0f;		//�|���S���̕�
float Talk4Height = 150.0f;
float Talk4_X = 160.0f;
float Talk4_Y = 600.0f;
float g_fLengthTalk4;		//�|���S���̑Ίp���̒���
float g_fAngleTalk4;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk4
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk4(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk4,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk4;
		g_pVtxBuffTalk4 ->Lock(0,0,(void **)&Talk4,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk4.png",
		&g_pTextureTalk4);

		bUseTalk4 = false;
		Talk4[0].pos = D3DXVECTOR3(Talk4_X,Talk4_Y,0.0f);
		Talk4[1].pos = D3DXVECTOR3(Talk4_X+Talk4Width,Talk4_Y,0.0f);
		Talk4[2].pos = D3DXVECTOR3(Talk4_X,Talk4_Y+Talk4Height,0.0f);
		Talk4[3].pos = D3DXVECTOR3(Talk4_X+Talk4Width,Talk4_Y+Talk4Height,0.0f);
		Talk4[0].rhw = 1.0f;
		Talk4[1].rhw = 1.0f;
		Talk4[2].rhw = 1.0f;
		Talk4[3].rhw = 1.0f;
		Talk4[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk4[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk4[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk4[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk4[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk4[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk4[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk4[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk4 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk4
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk4(void)
{
	if(g_pTextureTalk4!=NULL)
	{
		g_pTextureTalk4->Release();
		g_pTextureTalk4=NULL;
	}
	if(g_pVtxBuffTalk4!=NULL)
	{
		g_pVtxBuffTalk4->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk4=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk4
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk4(void)
{
	if(bUseTalk4 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk4);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk4,
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
//  �֐����@�FUpdateTalk41
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk4(void)
{
	if(bUseTalk4 == true)
	{
	}
}
