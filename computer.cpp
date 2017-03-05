#include "main.h"
#include "computer.h"
#include "bulletenemy.h"
//�O���[�o���ϐ�
COMPUTER g_aComputer[MAX_COMPUTER];
LPDIRECT3DTEXTURE9 g_pTextureComputer =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffComputer =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posComputer;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotComputer;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveComputer;		//�|���S���̈ړ���
int g_nCounterAnim_Computer;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Computer;		//�A�����[�V�����p�^�[��NO
float animRow_Computer =1.0f;
float maxAnimX_Computer = 2.0f;
float maxAnimY_Computer = 1.0f;
float g_fLengthComputer;		//�|���S���̑Ίp���̒���
float g_fAngleComputer;		//�|���S���̑Ίp���̊p�x
float move_Computer = 4.0f;		//�ړ���

float runSpeed_Computer = 3.0f;
int animMaxnum_Computer = 4;
float startAnimY_Computer = 0.0f;
//=============================================================================
//  �֐����@�FInitComputer
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitComputer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffComputer,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffComputer ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\computer.png",
		&g_pTextureComputer);
		 bUseComputer = true ;
		for(int i= 0;i<MAX_COMPUTER;i++)
		{
		g_aComputer[i].fHeight=90.0f;
		g_aComputer[i].fWidth=90.0f;
			//����������

		g_aComputer[i].pos.x = 950.0f;
		g_aComputer[i].pos.y = 220.0f;
		g_posComputer = D3DXVECTOR3(g_aComputer[i].pos.x,g_aComputer[i].pos.y,0.0f);
		}
			//��]����������
		g_rotComputer = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthComputer =sqrtf(g_aComputer[0].fWidth * g_aComputer[0].fWidth + g_aComputer[0].fHeight * g_aComputer[0].fHeight)*0.5f;
		g_fAngleComputer =atan2f(g_aComputer[0].fWidth,g_aComputer[0].fHeight)*0.5f;

		g_aComputer[0].bUse = true;
		g_aComputer[0].bUpMove = true;
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y - cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y - cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y + cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   g_aComputer[0].pos.y + cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
								   0.0f);

			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Computer,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);

		//���W�ϊ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
			
		//���_�F�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//���_���i�[���[�N
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

		g_pVtxBuffComputer ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitComputer
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitComputer(void)
{

	if(g_pVtxBuffComputer!=NULL)
	{
		g_pVtxBuffComputer->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffComputer=NULL;
	}
	if(g_pTextureComputer!=NULL)
	{
		g_pTextureComputer->Release();
		g_pTextureComputer=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawComputer
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawComputer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureComputer);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffComputer,
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
//=============================================================================
//  �֐����@�FUpdateComputer
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateComputer(void)
{

	VERTEX_2D *pVtx;
	g_pVtxBuffComputer ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^����

		if((g_aComputer[0].pos.x-g_aComputer[0].fWidth/5) <= 0)
		{
			g_aComputer[0].pos.x = (g_aComputer[0].fWidth/5);
		}
	
		if((g_aComputer[0].pos.x+g_aComputer[0].fWidth/3)>= SCREEN_WIDTH)
		{
			g_aComputer[0].pos.x = SCREEN_WIDTH+-(g_aComputer[0].fWidth/3);
		}

		if((g_aComputer[0].pos.y-g_aComputer[0].fHeight/5) <= 0)
		{
			g_aComputer[0].pos.y=(g_aComputer[0].fHeight/5);
		}

		if((g_aComputer[0].pos.y+g_aComputer[0].fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aComputer[0].pos.y = SCREEN_HEIGHT+-(g_aComputer[0].fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

		g_pVtxBuffComputer ->Unlock();	//LOCK


		if(  bUseComputer  ==false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffComputer ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
			
			pVtx[0].tex = D3DXVECTOR2(0.0f / maxAnimX_Computer, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Computer, 1.0f / maxAnimY_Computer);

			pVtx[0].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y - cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aComputer[0].pos.x - sinf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer - g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aComputer[0].pos.x + sinf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   g_aComputer[0].pos.y + cosf( g_fAngleComputer + g_rotComputer.z ) * g_fLengthComputer,
									   0.0f);
				g_pVtxBuffComputer ->Unlock();	//LOCK
				
		}
		else
		{
			ComputerMove();
		}


}

COMPUTER *GetComputer(void)
{
	return &g_aComputer[0];
}
void ComputerMove(void)
{
	if( g_aComputer[0].pos.y <= 210.0f)
	{
		if( bUseComputer  == true)
		{

	SetBulletEnemy(D3DXVECTOR3(g_aComputer[0].pos.x,g_aComputer[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-3.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aComputer[0].pos.x,g_aComputer[0].pos.y,0.0f) ,D3DXVECTOR3(10.0f,0.0f,0.0f),5);

		}
	g_aComputer[0].bUpMove =false;
	}
	else if(g_aComputer[0].pos.y >= 450.0f)
	{
		if( bUseComputer == true)
		{

	SetBulletEnemy(D3DXVECTOR3(g_aComputer[0].pos.x,g_aComputer[0].pos.y,0.0f) ,D3DXVECTOR3(10.0f,0.0f,0.0f),5);
		}
	g_aComputer[0].bUpMove = true;

	}

	if(g_aComputer[0].bUpMove == true)
	{
		g_aComputer[0].pos.y -= move_Computer;
	}
	else if(g_aComputer[0].bUpMove == false)
	{
		g_aComputer[0].pos.y += move_Computer;

	}
}
void SetComputer(D3DXVECTOR3 pos)
{
	for(int i = 0; i< MAX_COMPUTER; i++)
	{
		g_aComputer[i].pos.x = pos.x;
		g_aComputer[i].pos.y = pos.y;
		
	}
}