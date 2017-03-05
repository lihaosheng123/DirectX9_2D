#include "main.h"
#include "prop.h"
#include "input.h"
#include "score.h"
//�O���[�o���ϐ�
PROP g_aProp[MAX_PROP];
LPDIRECT3DTEXTURE9 g_pTextureProp =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffProp =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posProp;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotProp;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveProp;		//�|���S���̈ړ���
float animRow_Prop =1.0f;
float maxAnimX_Prop = 2.0f;
float maxAnimY_Prop = 1.0f;
float g_fLengthProp;		//�|���S���̑Ίp���̒���
float g_fAngleProp;		//�|���S���̑Ίp���̊p�x
float move_Prop = 2.0f;		//�ړ���
float runSpeed_Prop = 3.0f;
int animMaxnum_Prop = 2;
float startAnimY_Prop = 0.0f;
MODE g_ptype;
//=============================================================================
//  �֐����@�FInitProp
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitProp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffProp,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffProp ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\prop.png",
		&g_pTextureProp);
		bProp = false;
		bPropUpdate = false;
		g_aProp[0].fHeight=50.0f;
		g_aProp[0].fWidth=150.0f;
			//����������
		g_aProp[0].pos.x = 1115.0f;
		g_aProp[0].pos.y = 540.0f;
		g_posProp = D3DXVECTOR3(g_aProp[0].pos.x,g_aProp[0].pos.y,0.0f);
		
			//��]����������
		g_rotProp = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthProp =sqrtf(g_aProp[0].fWidth * g_aProp[0].fWidth + g_aProp[0].fHeight * g_aProp[0].fHeight)*0.5f;
		g_fAngleProp =atan2f(g_aProp[0].fWidth,g_aProp[0].fHeight)*0.5f;


		
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Prop);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop, 1.0f / maxAnimY_Prop);
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

		g_pVtxBuffProp ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitProp
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitProp(void)
{

	if(g_pVtxBuffProp!=NULL)
	{
		g_pVtxBuffProp->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffProp=NULL;
	}
	if(g_pTextureProp!=NULL)
	{
		g_pTextureProp->Release();
		g_pTextureProp=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawProp
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawProp(void)
{
	if(bProp == false )
	{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureProp);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffProp,
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
}
//=============================================================================
//  �֐����@�FUpdateProp
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateProp(void)
{
	if(bPropUpdate== true)
	{
		if(bProp == false)
		{
			VERTEX_2D *pVtx;
			g_pVtxBuffProp ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾


			g_aProp[0].pos.x = 980.0f;
			g_aProp[0].pos.y = 730.0f;

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / maxAnimY_Prop);
			pVtx[3].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop, 1.0f / maxAnimY_Prop);
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y - cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp[0].pos.x - sinf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp - g_rotProp.z ) * g_fLengthProp,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp[0].pos.x + sinf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   g_aProp[0].pos.y + cosf( g_fAngleProp + g_rotProp.z ) * g_fLengthProp,
								   0.0f);
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

		g_pVtxBuffProp ->Unlock();	//LOCK
		}
	}



}

PROP *GetProp(void)
{
	return &g_aProp[0];
}

