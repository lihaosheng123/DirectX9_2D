#include "main.h"
#include "timebg.h"
#include "input.h"
#include "pause.h"
//�}�N����`
#define TIMEBG_MAX (2)
//�O���[�o���ϐ�
VERTEX_2D g_aTimebgtex[4];
LPDIRECT3DTEXTURE9 g_pTextureTimebg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimebg =NULL;	//���_�p�b�t�@�ւ̃|�C���^
int g_nTimebg;		//�X�R�A�̐�
int animMaxnumTimebg= 10;		//0~9
float maxTimebgX = 10.0f;
float maxTimebgY = 1.0f;
int g_nCounterAnimTimebg;		//�A�����[�V�����J�E���^
int g_nPatternAnimTimebg;		//�A�����[�V�����p�^�[��NO
float TimebgHeight = 60.0f;
float TimebgWidth = 40.0f;
float TimebgCoordX =500.0f;
float TimebgCoordY = 0.0f;
float animTimebg =1.0f;
float startAnimYTimebg = 0.0f;
int nTimebg [TIMEBG_MAX];
TIME g_time;
//=============================================================================
//  �֐����@�FInitTimebg
//  �@�\�T�v�F�X�R�A�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTimebg(void)
{
	g_time.time =0 ;
	g_time.frame = 0;
	g_nTimebg= 60;		//
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//����������
	g_nCounterAnimTimebg = 0;
	g_nPatternAnimTimebg = 0;
//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*TIMEBG_MAX),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTimebg,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffTimebg ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\timebg.png",
		&g_pTextureTimebg);
	for(int i= 0;i<TIMEBG_MAX;i++)
	{
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( TimebgCoordX+(i*TimebgWidth), TimebgCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( TimebgCoordX + TimebgWidth+(i*TimebgWidth), TimebgCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( TimebgCoordX+(i*TimebgWidth) , TimebgCoordY + TimebgHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( TimebgCoordX + TimebgWidth+(i*TimebgWidth), TimebgCoordY + TimebgHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//���_���i�[���[�N
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffTimebg ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  �֐����@�FUninitTimebg
//  �@�\�T�v�F�X�R�A�̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTimebg(void)
{

	if(g_pVtxBuffTimebg!=NULL)
	{
		g_pVtxBuffTimebg->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTimebg=NULL;
	}
	if(g_pTextureTimebg!=NULL)
	{
		g_pTextureTimebg->Release();
		g_pTextureTimebg=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTimebg
//  �@�\�T�v�F�X�R�A�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTimebg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTimebg);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTimebg,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<TIMEBG_MAX;i++)
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
//  �֐����@�FUpdateTimebg
//  �@�\�T�v�F�X�R�A�̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTimebg(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	if(g_time.frame>=60)
	{
		g_time.time ++;
		g_time.frame = 0;
		AddTimebg(-1);
	}
	else
	{
		g_time.frame++;
	}
	//nTimebg[0] =g_nTimebg / 10000000 % 100;		//�疜
	//nTimebg[1] =g_nTimebg / 1000000 % 10;		//100��
	//nTimebg[2] =g_nTimebg / 100000 % 10;		//10��
	//nTimebg[3] =g_nTimebg / 10000 % 10;		//1��
	//nTimebg[4] =g_nTimebg / 1000 % 10;		//1��
	//nTimebg[5] =g_nTimebg / 100 % 10;		//100
	nTimebg[0] =g_nTimebg / 10 % 10;		//10
	nTimebg[1] =g_nTimebg / 1 % 10;		//1
	VERTEX_2D *pVtx;
	g_pVtxBuffTimebg ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

	for(int i= 0;i<TIMEBG_MAX;i++)
	{

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i], 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i]+0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i], 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f*nTimebg[i]+0.1f,1.0f);

	}
		g_pVtxBuffTimebg ->Unlock();	//LOCK
	}
}
/*******************************************************************************
* �֐���:AddTimebg
* 
* ����  : value
* �߂�l: �i�V
*******************************************************************************/
void AddTimebg(int valueTimebg)
{	
	g_nTimebg +=valueTimebg;
}

