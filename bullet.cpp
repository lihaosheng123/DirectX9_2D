#include "main.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "explosionenemy.h"
#include "lifeenemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include "pause.h"
//�[�̍\����///////////////
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	bool bUse;
} BULLET;
/////////////////////////

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet =NULL;
BULLET g_aBullet [BULLET_MAX];
float BulletWidth = 10.0f;		//�e�̕�
float BulletHeight = 10.0f;		//�e�̍���
bool bUseEnemy ;
bool bUsebg1;
bool bUsebg2;
bool bUseEnemy3;
//=============================================================================	
//  �֐����@�FInitBullet
//  �@�\�T�v�F�e�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(BULLET_MAX*4),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffBullet,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *pVtx;
		g_pVtxBuffBullet ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bullet.png",
		&g_pTextureBullet);
	for(int i = 0; i < BULLET_MAX; i++)
	{
				pVtx[0+(4*i)].pos = D3DXVECTOR3( g_aBullet[i].pos.x- (BulletWidth/2) ,
												 g_aBullet[i].pos.y- (BulletHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aBullet[i].pos.x+ (BulletWidth/2) ,
												 g_aBullet[i].pos.y- (BulletHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aBullet[i].pos.x- (BulletWidth/2) ,
												 g_aBullet[i].pos.y+ (BulletHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aBullet[i].pos.x+ (BulletWidth/2) ,
												 g_aBullet[i].pos.y+ (BulletHeight/2) ,
												 0.0f);

		pVtx[0+(4*i)].rhw = 1.0f;
		pVtx[1+(4*i)].rhw = 1.0f;
		pVtx[2+(4*i)].rhw = 1.0f;
		pVtx[3+(4*i)].rhw = 1.0f;

		pVtx[0+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255,127 );	//���_���i�[���[�N
		pVtx[1+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[2+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);
		pVtx[3+(4*i)].col = D3DCOLOR_RGBA(255, 255, 255, 127);

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(1.f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_aBullet[i].bUse = false;	 /* �e�𖢎g�p��Ԃ� */
	}
	g_pVtxBuffBullet ->Unlock();	//LOCK
	return S_OK;

}
/*******************************************************************************
* �֐� :void UpdateBullet(void)
* ���� :	�e�̍X�V���������������̊֐��B
*******************************************************************************/
void UpdateBullet(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

	for(int i= 0;i<BULLET_MAX;i++)
	{
		if(g_aBullet[i].bUse == true)/* �e���g�p*/
			{
				g_aBullet[i].pos+=g_aBullet[i].move;
				/* �ʒu���X�V */
				pVtx[0+(4*i)].pos= D3DXVECTOR3( g_aBullet[i].pos.x-(BulletWidth/2) ,
												 g_aBullet[i].pos.y-(BulletHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aBullet[i].pos.x+(BulletWidth/2) ,
												 g_aBullet[i].pos.y-(BulletHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aBullet[i].pos.x- (BulletWidth/2) ,
												 g_aBullet[i].pos.y+ (BulletHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aBullet[i].pos.x+ (BulletWidth/2) ,
												 g_aBullet[i].pos.y+(BulletHeight/2) ,
												 0.0f);
				if(bUsebg1 == true)
				{
				ENEMY *pEnemy = GetEnemy();
					if(pEnemy->bUse == true)
					{
						if(( g_aBullet[i].pos.x- (BulletWidth/2))>=(pEnemy->pos.x -(pEnemy->fWidth)/2)
							&&( g_aBullet[i].pos.x+ (BulletWidth/2))<=(pEnemy->pos.x+(pEnemy->fWidth)/2)
							&&( g_aBullet[i].pos.y- (BulletHeight/2))>=(pEnemy->pos.y -(pEnemy->fHeight)/2)
							&&( g_aBullet[i].pos.y+ (BulletHeight/2))<=(pEnemy->pos.y+(pEnemy->fHeight)/2))
						{
							SetExplosionenemy(D3DXVECTOR3(g_aBullet[i].pos.x,g_aBullet[i].pos.y,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
							pEnemy->nLifeenemy--;
							UpdateLifeenemy();
							if(pEnemy->nLifeenemy <= 0)
							{
								bUseEnemy  =false;
							}
							g_aBullet[i].bUse = false;
							AddScore(1);
						}
					}
				}
				if(bUsebg2 == true)
				{
					ENEMY2 *pEnemy2 = GetEnemy2();
						if(pEnemy2->bUse == true)
						{
							if(( g_aBullet[i].pos.x- (BulletWidth/2))>=(pEnemy2->pos.x -(pEnemy2->fWidth)/2)
								&&( g_aBullet[i].pos.x+ (BulletWidth/2))<=(pEnemy2->pos.x+(pEnemy2->fWidth)/2)
								&&( g_aBullet[i].pos.y- (BulletHeight/2))>=(pEnemy2->pos.y -(pEnemy2->fHeight)/2)
								&&( g_aBullet[i].pos.y+ (BulletHeight/2))<=(pEnemy2->pos.y+(pEnemy2->fHeight)/2))
							{
								SetExplosionenemy(D3DXVECTOR3(g_aBullet[i].pos.x,g_aBullet[i].pos.y,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
								pEnemy2->nLifeenemy2--;
								UpdateLifeenemy();
								if(pEnemy2->nLifeenemy2 <= 0)
								{
									bUseEnemy2  =false;
								}
								g_aBullet[i].bUse = false;
								AddScore(1);
							}
						}
				}
						if(bUsebg3 == true)
				{
					ENEMY3 *pEnemy3 = GetEnemy3();
						if(pEnemy3->bUse == true)
						{
							if(( g_aBullet[i].pos.x- (BulletWidth/2))>=(pEnemy3->pos.x -(pEnemy3->fWidth)/2)
								&&( g_aBullet[i].pos.x+ (BulletWidth/2))<=(pEnemy3->pos.x+(pEnemy3->fWidth)/2)
								&&( g_aBullet[i].pos.y- (BulletHeight/2))>=(pEnemy3->pos.y -(pEnemy3->fHeight)/2)
								&&( g_aBullet[i].pos.y+ (BulletHeight/2))<=(pEnemy3->pos.y+(pEnemy3->fHeight)/2))
							{
								SetExplosionenemy(D3DXVECTOR3(g_aBullet[i].pos.x,g_aBullet[i].pos.y,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
								pEnemy3->nLifeenemy3--;
								UpdateLifeenemy();
								if(pEnemy3->nLifeenemy3 <= 0)
								{
									bUseEnemy3  =false;
								}
								g_aBullet[i].bUse = false;
								AddScore(1);
							}
						}
				}
		if(g_aBullet[i].pos.x < 0.0f
			|| g_aBullet[i].pos.x > SCREEN_WIDTH
			|| g_aBullet[i].pos.y < 0.0f
			|| g_aBullet[i].pos.y > SCREEN_HEIGHT)
		/* �e����ʊO�� */
			{
				/* �O��̈ʒu�ł̒e������ */
				g_aBullet[i].bUse = false;		/* �e�𖢎g�p��Ԃ� */
			}
		}
	}
	g_pVtxBuffBullet ->Unlock();	//LOCK
	}
}

/*******************************************************************************
* �֐� :void SetBullet (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
* ���� :	�e�̐����̊֐��B
*******************************************************************************/
void SetBullet (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
{
	for(int i = 0; i< BULLET_MAX; i++)
	{
		if(g_aBullet[i].bUse == false)
		{/* �e�����g�p��� */
			g_aBullet[i].pos.x = pos.x;
			g_aBullet[i].pos.y = pos.y;
			g_aBullet[i].move.x =vecMove.x;
			g_aBullet[i].move.y = vecMove.y;
			g_aBullet[i].nLife = nLife;
			g_aBullet[i].bUse = true;	 /* �e���g�p��Ԃ� */
			break;
		}
	}

}
//=============================================================================
//  �֐����@�FDrawBullet
//  �@�\�T�v�F�e�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawBullet(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureBullet);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffBullet,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_aBullet[i].bUse == true)
		{
	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  4*i,		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);
		}
	}
	}
}
/*******************************************************************************
* �֐� :void UpdateBullet(void)
* ���� :	�e�̏I�����������������̊֐��B
*******************************************************************************/
void UnintBullet(void)
{
	if(g_pTextureBullet!=NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet=NULL;
	}
	if(g_pVtxBuffBullet!=NULL)
	{
		g_pVtxBuffBullet->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffBullet=NULL;
	}
}