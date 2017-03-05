#include "main.h"
#include "explosion.h"
//�[�̍\����///////////////
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
} EXPLOSION;
/////////////////////////

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion =NULL;
EXPLOSION g_aExplosion [MAX_EXPLOSION];
float ExplosionWidth = 100.0f;		//�e�̕�
float ExplosionHeight = 100.0f;		//�e�̍���

//=============================================================================	
//  �֐����@�FInitExplosion
//  �@�\�T�v�F�e�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(MAX_EXPLOSION*4),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffExplosion,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *pVtx;
		g_pVtxBuffExplosion ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\explosion.png",
		&g_pTextureExplosion);
	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
				pVtx[0+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x- (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y- (ExplosionHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+ (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y- (ExplosionHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x- (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+ (ExplosionHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+ (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+ (ExplosionHeight/2) ,
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

		bUseExplosion = false;	 /* �e�𖢎g�p��Ԃ� */
	}
	g_pVtxBuffExplosion ->Unlock();	//LOCK
	return S_OK;

}
/*******************************************************************************
* �֐� :void UpdateExplosion(void)
* ���� :	�e�̍X�V���������������̊֐��B
*******************************************************************************/
void UpdateExplosion(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

	for(int i= 0;i<MAX_EXPLOSION;i++)
	{
		if(bUseExplosion == true)/* �e���g�p*/
			{
				/* �ʒu���X�V */
				pVtx[0+(4*i)].pos= D3DXVECTOR3( g_aExplosion[i].pos.x-(ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y-(ExplosionHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+(ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y-(ExplosionHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x- (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+ (ExplosionHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosion[i].pos.x+ (ExplosionWidth/2) ,
												 g_aExplosion[i].pos.y+(ExplosionHeight/2) ,
												 0.0f);


			}
		if(g_aExplosion[i].pos.x < 0.0f
			|| g_aExplosion[i].pos.x > SCREEN_WIDTH
			|| g_aExplosion[i].pos.y < 0.0f
			|| g_aExplosion[i].pos.y > SCREEN_HEIGHT)
		/* �e����ʊO�� */
			{
				/* �O��̈ʒu�ł̒e������ */
				bUseExplosion = false;		/* �e�𖢎g�p��Ԃ� */
			}
	}
	g_pVtxBuffExplosion ->Unlock();	//LOCK
}

/*******************************************************************************
* �֐� :void SetExplosion (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
* ���� :	�e�̐����̊֐��B
*******************************************************************************/
void SetExplosion (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
{
	for(int i = 0; i< MAX_EXPLOSION; i++)
	{
		if(bUseExplosion == false)
		{/* �e�����g�p��� */
			g_aExplosion[i].pos.x = pos.x;
			g_aExplosion[i].pos.y = pos.y;
			g_aExplosion[i].move.x =vecMove.x;
			g_aExplosion[i].move.y = vecMove.y;
			g_aExplosion[i].nLife = nLife;
			bUseExplosion = true;	 /* �e���g�p��Ԃ� */
			break;
		}
	}

}
//=============================================================================
//  �֐����@�FDrawExplosion
//  �@�\�T�v�F�e�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureExplosion);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffExplosion,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(bUseExplosion == true)
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
* �֐� :void UpdateExplosion(void)
* ���� :	�e�̏I�����������������̊֐��B
*******************************************************************************/
void UninitExplosion(void)
{
	if(g_pTextureExplosion!=NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion=NULL;
	}
	if(g_pVtxBuffExplosion!=NULL)
	{
		g_pVtxBuffExplosion->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffExplosion=NULL;
	}
}