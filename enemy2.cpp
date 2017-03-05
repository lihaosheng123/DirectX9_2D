#include "main.h"
#include "enemy2.h"
#include "input.h"
#include "bulletEnemy.h"
#include "explosion.h"
//�O���[�o���ϐ�
ENEMY2 g_aEnemy2[MAX_ENEMY2];
LPDIRECT3DTEXTURE9 g_pTextureEnemy2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy2 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posEnemy2;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotEnemy2;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveEnemy2;		//�|���S���̈ړ���
int g_nCounterAnim_Enemy2;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Enemy2;		//�A�����[�V�����p�^�[��NO
float animRow_Enemy2 =1.0f;
float maxAnimX_Enemy2 = 7.0f;
float maxAnimY_Enemy2 = 1.0f;
float g_fLengthEnemy2;		//�|���S���̑Ίp���̒���
float g_fAngleEnemy2;		//�|���S���̑Ίp���̊p�x
float move_Enemy2 = 3.0f;		//�ړ���

float runSpeed_Enemy2 = 3.0f;
int animMaxnum_Enemy2 = 4;
float startAnimY_Enemy2 = 0.0f;
//=============================================================================
//  �֐����@�FInitEnemy2
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffEnemy2,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy2 ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\cat.png",
		&g_pTextureEnemy2);
		 bUseEnemy2 = true;
		for(int i= 0;i<MAX_ENEMY2;i++)
		{
		g_aEnemy2[i].nLifeenemy2 = 5;
		g_aEnemy2[i].fHeight=25.0f;
		g_aEnemy2[i].fWidth=170.0f;
			//����������

		g_aEnemy2[i].pos.x = 900.0f;
		g_aEnemy2[i].pos.y = 220.0f;
		g_posEnemy2 = D3DXVECTOR3(g_aEnemy2[i].pos.x,g_aEnemy2[i].pos.y,0.0f);
		}
			//��]����������
		g_rotEnemy2 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthEnemy2 =sqrtf(g_aEnemy2[0].fWidth * g_aEnemy2[0].fWidth + g_aEnemy2[0].fHeight * g_aEnemy2[0].fHeight)*0.5f;
		g_fAngleEnemy2 =atan2f(g_aEnemy2[0].fWidth,g_aEnemy2[0].fHeight)*0.5f;

		g_aEnemy2[0].bUse = true;
		g_aEnemy2[0].bUpMove = true;
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
								   0.0f);

			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);

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

		g_pVtxBuffEnemy2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitEnemy2
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitEnemy2(void)
{

	if(g_pVtxBuffEnemy2!=NULL)
	{
		g_pVtxBuffEnemy2->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffEnemy2=NULL;
	}
	if(g_pTextureEnemy2!=NULL)
	{
		g_pTextureEnemy2->Release();
		g_pTextureEnemy2=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawEnemy2
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawEnemy2(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureEnemy2);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffEnemy2,
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
//  �֐����@�FUpdateEnemy2
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateEnemy2(void)
{
	if( bUseEnemy2 == true)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2 ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

		Enemy2Move();


		if((g_aEnemy2[0].pos.x-g_aEnemy2[0].fWidth/5) <= 0)
		{
			g_aEnemy2[0].pos.x = (g_aEnemy2[0].fWidth/5);
		}
	
		if((g_aEnemy2[0].pos.x+g_aEnemy2[0].fWidth/3)>= SCREEN_WIDTH)
		{
			g_aEnemy2[0].pos.x = SCREEN_WIDTH+-(g_aEnemy2[0].fWidth/3);
		}

		if((g_aEnemy2[0].pos.y-g_aEnemy2[0].fHeight/5) <= 0)
		{
			g_aEnemy2[0].pos.y=(g_aEnemy2[0].fHeight/5);
		}

		if((g_aEnemy2[0].pos.y+g_aEnemy2[0].fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aEnemy2[0].pos.y = SCREEN_HEIGHT+-(g_aEnemy2[0].fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

		g_pVtxBuffEnemy2 ->Unlock();	//LOCK

	}
		if(  bUseEnemy2  ==false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffEnemy2 ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
			bUseExplosionenemy = false;
			pVtx[0].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);
			pVtx[3].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy2, 1.0f / maxAnimY_Enemy2);

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y - cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x - sinf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 - g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy2[0].pos.x + sinf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   g_aEnemy2[0].pos.y + cosf( g_fAngleEnemy2 + g_rotEnemy2.z ) * g_fLengthEnemy2,
									   0.0f);
				g_pVtxBuffEnemy2 ->Unlock();	//LOCK
				
		}


}

ENEMY2 *GetEnemy2(void)
{
	return &g_aEnemy2[0];
}
void Enemy2Move(void)
{
	if( g_aEnemy2[0].pos.y <= 210.0f)
	{
		g_aEnemy2[0].bUpMove =false;
		bUseExplosion=false;
		bUseExplosionenemy = false;
	}
	else if(g_aEnemy2[0].pos.y >= 450.0f)
	{
		g_aEnemy2[0].bUpMove = true;

	}

	if(g_aEnemy2[0].bUpMove == true)
	{
		g_aEnemy2[0].pos.y -= move_Enemy2;
	}
	else if(g_aEnemy2[0].bUpMove ==	false)
	{
		g_aEnemy2[0].pos.y += move_Enemy2;

	}
}
void SetEnemy2(D3DXVECTOR3 pos)
{
	for(int i = 0; i< MAX_ENEMY2; i++)
	{
		g_aEnemy2[i].pos.x = pos.x;
		g_aEnemy2[i].pos.y = pos.y;
		
	}
}