#include "main.h"
#include "talk2.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk2 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk2;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk2;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk2;		//�|���S���̈ړ���
int g_nCounterAnim_Talk2;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk2;		//�A�����[�V�����p�^�[��NO
float animRow_Talk2 =1.0f;
float maxAnimX_Talk2 = 1.0f;
float maxAnimY_Talk2 = 1.0f;
float Talk2Width = 800.0f;		//�|���S���̕�
float Talk2Height = 150.0f;
float Talk2_X = 160.0f;
float Talk2_Y = 600.0f;
float g_fLengthTalk2;		//�|���S���̑Ίp���̒���
float g_fAngleTalk2;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk2
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk2,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk2;
		g_pVtxBuffTalk2 ->Lock(0,0,(void **)&Talk2,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk2.png",
		&g_pTextureTalk2);

		bUseTalk2 = false;
		Talk2[0].pos = D3DXVECTOR3(Talk2_X,Talk2_Y,0.0f);
		Talk2[1].pos = D3DXVECTOR3(Talk2_X+Talk2Width,Talk2_Y,0.0f);
		Talk2[2].pos = D3DXVECTOR3(Talk2_X,Talk2_Y+Talk2Height,0.0f);
		Talk2[3].pos = D3DXVECTOR3(Talk2_X+Talk2Width,Talk2_Y+Talk2Height,0.0f);
		Talk2[0].rhw = 1.0f;
		Talk2[1].rhw = 1.0f;
		Talk2[2].rhw = 1.0f;
		Talk2[3].rhw = 1.0f;
		Talk2[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk2[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk2[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk2[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk2
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk2(void)
{
	if(g_pTextureTalk2!=NULL)
	{
		g_pTextureTalk2->Release();
		g_pTextureTalk2=NULL;
	}
	if(g_pVtxBuffTalk2!=NULL)
	{
		g_pVtxBuffTalk2->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk2=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk2
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk2(void)
{
	if(bUseTalk2 == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk2);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk2,
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
//  �֐����@�FUpdateTalk21
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk2(void)
{
	if(bUseTalk2 == true)
	{
	}
}
