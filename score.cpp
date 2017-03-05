#include "main.h"
#include "score.h"
#include "input.h"
//�}�N����`
#define SCORE_MAX (4)
//�O���[�o���ϐ�
VERTEX_2D g_aScoretex[4];
LPDIRECT3DTEXTURE9 g_pTextureScore =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore =NULL;	//���_�p�b�t�@�ւ̃|�C���^
int g_nScore;		//�X�R�A�̐�
int animMaxnum = 10;		//0~9
float maxScoreX = 10.0f;
float maxScoreY = 1.0f;
int g_nCounterAnimScore;		//�A�����[�V�����J�E���^
int g_nPatternAnimScore;		//�A�����[�V�����p�^�[��NO
float ScoreHeight = 90.0f;
float ScoreWidth = 50.0f;
float ScoreCoordX = 1000.0f;
float ScoreCoordY = 0.0f;
float animScore =1.0f;
float startAnimY = 0.0f;
int nScore [SCORE_MAX];
//=============================================================================
//  �֐����@�FInitScore
//  �@�\�T�v�F�X�R�A�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitScore(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//����������
	g_nCounterAnimScore = 0;
	g_nPatternAnimScore = 0;
//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*SCORE_MAX),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffScore,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\score.png",
		&g_pTextureScore);
	for(int i= 0;i<SCORE_MAX;i++)
	{
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( ScoreCoordX+(i*ScoreWidth), ScoreCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( ScoreCoordX + ScoreWidth+(i*ScoreWidth), ScoreCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( ScoreCoordX+(i*ScoreWidth) , ScoreCoordY + ScoreHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( ScoreCoordX + ScoreWidth+(i*ScoreWidth), ScoreCoordY + ScoreHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//���_���i�[���[�N
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffScore ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  �֐����@�FUninitScore
//  �@�\�T�v�F�X�R�A�̏I������
//  �߂�l�@�F
//=============================================================================
void UninitScore(void)
{

	if(g_pVtxBuffScore!=NULL)
	{
		g_pVtxBuffScore->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffScore=NULL;
	}
	if(g_pTextureScore!=NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawScore
//  �@�\�T�v�F�X�R�A�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureScore);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffScore,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<SCORE_MAX;i++)
	{
	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  (0+4*i),		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);
	}
}
//=============================================================================
//  �֐����@�FUpdateScore
//  �@�\�T�v�F�X�R�A�̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateScore(void)
{
	if(GetKeyboardTrigger(DIK_SPACE) == true)
	{
		AddScore(1);
	}
	//nScore[0] =g_nScore / 10000000 % 100;		//�疜
	//nScore[1] =g_nScore / 1000000 % 10;		//100��
	//nScore[2] =g_nScore / 100000 % 10;		//10��
	//nScore[3] =g_nScore / 10000 % 10;		//1��
	nScore[0] =g_nScore / 1000 % 10;		//1��
	nScore[1] =g_nScore / 100 % 10;		//100
	nScore[2] =g_nScore / 10 % 10;		//10
	nScore[3] =g_nScore / 1 % 10;		//1
	VERTEX_2D *pVtx;
	g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

	for(int i= 0;i<SCORE_MAX;i++)
	{

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,1.0f);

	}
		g_pVtxBuffScore ->Unlock();	//LOCK
}
/*******************************************************************************
* �֐���:AddScore
* 
* ����  : value
* �߂�l: �i�V
*******************************************************************************/
void AddScore(int value)
{	
	g_nScore +=value;
}

