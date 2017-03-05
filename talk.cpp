#include "main.h"
#include "talk.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTalk =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTalk =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTalk;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotTalk;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveTalk;		//�|���S���̈ړ���
int g_nCounterAnim_Talk;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Talk;		//�A�����[�V�����p�^�[��NO
float animRow_Talk =1.0f;
float maxAnimX_Talk = 1.0f;
float maxAnimY_Talk = 1.0f;
float TalkWidth = 1200.0f;		//�|���S���̕�
float Talk_Y = 600.0f;
float g_fLengthTalk;		//�|���S���̑Ίp���̒���
float g_fAngleTalk;		//�|���S���̑Ίp���̊p�x
//=============================================================================
//  �֐����@�FInitTalk
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTalk(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTalk,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Talk;
		g_pVtxBuffTalk ->Lock(0,0,(void **)&Talk,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\talk.png",
		&g_pTextureTalk);

		bUseTalk = false;
		Talk[0].pos = D3DXVECTOR3(0.0f,Talk_Y,0.0f);
		Talk[1].pos = D3DXVECTOR3(0.0f+TalkWidth,Talk_Y,0.0f);
		Talk[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Talk[3].pos = D3DXVECTOR3(0.0f+TalkWidth,SCREEN_HEIGHT,0.0f);
		Talk[0].rhw = 1.0f;
		Talk[1].rhw = 1.0f;
		Talk[2].rhw = 1.0f;
		Talk[3].rhw = 1.0f;
		Talk[0].col=D3DCOLOR_RGBA(200,200,200,255);	//���_���i�[���[�N
		Talk[1].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk[2].col=D3DCOLOR_RGBA(200,200,200,255);
		Talk[3].col=D3DCOLOR_RGBA(200,200,200,255);

		Talk[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Talk[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Talk[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Talk[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTalk ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTalk
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTalk(void)
{
	if(g_pTextureTalk!=NULL)
	{
		g_pTextureTalk->Release();
		g_pTextureTalk=NULL;
	}
	if(g_pVtxBuffTalk!=NULL)
	{
		g_pVtxBuffTalk->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTalk=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTalk
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTalk(void)
{
	if(bUseTalk == true)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTalk);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTalk,
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
//  �֐����@�FUpdateTalk1
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTalk(void)
{
	if(bUseTalk == true)
	{
	}
}
