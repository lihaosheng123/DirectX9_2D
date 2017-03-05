#include "main.h"
#include "explosionenemy.h"
//�[�̍\����///////////////
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
}EXPLOSIONENEMY;
/////////////////////////

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosionenemy = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosionenemy =NULL;
EXPLOSIONENEMY g_aExplosionenemy [MAX_EXPLOSIONENEMY];
float ExplosionenemyWidth = 100.0f;		//�e�̕�
float ExplosionenemyHeight = 100.0f;		//�e�̍���

//=============================================================================	
//  �֐����@�FInitExplosionenemy
//  �@�\�T�v�F�e�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitExplosionenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(MAX_EXPLOSIONENEMY*4),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffExplosionenemy,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *pVtx;
		g_pVtxBuffExplosionenemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		".\\data\\TEXTURE\\explosionenemy.png",
		&g_pTextureExplosionenemy);
	for(int i = 0; i < MAX_EXPLOSIONENEMY; i++)
	{
				pVtx[0+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x- (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y- (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+ (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y- (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x- (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+ (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+ (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+ (ExplosionenemyHeight/2) ,
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

		bUseExplosionenemy = false;	 /* �e�𖢎g�p��Ԃ� */
	}
	g_pVtxBuffExplosionenemy ->Unlock();	//LOCK
	return S_OK;

}
/*******************************************************************************
* �֐� :void UpdateExplosionenemy(void)
* ���� :	�e�̍X�V���������������̊֐��B
*******************************************************************************/
void UpdateExplosionenemy(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosionenemy ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

	for(int i= 0;i<MAX_EXPLOSIONENEMY;i++)
	{
		if(bUseExplosionenemy == true)/* �e���g�p*/
			{
				/* �ʒu���X�V */
				pVtx[0+(4*i)].pos= D3DXVECTOR3( g_aExplosionenemy[i].pos.x-(ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y-(ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[1+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+(ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y-(ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[2+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x- (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+ (ExplosionenemyHeight/2) ,
												 0.0f);
				pVtx[3+(4*i)].pos = D3DXVECTOR3( g_aExplosionenemy[i].pos.x+ (ExplosionenemyWidth/2) ,
												 g_aExplosionenemy[i].pos.y+(ExplosionenemyHeight/2) ,
												 0.0f);


			}
		if(g_aExplosionenemy[i].pos.x < 0.0f
			|| g_aExplosionenemy[i].pos.x > SCREEN_WIDTH
			|| g_aExplosionenemy[i].pos.y < 0.0f
			|| g_aExplosionenemy[i].pos.y > SCREEN_HEIGHT)
		/* �e����ʊO�� */
			{
				/* �O��̈ʒu�ł̒e������ */
				bUseExplosionenemy = false;		/* �e�𖢎g�p��Ԃ� */
			}
	}
	g_pVtxBuffExplosionenemy ->Unlock();	//LOCK
}

/*******************************************************************************
* �֐� :void SetExplosionenemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
* ���� :	�e�̐����̊֐��B
*******************************************************************************/
void SetExplosionenemy (D3DXVECTOR3 pos,D3DXVECTOR3 vecMove,int nLife)
{
	for(int i = 0; i< MAX_EXPLOSIONENEMY; i++)
	{
		if(bUseExplosionenemy == false)
		{/* �e�����g�p��� */
			g_aExplosionenemy[i].pos.x = pos.x;
			g_aExplosionenemy[i].pos.y = pos.y;
			g_aExplosionenemy[i].move.x =vecMove.x;
			g_aExplosionenemy[i].move.y = vecMove.y;
			g_aExplosionenemy[i].nLife = nLife;
			bUseExplosionenemy = true;	 /* �e���g�p��Ԃ� */
			break;
		}
	}

}
//=============================================================================
//  �֐����@�FDrawExplosionenemy
//  �@�\�T�v�F�e�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawExplosionenemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureExplosionenemy);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffExplosionenemy,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i = 0; i < MAX_EXPLOSIONENEMY; i++)
	{
		if(bUseExplosionenemy == true)
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
* �֐� :void UpdateExplosionenemy(void)
* ���� :	�e�̏I�����������������̊֐��B
*******************************************************************************/
void UninitExplosionenemy(void)
{
	if(g_pTextureExplosionenemy!=NULL)
	{
		g_pTextureExplosionenemy->Release();
		g_pTextureExplosionenemy=NULL;
	}
	if(g_pVtxBuffExplosionenemy!=NULL)
	{
		g_pVtxBuffExplosionenemy->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffExplosionenemy=NULL;
	}
}