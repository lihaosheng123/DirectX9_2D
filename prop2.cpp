#include "main.h"
#include "prop2.h"
#include "input.h"
//�O���[�o���ϐ�
PROP2 g_aProp2[MAX_PROP2];
LPDIRECT3DTEXTURE9 g_pTextureProp2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffProp2 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posProp2;	//�|���S���̈ʒu
D3DXVECTOR3 g_rotProp2;		//�|���S���̉�]�p
D3DXVECTOR3 g_moveProp2;		//�|���S���̈ړ���
float animRow_Prop2 =1.0f;
float maxAnimX_Prop2 = 2.0f;
float maxAnimY_Prop2 = 1.0f;
float g_fLengthProp2;		//�|���S���̑Ίp���̒���
float g_fAngleProp2;		//�|���S���̑Ίp���̊p�x
float move_Prop2 = 2.0f;		//�ړ���
float runSpeed_Prop2 = 3.0f;
int animMaxnum_Prop2 = 2;
float startAnimY_Prop2 = 0.0f;
bool bUseComputer;
//=============================================================================
//  �֐����@�FInitProp2
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitProp2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffProp2,NULL)))
	{
		return E_FAIL;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffProp2 ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
		//�e�N�X�`���̓ǂݍ���	
		D3DXCreateTextureFromFile(
			pDevice,
			".\\data\\TEXTURE\\prop.png",
		&g_pTextureProp2);
		 bProp2 = false;

		g_aProp2[0].fHeight=50.0f;
		g_aProp2[0].fWidth=150.0f;
			//����������
		g_aProp2[0].pos.x = 1115.0f;
		g_aProp2[0].pos.y = 540.0f;
		g_posProp2 = D3DXVECTOR3(g_aProp2[0].pos.x,g_aProp2[0].pos.y,0.0f);
		
			//��]����������
		g_rotProp2 = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_fLengthProp2 =sqrtf(g_aProp2[0].fWidth * g_aProp2[0].fWidth + g_aProp2[0].fHeight * g_aProp2[0].fHeight)*0.5f;
		g_fAngleProp2 =atan2f(g_aProp2[0].fWidth,g_aProp2[0].fHeight)*0.5f;


		
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);


			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);


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

		g_pVtxBuffProp2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitProp2
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitProp2(void)
{

	if(g_pVtxBuffProp2!=NULL)
	{
		g_pVtxBuffProp2->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffProp2=NULL;
	}
	if(g_pTextureProp2!=NULL)
	{
		g_pTextureProp2->Release();
		g_pTextureProp2=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawProp2
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawProp2(void)
{
	//if(bProp2 == false )
	//{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureProp2);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffProp2,
								0,
								sizeof(VERTEX_2D)
								);
	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  0,		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);
	//}
}
//=============================================================================
//  �֐����@�FUpdateProp2
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateProp2(void)
{
	if( bProp2 ==true)
	{
	g_aProp2[0].pos.y++;
	}
	if(g_aProp2[0].pos.y >=600.0f)
	{
		bUseComputer = false;
		g_aProp2[0].pos.y = 600.0f;
	}
		VERTEX_2D *pVtx;
		g_pVtxBuffProp2 ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾


		
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[1].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y - cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[2].pos = D3DXVECTOR3 (g_aProp2[0].pos.x - sinf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 - g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);

		pVtx[3].pos = D3DXVECTOR3 (g_aProp2[0].pos.x + sinf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   g_aProp2[0].pos.y + cosf( g_fAngleProp2 + g_rotProp2.z ) * g_fLengthProp2,
								   0.0f);


			pVtx[0].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 0.0f );
			pVtx[1].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2,0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);
			pVtx[3].tex = D3DXVECTOR2(2.0f / maxAnimX_Prop2, 1.0f / maxAnimY_Prop2);


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

		g_pVtxBuffProp2 ->Unlock();	//LOCK

}

PROP2 *GetProp2(void)
{
	return &g_aProp2[0];
}

