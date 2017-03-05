#include "main.h"
#include "bulletenemy.h"
#include "polygon.h"
#include "score.h"
#include "explosion.h"
#include "fade.h"
#include "life.h"
#include "pause.h"
//�[�̍\����///////////////
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	bool bUse;
} BulletEnemy;
/////////////////////////

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBulletEnemy = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBulletEnemy =NULL;
BulletEnemy g_aBulletEnemy [BULLETENEMY_MAX];
float BulletEnemyWidth = 60.0f;		//�e�̕�
float BulletEnemyHeight = 60.0f;		//�e�̍���

//=============================================================================
//  �֐����@�FInitBulletEnemy
//  �@�\�T�v�F�e�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitBulletEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(BULLETENEMY_MAX*4),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffBulletEnemy,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *pVtx;
		g_pVtxBuffBulletEnemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\bulletenemy.png",
		&g_pTextureBulletEnemy);
	for(int i = 0; i < BULLETENEMY_MAX; i++)
	{
				pVtx[0+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y- (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y- (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2) ,
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

		g_aBulletEnemy[i].bUse = false;	 /* �e�𖢎g�p��Ԃ� */
	}
	g_pVtxBuffBulletEnemy ->Unlock();	//LOCK
	return S_OK;

}
/*******************************************************************************
* �֐� :void UpdateBulletEnemy(void)
* ���� :	�e�̍X�V���������������̊֐��B
*******************************************************************************/
void UpdateBulletEnemy(void)
{
	PAUSEUSE *bUseCheck = GetPause();
	if(bUseCheck->bUse == false)
	{
	VERTEX_2D *pVtx;
	g_pVtxBuffBulletEnemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

	for(int i= 0;i<BULLETENEMY_MAX;i++)
	{
		if(g_aBulletEnemy[i].bUse == true)/* �e���g�p*/
			{
				g_aBulletEnemy[i].pos-=g_aBulletEnemy[i].move;
				/* �ʒu���X�V */
				pVtx[0+(4*i)].pos= D3DXVECTOR3( g_aBulletEnemy[i].pos.x-(BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y-(BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+(BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y-(BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2) ,
												 g_aBulletEnemy[i].pos.y+(BulletEnemyHeight/2) ,
												 0.0f);
				POLYGON *pPolygon = GetPolygon();
					if(pPolygon->bUse == true)
					{
						if(bUseTalk == false)
						{
						if(( g_aBulletEnemy[i].pos.x- (BulletEnemyWidth/2))>=(pPolygon->pos.x -(pPolygon->fWidth)/2)
							&&( g_aBulletEnemy[i].pos.x+ (BulletEnemyWidth/2))<=(pPolygon->pos.x+(pPolygon->fWidth)/2)
							&&( g_aBulletEnemy[i].pos.y- (BulletEnemyHeight/2))>=(pPolygon->pos.y -(pPolygon->fHeight)/2)
							&&( g_aBulletEnemy[i].pos.y+ (BulletEnemyHeight/2))<=(pPolygon->pos.y+(pPolygon->fHeight)/2))
						{
							SetExplosion(D3DXVECTOR3(g_aBulletEnemy[i].pos.x,g_aBulletEnemy[i].pos.y,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
							pPolygon->nLife--;
							UpdateLife();
							if(pPolygon->nLife <= 0)
							{
								SetFade(FADE_OUT,MODE_RESULT);
							}
							g_aBulletEnemy[i].bUse = false;
						}
						}
					}
			}
		if(g_aBulletEnemy[i].pos.x < 0.0f
			|| g_aBulletEnemy[i].pos.x > SCREEN_WIDTH
			|| g_aBulletEnemy[i].pos.y < 0.0f
			|| g_aBulletEnemy[i].pos.y > SCREEN_HEIGHT)
		/* �e����ʊO�� */
			{
				/* �O��̈ʒu�ł̒e������ */
				g_aBulletEnemy[i].bUse = false;		/* �e�𖢎g�p��Ԃ� */
			}
	}
	g_pVtxBuffBulletEnemy ->Unlock();	//LOCK
	}
}

/*******************************************************************************
* �֐� :void SetBulletEnemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
* ���� :	�e�̐����̊֐��B
*******************************************************************************/
void SetBulletEnemy (D3DXVECTOR3 posEnemy,D3DXVECTOR3 vecMoveEnemy,int nLifeEnemy)
{
	for(int i = 0; i< BULLETENEMY_MAX; i++)
	{
		if(g_aBulletEnemy[i].bUse == false)
		{/* �e�����g�p��� */
			g_aBulletEnemy[i].pos.x = posEnemy.x;
			g_aBulletEnemy[i].pos.y = posEnemy.y;
			g_aBulletEnemy[i].move.x =vecMoveEnemy.x;
			g_aBulletEnemy[i].move.y = vecMoveEnemy.y;
			g_aBulletEnemy[i].nLife = nLifeEnemy;
			g_aBulletEnemy[i].bUse = true;	 /* �e���g�p��Ԃ� */
			break;
		}
	}

}
//=============================================================================
//  �֐����@�FDrawBulletEnemy
//  �@�\�T�v�F�e�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawBulletEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureBulletEnemy);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffBulletEnemy,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i = 0; i < BULLETENEMY_MAX; i++)
	{
		if(g_aBulletEnemy[i].bUse == true)
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
/*******************************************************************************
* �֐� :void UpdateBulletEnemy(void)
* ���� :	�e�̏I�����������������̊֐��B
*******************************************************************************/
void UnintBulletEnemy(void)
{
	if(g_pTextureBulletEnemy!=NULL)
	{
		g_pTextureBulletEnemy->Release();
		g_pTextureBulletEnemy=NULL;
	}
	if(g_pVtxBuffBulletEnemy!=NULL)
	{
		g_pVtxBuffBulletEnemy->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffBulletEnemy=NULL;
	}
}