#include "main.h"
#include "enemy.h"
#include "input.h"
#include "bulletenemy.h"
#include "explosion.h"
#include "pause.h"
//�O���[�o���ϐ�
ENEMY g_aEnemy[MAX_ENEMY];
LPDIRECT3DTEXTURE9 g_pTextureEnemy =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posEnemy;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotEnemy;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveEnemy;		//�|���S���̈ړ���
int g_nCounterAnim_Enemy;		//�A�����[�V�����J�E���^
int g_nPatternAnim_Enemy;		//�A�����[�V�����p�^�[��NO
float animRow_Enemy =1.0f;
float maxAnimX_Enemy = 7.0f;
float maxAnimY_Enemy = 1.0f;
float g_fLengthEnemy;		//�|���S���̑Ίp���̒���
float g_fAngleEnemy;		//�|���S���̑Ίp���̊p�x
float move_Enemy = 3.0f;		//�ړ���
float spinmove_cat =0.1f;		//��]��
float runSpeed_Enemy = 3.0f;
int animMaxnum_Enemy = 4;
float startAnimY_Enemy = 0.0f;
ENEMYSTATE g_enemystate = ENEMYSTATE_NORMAL;
ENEMYMOVE g_enemymove = ENEMYMOVE_1;
CATTYPE g_type = CAT_1;
bool bUseExplosion ;
 bool bUseExplosionenemy ;
//=============================================================================
//  �֐����@�FInitEnemy
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffEnemy,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffEnemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\cat.png",
		&g_pTextureEnemy);
		 bUseEnemy = true;
		for(int i= 0;i<MAX_ENEMY;i++)
		{
		g_aEnemy[i].nLifeenemy = 5;
		g_aEnemy[i].fHeight=25.0f;
		g_aEnemy[i].fWidth=170.0f;
			//����������
		g_aEnemy[i].pos.x = 1000.0f;
		g_aEnemy[i].pos.y = 220.0f;
		g_posEnemy = D3DXVECTOR3(g_aEnemy[i].pos.x,g_aEnemy[i].pos.y,0.0f);
		}
			//��]����������
		g_rotEnemy = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthEnemy =sqrtf(g_aEnemy[0].fWidth * g_aEnemy[0].fWidth + g_aEnemy[0].fHeight * g_aEnemy[0].fHeight)*0.5f;
		g_fAngleEnemy =atan2f(g_aEnemy[0].fWidth,g_aEnemy[0].fHeight)*0.5f;

		g_aEnemy[0].bUse = true;
		g_aEnemy[0].bUpMove = true;
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
								   0.0f);
		//UV�ݒ�
		switch(g_type)
		{
		case CAT_1:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_2:
			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_3:
			pVtx[0].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(2.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_4:
			pVtx[0].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(3.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_5:
			pVtx[0].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(4.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_6:
			pVtx[0].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(5.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;

		case CAT_7:
			pVtx[0].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			break;
		}
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

		g_pVtxBuffEnemy ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitEnemy
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitEnemy(void)
{

	if(g_pVtxBuffEnemy!=NULL)
	{
		g_pVtxBuffEnemy->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffEnemy=NULL;
	}
	if(g_pTextureEnemy!=NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawEnemy
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureEnemy);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffEnemy,
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
//  �֐����@�FUpdateEnemy
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateEnemy(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	if(  bUseEnemy  ==true)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	switch(g_enemystate)
		{
		case ENEMYSTATE_NORMAL:
			EnemyMove();
			break;
		}
		if((g_aEnemy[0].pos.x-g_aEnemy[0].fWidth/5) <= 0)
		{
			g_aEnemy[0].pos.x = (g_aEnemy[0].fWidth/5);
		}
	
		if((g_aEnemy[0].pos.x+g_aEnemy[0].fWidth/3)>= SCREEN_WIDTH)
		{
			g_aEnemy[0].pos.x = SCREEN_WIDTH+-(g_aEnemy[0].fWidth/3);
		}

		if((g_aEnemy[0].pos.y-g_aEnemy[0].fHeight/5) <= 0)
		{
			g_aEnemy[0].pos.y=(g_aEnemy[0].fHeight/5);
		}

		if((g_aEnemy[0].pos.y+g_aEnemy[0].fHeight/5) >= SCREEN_HEIGHT)
		{
			g_aEnemy[0].pos.y = SCREEN_HEIGHT+-(g_aEnemy[0].fHeight/5);
		}

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

		g_pVtxBuffEnemy ->Unlock();	//LOCK
	}
		if(  bUseEnemy  ==false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffEnemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

			pVtx[0].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy,0.0f);
			pVtx[2].tex = D3DXVECTOR2(6.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);
			pVtx[3].tex = D3DXVECTOR2(7.0f / maxAnimX_Enemy, 1.0f / maxAnimY_Enemy);

			pVtx[0].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[1].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y - cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);
	
			pVtx[2].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x - sinf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy - g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);

			pVtx[3].pos = D3DXVECTOR3 (g_aEnemy[0].pos.x + sinf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   g_aEnemy[0].pos.y + cosf( g_fAngleEnemy + g_rotEnemy.z ) * g_fLengthEnemy,
									   0.0f);
				g_pVtxBuffEnemy ->Unlock();	//LOCK
				 bUseExplosionenemy = false;
		}

	}
	
}

ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
void EnemyMove(void)
{
	if( g_aEnemy[0].pos.y <= 210.0f)
	{
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,0.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,5.0f,0.0f),5);
		g_aEnemy[0].bUpMove =false;
		bUseExplosion=false;
	}
	else if(g_aEnemy[0].pos.y >= 370.0f)
	{
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,0.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,5.0f,0.0f),5);
	SetBulletEnemy(D3DXVECTOR3(g_aEnemy[0].pos.x,g_aEnemy[0].pos.y,0.0f) ,D3DXVECTOR3(5.0f,-5.0f,0.0f),5);
		g_aEnemy[0].bUpMove = true;
		 bUseExplosionenemy = false;

	}

	if(g_aEnemy[0].bUpMove == true)
	{
		g_aEnemy[0].pos.y -= move_Enemy;
	}
	else if(g_aEnemy[0].bUpMove ==	false)
	{
		g_aEnemy[0].pos.y += move_Enemy;

	}
}
void SetEnemy(D3DXVECTOR3 pos)
{
	for(int i = 0; i< MAX_ENEMY; i++)
	{
		g_aEnemy[i].pos.x = pos.x;
		g_aEnemy[i].pos.y = pos.y;
		
	}
}