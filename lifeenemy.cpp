#include "main.h"
#include "lifeenemy.h"
#include "score.h"
//�O���[�o���ϐ�
VERTEX_2D g_aLifeenemytex[4];
LPDIRECT3DTEXTURE9 g_pTextureLifeenemy =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeenemy =NULL;	//���_�p�b�t�@�ւ̃|�C���^
int g_nCounterAnim_Lifeenemy;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Lifeenemy;		//�A�����[�V�����p�^�[��NO
float animRow_Lifeenemy =1.0f;
int g_nLifeenemy;		//�X�R�A�̐�
float maxAnimX_Lifeenemy = 1.0f;
float maxAnimY_Lifeenemy = 1.0f;
int g_nCounterAnimLifeenemy;		//�A�����[�V�����J�E���^
int g_nPatternAnimLifeenemy;		//�A�����[�V�����p�^�[��NO
float LifeenemyHeight = 50.0f;
float LifeenemyWidth = 50.0f;
float LifeenemyCoordX = 600.0f;
float LifeenemyCoordY = 0.0f;
float animLifeenemy =1.0f;
float runSpeed_Lifeenemy = 1.0f;
int animMaxnum_Lifeenemy = 1;
float startAnimY_Lifeenemy = 0.0f;
int nLifeenemy = MAX_LIFEENMEY;
float LifeenemyX= 5.0f;
bool bUseLifechangeenemy = true;
//=============================================================================
//  �֐����@�FInitLifeenemy
//  �@�\�T�v�F�X�R�A�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitLifeenemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//����������
	g_nCounterAnimLifeenemy = 0;
	g_nPatternAnimLifeenemy = 0;
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*MAX_LIFEENMEY),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffLifeenemy,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffLifeenemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\lifeenemy.png",
		&g_pTextureLifeenemy);
		nLifeenemy =MAX_LIFEENMEY;
		bUseLifechangeenemy =true;
	for(int i= 0;i<MAX_LIFEENMEY;i++)
	{
		//UV�ݒ�
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Lifeenemy,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Lifeenemy);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Lifeenemy, 1.0f / maxAnimY_Lifeenemy);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX+(i*LifeenemyWidth)+(i*LifeenemyX), LifeenemyCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX + LifeenemyWidth+(i*LifeenemyWidth)+(i*LifeenemyX), LifeenemyCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX+(i*LifeenemyWidth)+(i*LifeenemyX) , LifeenemyCoordY + LifeenemyHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( LifeenemyCoordX + LifeenemyWidth+(i*LifeenemyWidth)+(i*LifeenemyX), LifeenemyCoordY + LifeenemyHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//���_���i�[���[�N
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffLifeenemy ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  �֐����@�FUninitLifeenemy
//  �@�\�T�v�F�X�R�A�̏I������
//  �߂�l�@�F
//=============================================================================
void UninitLifeenemy(void)
{

	if(g_pVtxBuffLifeenemy!=NULL)
	{
		g_pVtxBuffLifeenemy->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffLifeenemy=NULL;
	}
	if(g_pTextureLifeenemy!=NULL)
	{
		g_pTextureLifeenemy->Release();
		g_pTextureLifeenemy=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawLifeenemy
//  �@�\�T�v�F�X�R�A�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawLifeenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureLifeenemy);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffLifeenemy,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<nLifeenemy;i++)
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
//  �֐����@�FUpdateLifeenemy
//  �@�\�T�v�F�X�R�A�̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateLifeenemy(void)
{

	nLifeenemy=nLifeenemy--;

}
