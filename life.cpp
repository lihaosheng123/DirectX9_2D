#include "main.h"
#include "life.h"
//�O���[�o���ϐ�
VERTEX_2D g_aLifetex[4];
LPDIRECT3DTEXTURE9 g_pTextureLife =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife =NULL;	//���_�p�b�t�@�ւ̃|�C���^
int g_nCounterAnim_Life;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Life;		//�A�����[�V�����p�^�[��NO
float animRow_Life =1.0f;
int g_nLife;		//�X�R�A�̐�
float maxAnimX_Life = 6.0f;
float maxAnimY_Life = 1.0f;
int g_nCounterAnimLife;		//�A�����[�V�����J�E���^
int g_nPatternAnimLife;		//�A�����[�V�����p�^�[��NO
float LifeHeight = 120.0f;
float LifeWidth = 130.0f;
float LifeCoordX = 0.0f;
float LifeCoordY = 0.0f;
float animLife =1.0f;
float runSpeed_Life = 1.0f;
int animMaxnum_Life = 6;
float startAnimY_Life = 0.0f;
int nLife = MAX_LIFE;
float LifeX= 10.0f;
//=============================================================================
//  �֐����@�FInitLife
//  �@�\�T�v�F�X�R�A�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitLife(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//����������
	g_nCounterAnimLife = 0;
	g_nPatternAnimLife = 0;
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*MAX_LIFE),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffLife,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
		g_pVtxBuffLife ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\life.png",
		&g_pTextureLife);
		nLife =MAX_LIFE;
	for(int i= 0;i<MAX_LIFE;i++)
	{
		//UV�ݒ�
		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Life,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Life);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(1.0f / maxAnimX_Life, 1.0f / maxAnimY_Life);

		pVtx[0+(4*i)].pos = D3DXVECTOR3( LifeCoordX+(i*LifeWidth)+(i*LifeX), LifeCoordY, 0.0f);
		pVtx[1+(4*i)].pos = D3DXVECTOR3( LifeCoordX + LifeWidth+(i*LifeWidth)+(i*LifeX), LifeCoordY, 0.0f);
		pVtx[2+(4*i)].pos = D3DXVECTOR3( LifeCoordX+(i*LifeWidth)+(i*LifeX) , LifeCoordY + LifeHeight, 0.0f);
		pVtx[3+(4*i)].pos = D3DXVECTOR3( LifeCoordX + LifeWidth+(i*LifeWidth)+(i*LifeX), LifeCoordY + LifeHeight, 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//���_���i�[���[�N
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		}
		g_pVtxBuffLife ->Unlock();	//LOCK

		return S_OK;
}
//=============================================================================
//  �֐����@�FUninitLife
//  �@�\�T�v�F�X�R�A�̏I������
//  �߂�l�@�F
//=============================================================================
void UninitLife(void)
{

	if(g_pVtxBuffLife!=NULL)
	{
		g_pVtxBuffLife->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffLife=NULL;
	}
	if(g_pTextureLife!=NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawLife
//  �@�\�T�v�F�X�R�A�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureLife);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffLife,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<nLife;i++)
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
//  �֐����@�FUpdateLife
//  �@�\�T�v�F�X�R�A�̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateLife(void)
{
	nLife--;
}